/*
 * Destination.cc
 *
 *  Created on: Feb 8, 2025
 *      Author: puneeth
 */


#include <omnetpp.h>

using namespace omnetpp;

class Destination : public cSimpleModule {
protected:
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Destination);

void Destination::handleMessage(cMessage *msg) {
    EV << getFullName() << " received message: " << msg->getName() << endl;
    delete msg;
}
