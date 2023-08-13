/*
 * App.cc
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

class App : public cSimpleModule
{
  private:

    int my_idx;
    long numSent, numReceived;
    simtime_t delay,Aging_Time, SEC;
    cMessage *gen;
    simtime_t curr, prev, interval;
    cDoubleHistogram inteval_stats;
    cOutVector inteval_vector;
    long double t1, v1;

  protected:
    virtual App_msg *generateMessage(int num);
    virtual void forwardMessage(App_msg *msg);
    virtual void initialize() override;
    virtual void finish() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual int rand_num();
};

Define_Module(App);

void App::initialize()
{
    // Initialize variables
    numSent = 0;
    numReceived = 0;
    curr = simTime();
    prev = simTime();
    SEC = par("sec");
    inteval_stats.setName("inteval_stats");
    inteval_vector.setName("inteval_vector");

    my_idx = getParentModule()->getIndex();
    gen = new cMessage("gen");
    delay = par("time_bwn_msg");
//    scheduleAt(simTime()+delay, gen);
    //=======================================================================
    if(my_idx != 0){
        if(my_idx==5 || my_idx==6 || my_idx==7 || my_idx==8 || my_idx==9){
            scheduleAt(simTime()+SEC, gen);
        }
        else{
            scheduleAt(simTime()+delay, gen);
        }
    }
    //=======================================================================
}

void App::finish()
{
    if(my_idx==0){
        EV << "=============================================================" << endl;
        EV << getFullPath() << " statistic: " << endl;
        EV << "" << endl;
        EV << "Number of received packet: "<< numReceived << endl;
        EV << "Number of packet we send: "<< numSent << endl;
        EV << "" << endl;
        EV << "Arrival interval statistics:  " << endl;
        EV << "Min= "<< inteval_stats.getMin() << "[sec]" << endl;
        EV << "Max= "<< inteval_stats.getMax() << "[sec]" << endl;
        EV << "Mean= "<< inteval_stats.getMean() << "[sec]" << endl;
        EV << "StdDev= "<< inteval_stats.getStddev() << "[sec]" << endl;
        EV << "Variance= "<< inteval_stats.getVariance() << "[sec]" << endl;
        EV << "" << endl;
        inteval_stats.recordAs("Arrival Intervals");
    }
}

void App::handleMessage(cMessage *msg)
{
    int k=0;
    if (msg->isSelfMessage()){
        k = rand_num();
        App_msg *new_msg = generateMessage(k);
        forwardMessage(new_msg);
        delay = par("time_bwn_msg");
        SEC = par("sec");
//        scheduleAt(simTime()+delay, gen);
        //=========================================================================================
        if(my_idx==5 || my_idx==6 || my_idx==7 || my_idx==8 || my_idx==9){
            scheduleAt(simTime()+SEC, gen);
        }
        else{
            scheduleAt(simTime()+delay, gen);
        }
        //=========================================================================================
    }
    else{ //got data message
        numReceived++;

        curr = simTime();
        interval = curr-prev;
        inteval_vector.record(interval.dbl());
        inteval_stats.collect(interval.dbl());
        prev = simTime();

        App_msg *ttmsg = check_and_cast<App_msg *>(msg);
        EV << "HOST " << my_idx <<" GOT DATA MESSAGE: "<< ttmsg->getData() << endl;
        EV << "HOST " << my_idx <<" GOT DATA MESSAGE NUMBER: "<< numReceived << endl;
        delete ttmsg;
        if(numReceived==500){endSimulation();}
    }
}

void App::forwardMessage(App_msg *msg)
{
    numSent++; //increase the total number of message we sent.
    send(msg,"A_IP$o");
}

App_msg *App::generateMessage(int num)
{
    App_msg *msg = new App_msg("APP-Message");
    msg->setByteLength(num);
    return msg;
}

int App::rand_num() // for message length
{
    int k = par("packet_len");
    while((k<26) && (k>1480)){k = par("packet_len");}
    while((k%4)!=0){k++;}
    return k;
}
