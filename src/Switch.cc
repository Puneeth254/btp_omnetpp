/*
 * Switch.cc
 *
 *  Created on: Feb 8, 2025
 *      Author: puneeth
 */


#include <omnetpp.h>

using namespace omnetpp;

class Switch : public cSimpleModule {
public:
    int pktcnt;

    Switch(){
        pktcnt = 0;
    }

protected:
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Switch);

void Switch::handleMessage(cMessage *msg) {
    int destIP = msg->par("destIP").longValue();
    if (pktcnt < par("maxPackets").intValue() && destIP >= 0 && destIP < gateSize("out")) {
        send(msg, "out", destIP);
        pktcnt++;
    } else {
        delete msg;  // Drop invalid packets
    }
}
