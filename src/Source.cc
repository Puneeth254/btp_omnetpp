/*
 * Source.cc
 *
 *  Created on: Feb 8, 2025
 *      Author: puneeth
 */


#include <omnetpp.h>

using namespace omnetpp;

class Source : public cSimpleModule {
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Source);

void Source::initialize() {
    for (int i = 0; i < 3; i++) {
        cMessage *msg = new cMessage("Data Packet sent");
        if(strcmp(getName(), "source2") == 0){
            msg->addPar("destIP") = (i + 1) % 3;
        }
        else{
            msg->addPar("destIP") = i;
        }
        scheduleAt(simTime() + i, msg);
    }
}

void Source::handleMessage(cMessage *msg) {
    send(msg, "out");
}
