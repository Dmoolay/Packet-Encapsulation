/*
 * Switch.cc
 *
 *  Created on: 1 במאי 2022
 *      Author: Administrator
 */
#include <stdio.h>
#include <string.h>
#include <map>
#include <iterator>
#include <iostream>
#include <omnetpp.h>
#include "Eth_msg_m.h"
#include "ARP_msg_m.h"
using namespace omnetpp;
using namespace std;
#define RATE 100000000

class Switch : public cSimpleModule
{
  private:
    int number_of_host;
    long numReceived;
    string broadcast_mac;
    map <string, pair<int, simtime_t>>arp_table;
    map<string, pair<int, simtime_t>>::iterator it ;
    simtime_t Aging_Time, latency;
    simtime_t curr, temp=1;
    cDoubleHistogram delay_stats;
    cOutVector delay_vector;
    long double t1;

  protected:
    virtual void InsertArpTable(string mac, int port);
    virtual int CheckArpTable(string mac);
    virtual void UpdateArpTable();
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void updateVector(Eth_msg *msg, simtime_t latency, int len);
    virtual void forwardMessage(Eth_msg *msg, int idx , simtime_t latency, int len);
    virtual void finish() override;
};

Define_Module(Switch);

void Switch::initialize()
{
    // Initialize variables
    number_of_host = 10;
    numReceived = 0;
    broadcast_mac = "ff.ff.ff.ff.ff.ff";
    Aging_Time = par("switch_aging_time");
    latency = par("switch_latency");
}

void Switch::handleMessage(cMessage *msg)
{
    int port;
    cPacket *ttmsg1 = check_and_cast<cPacket *>(msg);
    int len = ttmsg1->getByteLength();
    //int len1 = ttmsg1->getBitLength();
    Eth_msg *ttmsg = check_and_cast<Eth_msg *>(msg);
    if(msg->arrivedOn("s_port$i")){
        int gate_number = ttmsg->getArrivalGate()->getIndex();
        string mac_src = ttmsg->getMac_src();
        string mac_dest = ttmsg->getMac_dest();
        UpdateArpTable();
        InsertArpTable(mac_src, gate_number);
        UpdateArpTable();
        if(CheckArpTable(mac_dest)){
           //have destination address in table
           port = arp_table[mac_dest].first;
           latency = par("switch_latency");
           if(ttmsg->getType() == 3){updateVector (ttmsg, latency, len);}
           forwardMessage(ttmsg,port,  latency,  len);
        }
        else{
            // dont have destination address in table, so forward the msg in broadcast.
            EV<<"SWITCH - SEND BROADCAST!"<<endl;
            latency = par("switch_latency");
            simtime_t curr = simTime();
            if(ttmsg->getType() == 3){updateVector (ttmsg, latency, len);}
            for(int i=0; i<number_of_host; i++){
                if(i != gate_number){
                    forwardMessage(ttmsg->dup(),i,  latency, len);
                }
            }
            delete(ttmsg);
        }
    }
}

void Switch::forwardMessage(Eth_msg *msg, int idx, simtime_t latency, int len)
{

    if(gate("s_port$o",idx)->getTransmissionChannel()->isBusy()){
        simtime_t finish = gate("s_port$o",idx)->getTransmissionChannel()->getTransmissionFinishTime();
        sendDelayed(msg,(latency*len)+finish-simTime(),"s_port$o",idx);
    }
    else{
        sendDelayed(msg, latency*len,"s_port$o",idx);
    }
}


void Switch::InsertArpTable(string mac, int port) // check if address in table and insert if not.
{
    int flag1 = 1;
    for (std::map<string,pair<int, simtime_t>>::iterator it=arp_table.begin(); it!=arp_table.end(); ++it){
        if(it->first.compare(mac)==0){
            flag1 = 0;
        }
     }
    if(flag1){        // need to insert ip and mac address to table
        arp_table[mac] = make_pair(port,simTime());
        EV<<"SWITCH - INSERT ADDRESS TO TABLE!"<<endl;
    }
}

int Switch::CheckArpTable(string mac) //check if ip address in table
{
    for (std::map<string,pair<int, simtime_t>>::iterator it=arp_table.begin(); it!=arp_table.end(); ++it){
        if(it->first.compare(mac)==0){
            return 1;
        }
     }
    return 0;
}

void Switch::UpdateArpTable()  // update the arp table, delete addresses that out of time.
{
    std::map<string,pair<int, simtime_t>>::iterator it;
    for (it=arp_table.begin(); it!=arp_table.end();){
        if((simTime()-(it->second.second)) > Aging_Time){
            EV<<"SWITCH - TIME EXPIRED!"<<endl;
            it=arp_table.erase(it);
        }
        else{
            ++it;
        }
     }
}

void Switch::updateVector(Eth_msg *msg, simtime_t latency, int len)
{
    numReceived++;
    curr = simTime();
    EV<<"TEMP = "<< temp <<endl;
    t1 = curr.dbl() - msg->getCreationTime().dbl() + (latency*len).dbl() + ((temp*len*8)/100000000).dbl();
    delay_vector.record(t1);
    delay_stats.collect(t1);
}

void Switch::finish()
{
    EV << "=============================================================" << endl;
    EV << "Delay statistics(Switch):  " << endl;
    EV << "Min= "<< delay_stats.getMin() << "[sec]" << endl;
    EV << "Max= "<< delay_stats.getMax() << "[sec]" << endl;
    EV << "Mean= "<< delay_stats.getMean() << "[sec]" << endl;
    EV << "StdDev= "<< delay_stats.getStddev() << "[sec]" << endl;
    EV << "Variance= "<< delay_stats.getVariance() << "[sec]" << endl;
    EV << "=============================================================" << endl;
    EV << "" << endl;
    delay_stats.recordAs("Delays");
}
