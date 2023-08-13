/*
 * Ip.cc
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
#include "App_msg_m.h"
#include "IP_msg_m.h"
using namespace omnetpp;
using namespace std;

class IP : public cSimpleModule
{
  private:
    int number_of_host, my_idx, host_to_send;
    long numSent,numReceived;
    string my_ip, iptosend;

  protected:
    virtual void forwardMessage(IP_msg *msg, int num);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual IP_msg *generateMessage(int idx);
};

Define_Module(IP);

void IP::initialize()
{
    // Initialize variables
    numSent = 0;
    numReceived = 0;
    number_of_host = 10;
    my_ip = "172.168.32.";
    iptosend = "172.168.32.";
    my_idx = getParentModule()->getIndex();
    my_ip.append(to_string(my_idx));
    host_to_send = my_idx;
}

IP_msg *IP::generateMessage(int idx)
{
    IP_msg *msg = new IP_msg("IP-MSG");
    msg->setIp_src(my_ip.c_str());
    msg->setIp_dest(iptosend.append(to_string(idx)).c_str());
    iptosend.pop_back();
    msg->setByteLength(20);
    numSent++; //increase the total number of message we sent.
    return msg;
}

void IP::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("IP_A$i")){   // got msg from APP, send to ETH
        App_msg *ttmsg = check_and_cast<App_msg *>(msg);
        host_to_send = par("dest_idx");
        while(host_to_send==my_idx){host_to_send = par("dest_idx");}
        host_to_send=0;//=========================================================================================
        IP_msg *new_msg = generateMessage(host_to_send);
        new_msg->encapsulate(ttmsg);
        forwardMessage(new_msg, 0);
        }
    else{    // got data msg from ETH, send to APP
        IP_msg *IP_msg1 = check_and_cast<IP_msg *>(msg);
        if((my_ip.compare(IP_msg1->getIp_dest()) == 0)){ // message is for me
            forwardMessage(IP_msg1, 1);
        }
        else{
            delete msg;
        }
     }
}

void IP::forwardMessage(IP_msg *msg, int num) // 0 = forward to ETH, 1 = forward to APP
{
    if(num == 0){
        send(msg,"IP_E$o");
    }
    else{
        cPacket *IPmsg1 = msg->decapsulate();
        App_msg *App_msg1 = check_and_cast<App_msg *>(IPmsg1);
        send(App_msg1,"IP_A$o");
        delete(msg);
    }
}

