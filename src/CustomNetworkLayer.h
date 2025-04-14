#ifndef __CUSTOM_ROUTER_H
#define __CUSTOM_ROUTER_H

//#include "inet/networklayer/base/NetworkProtocolBase.h"
#include "inet/networklayer/ipv4/Ipv4.h"
#include "inet/queueing/queue/PacketQueue.h"
//#include "inet/common/packet/Packet.h"
#include <omnetpp.h>

//class CustomNetworkLayer : public inet::NetworkProtocolBase, public inet::NetfilterBase {
//  protected:
//    virtual void initialize(int stage) override;
//    virtual void handleUpperCommand(omnetpp::cMessage *msg) override;
//    virtual void sendUp(omnetpp::cMessage *message) override;
//    virtual void sendDown(omnetpp::cMessage *message, int interfaceId = -1) override;
//    virtual const inet::Protocol& getProtocol() const override;
//
//    virtual void handleStartOperation(inet::LifecycleOperation *operation) override;
//    virtual void handleStopOperation(inet::LifecycleOperation *operation) override;
//    virtual void handleCrashOperation(inet::LifecycleOperation *operation) override;
//    void handleIncomingDatagram(inet::Packet *packet);
//
//  public:
//    CustomNetworkLayer() {}
//    virtual ~CustomNetworkLayer() {}
//
//    virtual void handleRegisterService(const inet::Protocol& protocol, inet::cGate *gate, inet::ServicePrimitive servicePrimitive) override;
//    virtual void handleRegisterProtocol(const inet::Protocol& protocol, inet::cGate *gate, inet::ServicePrimitive servicePrimitive) override;
//
//    void dropQueuedDatagram(const inet::Packet *datagram) override {
//        EV_INFO << "Dropping datagram: " << datagram->getName() << "\n";
//        delete datagram;  // Free memory
//    }
//
//    void reinjectQueuedDatagram(const inet::Packet *datagram) override {
//        EV_INFO << "Reinjecting datagram: " << datagram->getName() << "\n";
//        // In a real implementation, this would be reprocessed by the network stack
//        send(datagram->dup(), "networkOut");  // Forward to network
//    }
//};

class CustomNetworkLayer : public inet::Ipv4{
public:
    inet::queueing::PacketQueue packetQueue;
    CustomNetworkLayer(){
        EV_INFO << "CustomNetworkLayer Constructor Called!" << std::endl;
    }
    ~CustomNetworkLayer() override;

    virtual void initialize(int stage) override;


protected:

    virtual void sendDatagramToOutput(inet::Packet *packet) override;
};

#endif
