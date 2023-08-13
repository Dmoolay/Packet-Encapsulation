/*
 * Eth.cc
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
#include "IP_msg_m.h"
using namespace omnetpp;
using namespace std;

class Ethernet : public cSimpleModule
{
  private:
    int number_of_host, my_idx;
    long numSent,numReceived, numReceived_ARP_9, numReceived_ARP;
    string my_ip, iptosend;
    string my_mac, mactosend, broadcast_mac;
    map <string, pair<string, simtime_t>>arp_table;
    simtime_t Aging_Time, prev_9, curr_9, interval_9, ARP_interval[10], curr, interval;
    cMessage *gen;
    cDoubleHistogram inteval_ARP_9, inteval_ARP;
    cOutVector inteval_vector_ARP_9, inteval_vector_ARP;

  protected:
    virtual Eth_msg *generateMessage(int num, int idx);
    virtual ARP_msg *generate_ARP_Message(int num, int idx);
    virtual void forwardMessage(Eth_msg *msg, int num);
    virtual void InsertArpTable(ARP_msg *msg);
    virtual void UpdateArpTable();
    virtual void InsertArpTable_FromIpMessaage(IP_msg *msg, string macAdd);
    virtual int CheckArpTable(string ip);
    virtual int Check_If_ArpTable_Complete();
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

Define_Module(Ethernet);

void Ethernet::initialize()
{
    // Initialize variables
    numSent = 0;
    numReceived = 0;
    numReceived_ARP_9 = 0;
    numReceived_ARP = 0;
    number_of_host = 10;
    curr_9 = simTime();
    prev_9 = simTime();
    curr = simTime();
    for(int i=0; i<number_of_host; i++){ ARP_interval[i] = simTime();}

    inteval_ARP_9.setName("ARP interval host 9");
    inteval_vector_ARP_9.setName("interval vector ARP host 9");
    inteval_ARP.setName("interval ARP ALL HOST");
    inteval_vector_ARP.setName("interval_vector_ARP");

    my_ip = "172.168.32.";
    iptosend = "172.168.32.";
    my_mac = "11.11.11.11.11.0";
    mactosend = "11.11.11.11.11.0";
    broadcast_mac = "ff.ff.ff.ff.ff.ff";
    Aging_Time = par("arp_aging_time");

    my_idx = getParentModule()->getIndex();
    if(my_idx==9){Aging_Time = par("arp_aging_time_9");}
    my_ip.append(to_string(my_idx));
    my_mac.append(to_string(my_idx));
}

void Ethernet::finish()
{
    EV << "=============================================================" << endl;
    EV << getFullPath() << " statistic: " << endl;
    EV << "" << endl;
    EV << "Number of received Arp request from HOST 9: "<< numReceived_ARP_9 << endl;
    EV << "" << endl;
    EV << "Arrival interval statistics (Arp request from HOST 9):  " << endl;
    EV << "Min= "<< inteval_ARP_9.getMin() << "[sec]" << endl;
    EV << "Max= "<< inteval_ARP_9.getMax() << "[sec]" << endl;
    EV << "Mean= "<< inteval_ARP_9.getMean() << "[sec]" << endl;
    EV << "StdDev= "<< inteval_ARP_9.getStddev() << "[sec]" << endl;
    EV << "Variance= "<< inteval_ARP_9.getVariance() << "[sec]" << endl;
    EV << "" << endl;
    EV << "=============================================================" << endl;
    EV << "" << endl;
    EV << "=============================================================" << endl;
    EV << getFullPath() << " statistic: " << endl;
    EV << "" << endl;
    EV << "Number of received Arp request from ALL HOST: "<< numReceived_ARP << endl;
    EV << "" << endl;
    EV << "Arrival interval statistics (Arp request from ALL HOST):  " << endl;
    EV << "Min= "<< inteval_ARP.getMin() << "[sec]" << endl;
    EV << "Max= "<< inteval_ARP.getMax() << "[sec]" << endl;
    EV << "Mean= "<< inteval_ARP.getMean() << "[sec]" << endl;
    EV << "StdDev= "<< inteval_ARP.getStddev() << "[sec]" << endl;
    EV << "Variance= "<< inteval_ARP.getVariance() << "[sec]" << endl;
    EV << "=============================================================" << endl;
    EV << "" << endl;

    inteval_ARP_9.recordAs("Arrival Arp Intervals - HOST 9");
    inteval_ARP.recordAs("Arrival Arp Intervals - All Host");
}

ARP_msg *Ethernet::generate_ARP_Message(int num, int idx)
{
    ARP_msg *msg = new ARP_msg();
    if (num==1){
        msg->setName("ARP-request");
        msg->setOpcode(1);                                        // 1 = request
        msg->setMac_src(my_mac.c_str());                          // my mac address
        msg->setIp_src(my_ip.c_str());                            // my ip address
        msg->setMac_dest(broadcast_mac.c_str());                  // broadcast
        msg->setIp_dest(iptosend.append(to_string(idx)).c_str()); // dest ip
        iptosend.pop_back();
        msg->setByteLength(28);
    }
    else{
        msg->setName("ARP-reply");
        msg->setOpcode(2);                                         // 2 = reply
        msg->setMac_src(my_mac.c_str());                           // my mac address
        msg->setIp_src(my_ip.c_str());                             // my ip address
        msg->setMac_dest(mactosend.append(to_string(idx)).c_str());// dest mac address
        msg->setIp_dest(iptosend.append(to_string(idx)).c_str());  // dest ip address
        mactosend.pop_back();
        iptosend.pop_back();
        msg->setByteLength(28);
    }
    return msg;
}

Eth_msg *Ethernet::generateMessage(int num, int idx)
{
    Eth_msg *msg = new Eth_msg();
    if (num==1){ //generate ARP-request

        msg->setName("ARP-request");
        msg->setMac_src(my_mac.c_str());
        msg->setMac_dest(broadcast_mac.c_str());
        msg->setType(1);
        ARP_msg *msg_arp = generate_ARP_Message(num,idx);
        msg->setByteLength(14);
        msg->encapsulate(msg_arp);
    }
    else if(num==2){ // generate ARP-reply
        msg->setName("ARP-reply");
        msg->setMac_src(my_mac.c_str());
        msg->setMac_dest(mactosend.append(to_string(idx)).c_str());
        mactosend.pop_back();
        msg->setType(2);
        ARP_msg *msg_arp = generate_ARP_Message(num,idx);
        msg->setByteLength(14);
        msg->encapsulate(msg_arp);
    }
    else{
        // for data msg
        msg->setMac_src(my_mac.c_str());
        msg->setMac_dest(mactosend.append(to_string(idx)).c_str());
        mactosend.pop_back();
        msg->setType(3);
        msg->setByteLength(14);
    }
    numSent++; //increase the total number of message we sent.
    return msg;
}

void Ethernet::handleMessage(cMessage *msg)
{
        if(msg->arrivedOn("host_port$i")){     // if got message from switch
            Eth_msg *ttmsg = check_and_cast<Eth_msg *>(msg);
            string eth_mac_dest = ttmsg->getMac_dest();
            string eth_mac_src = ttmsg->getMac_src();
            if((my_mac.compare(eth_mac_dest) == 0) || (broadcast_mac.compare(eth_mac_dest) == 0)){
                // mac address destination is for me or broadcast

                if(ttmsg->getType()==1){              // if got ARP-request msg
                    cPacket *Amsg1 = ttmsg->decapsulate();
                    ARP_msg *Amsg = check_and_cast<ARP_msg *>(Amsg1);
                    string ip_tocheck = Amsg->getIp_dest();
                    string ip_to_send = Amsg->getIp_src();
                    if ((my_ip.compare(ip_tocheck)) == 0) {
                        // destination ip address of message = my ip address,
                        // need to reply with ARP-reply.
                        UpdateArpTable();
                        InsertArpTable(Amsg);
                        numReceived++; //increase the total number of message we received.
                        char ch = ip_to_send.back();
                        int k = ch-48;
                        //==================================================================================================
                        if(my_idx==0)
                        {
                            if(k==9){
                                numReceived_ARP_9++;
                                curr_9 = simTime();
                                interval_9 = curr_9-prev_9;
                                inteval_vector_ARP_9.record(interval_9.dbl());
                                inteval_ARP_9.collect(interval_9.dbl());
                                prev_9 = simTime();
                                EV << "---------------- numReceived_ARP_9 = "<< numReceived_ARP_9 << "---------------------" << endl;
                            }
                            else{
                                numReceived_ARP++;
                                curr = simTime();
                                interval = curr-ARP_interval[k];
                                inteval_vector_ARP.record(interval.dbl());
                                inteval_ARP.collect(interval.dbl());
                                ARP_interval[k] = simTime();
                            }
                        }
                        //=================================================================================================
//                        if(numReceived_ARP_9==20){endSimulation();}//====================================================
                        Eth_msg *new_msg = generateMessage(2, k);
                        forwardMessage(new_msg, 0);  // 0 = forward to Switch, 1 = forward to IP
                        delete Amsg;
                        delete ttmsg;
                        }
                    else{
                        //msg is not for me, delete msg and do nothing
                        delete Amsg;
                        delete ttmsg;
                    }
                }
                else if(ttmsg->getType()==2){  // got ARP-reply msg
                    cPacket *Amsg1 = ttmsg->decapsulate();
                    ARP_msg *Amsg = check_and_cast<ARP_msg *>(Amsg1);
                    string ip_tocheck = Amsg->getIp_dest();
                    if ((my_ip.compare(ip_tocheck)) == 0){   // destination ip address of message = my ip address
                        UpdateArpTable();
                        InsertArpTable(Amsg);
                    }
                    delete Amsg;
                    delete ttmsg;
                }
                else if (ttmsg->getType()==3){
                    // got data message from another host

                    EV<<"FORWARD DATA MESSAGE -TO- IP"<<endl;
                    forwardMessage(ttmsg, 1);
                }
                else{
                    //got message with no familiar type! ERROR!
                    EV << "got message with no familiar type! ERROR!"<< endl;
                    delete ttmsg;
                }
            }
            else{ // message  is not for me!
                delete ttmsg;
            }
        }//until here msg from switch port!

        else{// HERE- message from my ip!
             //data message from IP to send
            IP_msg *msg_to_send = check_and_cast<IP_msg *>(msg);
            string ip_dest = msg_to_send->getIp_dest();
            char ch;
            int k;
            UpdateArpTable();
            if(CheckArpTable(ip_dest)){
                ch = ip_dest.back();
                k = ch-48;
                Eth_msg *eth_msg_to_send = generateMessage(3, k);
                eth_msg_to_send->encapsulate(msg_to_send);
                forwardMessage(eth_msg_to_send, 0);
                }
            else{
                //dont have ip in arp table, need to send arp request
                EV<<"DONT HAVE ADDRESS IN TABLE, DROP DATA, SEND ARP REQUEST INSTEAD!!"<<endl;
                ch = ip_dest.back();
                k = ch-48;
                Eth_msg *new_msg = generateMessage(1, k);
                forwardMessage(new_msg, 0); // 0 = forward to Switch, 1 = forward to IP
            }
        }
}

void Ethernet::forwardMessage(Eth_msg *msg, int num) // 0 = forward to Switch, 1 = forward to IP
{
    if(num == 0){
        if(gate("host_port$o")->getTransmissionChannel()->isBusy()){
                    simtime_t finish = gate("host_port$o")->getTransmissionChannel()->getTransmissionFinishTime();
                    sendDelayed(msg,finish-simTime(),"host_port$o");
        }
        else{
            send(msg,"host_port$o");
        }
    }
    else{
        Eth_msg *ttmsg = check_and_cast<Eth_msg *>(msg);
        string eth_mac_src = ttmsg->getMac_src();
        cPacket *IPmsg1 = ttmsg->decapsulate();
        IP_msg *IPmsg = check_and_cast<IP_msg *>(IPmsg1);
        EV<<"FROM: "<<endl;
        EV<< IPmsg->getIp_src() <<endl;
        EV<<"TO: "<<endl;
        EV<< IPmsg->getIp_dest() <<endl;
        UpdateArpTable();
        InsertArpTable_FromIpMessaage(IPmsg, eth_mac_src); //check if address in arp table, insert if not.
        send(IPmsg,"E_IP$o");
    }
}

void Ethernet::InsertArpTable(ARP_msg *msg)  // check if address in table and insert if not.
{
    int flag1 = 1;
    string ip = msg->getIp_src();
    string mac = msg->getMac_src();
    for (std::map<string,pair<string, simtime_t>>::iterator it=arp_table.begin(); it!=arp_table.end(); ++it){
        if(it->first.compare(ip)==0){
            EV<<"HAVE ADDRESS IN TABLE!"<<endl;
            it->second.second = simTime();//test EFI
            flag1 = 0;
        }
     }
    if(flag1){        // need to insert ip and mac address to table
        arp_table[ip] = make_pair(mac,simTime());
    }
}
void Ethernet::InsertArpTable_FromIpMessaage(IP_msg *msg1, string macAdd)  // check if address in table and insert if not.
{   // this check is to data message!
    IP_msg *msg = check_and_cast<IP_msg *>(msg1);
    int flag1 = 1;
    string ip = msg->getIp_src();
    for (std::map<string,pair<string, simtime_t>>::iterator it=arp_table.begin(); it!=arp_table.end(); ++it){
        if(it->first.compare(ip)==0){
            EV<<"HAVE ADDRESS IN TABLE - FROM IP!"<<endl;
            flag1 = 0;
        }
     }
    if(flag1){        // need to insert ip and mac address to table
        arp_table[ip] = make_pair(macAdd,simTime());
        EV << "HOST - INSERT ADDRESS TO TABLE!" << endl;
    }
}

int Ethernet::CheckArpTable(string ip) //check if ip address in table
{
    for (std::map<string,pair<string, simtime_t>>::iterator it=arp_table.begin(); it!=arp_table.end(); ++it){
        if(it->first.compare(ip)==0){ //found ip in table
            return 1;
        }
     }
    return 0; // didnt found
}

int Ethernet::Check_If_ArpTable_Complete() // check if table complete
{
    if(arp_table.size()==3){
        return 1;
    }
    return 0;
}

void Ethernet::UpdateArpTable()  // update the arp table, delete addresses that out of time.
{
    map<string,pair<string, simtime_t>>::iterator it;
    for (it=arp_table.begin(); it!=arp_table.end();){
        if((simTime()-(it->second.second)) > Aging_Time){
            EV<<"HOST " << my_idx <<" TIME EXPIRED!"<<endl;
            it = arp_table.erase(it);
        }
        else{
            ++it;
        }
     }
}

