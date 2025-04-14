#include "CustomNetworkLayer.h"

#include <stdlib.h>
#include <string.h>

#include "inet/common/checksum/TcpIpChecksum.h"
#include "inet/common/INETUtils.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/LayeredProtocolBase.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Message.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/ProtocolUtils.h"
#include "inet/common/socket/SocketTag_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/networklayer/arp/ipv4/ArpPacket_m.h"
#include "inet/networklayer/common/DscpTag_m.h"
#include "inet/networklayer/common/EcnTag_m.h"
#include "inet/networklayer/common/FragmentationTag_m.h"
#include "inet/networklayer/common/HopLimitTag_m.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/networklayer/common/L3Tools.h"
#include "inet/networklayer/common/MulticastTag_m.h"
#include "inet/networklayer/common/NextHopAddressTag_m.h"
#include "inet/networklayer/common/TosTag_m.h"
#include "inet/networklayer/contract/IArp.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/contract/ipv4/Ipv4SocketCommand_m.h"
#include "inet/networklayer/ipv4/IIpv4RoutingTable.h"
#include "inet/networklayer/ipv4/IcmpHeader_m.h"
#include "inet/networklayer/ipv4/Ipv4Header_m.h"
#include "inet/networklayer/ipv4/Ipv4InterfaceData.h"
#include "inet/networklayer/ipv4/Ipv4OptionsTag_m.h"

using namespace inet;

//void CustomNetworkLayer::initialize(int stage) {
////    if (stage == inet::INITSTAGE_NETWORK_LAYER) {
////
////    }
//    NetworkProtocolBase::initialize(inet::INITSTAGE_NETWORK_LAYER);
//    EV_INFO << "Custom Router Initialized" << std::endl;
//}
//
//void CustomNetworkLayer::handleIncomingDatagram(inet::Packet *packet)
//{
//    EV_INFO << "Handling Incoming Datagram\n";
//}
//
//void CustomNetworkLayer::handleUpperCommand(omnetpp::cMessage *msg) {
//    NetworkProtocolBase::handleUpperCommand(msg);
//}
//
//void CustomNetworkLayer::sendUp(omnetpp::cMessage *message) {
//    NetworkProtocolBase::sendUp(message);
//}
//
//
//void CustomNetworkLayer::sendDown(omnetpp::cMessage *message, int interfaceId) {
//    NetworkProtocolBase::sendDown(message, interfaceId);
//}
//
//const inet::Protocol& CustomNetworkLayer::getProtocol() const{
//    return inet::Protocol::ipv4;
//}
//
//
//void CustomNetworkLayer::handleStartOperation(inet::LifecycleOperation *operation) {
//    EV_INFO << "Starting Custom Router" << std::endl;
//}
//
//void CustomNetworkLayer::handleStopOperation(inet::LifecycleOperation *operation) {
//    EV_INFO << "Stopping Custom Router" << std::endl;
//}
//
//void CustomNetworkLayer::handleCrashOperation(inet::LifecycleOperation *operation) {
//    EV_INFO << "Custom Router Crashed!" << std::endl;
//}
//
//void CustomNetworkLayer::handleRegisterService(const inet::Protocol& protocol, inet::cGate *gate, inet::ServicePrimitive servicePrimitive) {
//    NetworkProtocolBase::handleRegisterService(protocol, gate, servicePrimitive);
//}
//
//
//void CustomNetworkLayer::handleRegisterProtocol(const inet::Protocol& protocol, inet::cGate *gate, inet::ServicePrimitive servicePrimitive) {
//    NetworkProtocolBase::handleRegisterProtocol(protocol, gate, servicePrimitive);
//}


void CustomNetworkLayer::initialize(int stage){
    Ipv4::initialize(stage);
}


CustomNetworkLayer::~CustomNetworkLayer() {
    // Destructor logic if needed
    EV_INFO << "CustomNetworkLayer Destructor Called!" << endl;
}

void CustomNetworkLayer::sendDatagramToOutput(inet::Packet *packet){

    EV_INFO << "Inside Overridden Function\n";
    const NetworkInterface *ie = ift->getInterfaceById(packet->getTag<InterfaceReq>()->getInterfaceId());
    auto nextHopAddressReq = packet->removeTag<NextHopAddressReq>();
    Ipv4Address nextHopAddr = nextHopAddressReq->getNextHopAddress().toIpv4();
    if (!ie->isBroadcast() || ie->getMacAddress().isUnspecified()) // we can't do ARP
        sendPacketToNIC(packet);
    else {
        MacAddress nextHopMacAddr = resolveNextHopMacAddress(packet, nextHopAddr, ie);
        if (nextHopMacAddr.isUnspecified()) {
            EV_INFO << "Pending " << packet << " to ARP resolution.\n";
            pendingPackets[nextHopAddr].insert(packet);
        }
        else {
            ASSERT2(!containsKey(pendingPackets, nextHopAddr), "Ipv4-ARP error: nextHopAddr found in ARP table, but Ipv4 queue for nextHopAddr not empty");
            packet->addTagIfAbsent<MacAddressReq>()->setDestAddress(nextHopMacAddr);
            EV_INFO << "Overriding Here\n";
            sendPacketToNIC(packet);
        }
    }
}


Define_Module(CustomNetworkLayer);

