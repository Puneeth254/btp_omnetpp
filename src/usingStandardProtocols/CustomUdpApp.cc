

#include "CustomUdpApp.h"

#include "inet/applications/base/ApplicationPacket_m.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/common/FragmentationTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"

using namespace inet;
using namespace std;

void CustomUdpApp::sendPacket(){

    EV_INFO<<"Overridden sendPacket here\n";

    std::ostringstream str;
    str << packetName << "-" << numSent;
    Packet *packet = new Packet(str.str().c_str());
    if (dontFragment)
        packet->addTag<FragmentationReq>()->setDontFragment(true);
    const auto& payload = makeShared<ApplicationPacket>();

    int minMessageLength = par("minMessageLength").intValue();
    int maxMessageLength = par("maxMessageLength").intValue();
    int randomMessageLength = intuniform(minMessageLength, maxMessageLength);

    EV_INFO<<"Random Message Length is : "<<randomMessageLength<<endl;

    payload->setChunkLength(B(randomMessageLength));
    payload->setSequenceNumber(numSent);
    payload->addTag<CreationTimeTag>()->setCreationTime(simTime());
    packet->insertAtBack(payload);
    L3Address destAddr = chooseDestAddr();
    emit(packetSentSignal, packet);
    socket.sendTo(packet, destAddr, destPort);
    numSent++;
}

Define_Module(CustomUdpApp);
