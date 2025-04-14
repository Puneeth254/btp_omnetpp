#include <omnetpp.h>

using namespace omnetpp;

class Node : public cSimpleModule {
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Node);

void Node::initialize() {
    // Node 1 sends the first message
    if (strcmp(getName(), "node1") == 0) {
        cMessage *msg = new cMessage("Hello1");
        send(msg, "out");
        EV << "Node 1 sent a message" << endl;
    }
//    if (strcmp(getName(), "node2") == 0) {
//            cMessage *msg = new cMessage("Hello2");
//            send(msg, "out");
//            EV << "Node 2 sent a message" << endl;
//    }
}

void Node::handleMessage(cMessage *msg) {
    // Forward the message to the next node
    EV << "Node " << getName() << " received a message" << endl;
    if (strcmp(getName(), "node2") == 0) {
        cMessage *msg = new cMessage("Hello2");
        send(msg, "out");
        EV << "Node 2 sent a message" << endl;
    }
    else if (strcmp(getName(), "node3") == 0) {
        cMessage *msg = new cMessage("Hello3");
        send(msg, "out");
        EV << "Node 3 sent a message" << endl;
    }
    else if (strcmp(getName(), "node1") == 0) {
        cMessage *msg = new cMessage("Hello1");
        send(msg, "out");
        EV << "Node 1 sent a message" << endl;
    }
}
