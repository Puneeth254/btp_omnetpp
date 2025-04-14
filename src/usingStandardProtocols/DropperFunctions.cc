
#include "inet/queueing/function/PacketDropperFunction.h"
#include "inet/queueing/contract/IPacketCollection.h"

using namespace omnetpp;

inet::Packet *selectRandomPacket(inet::queueing::IPacketCollection *collection)
{
    EV_INFO << "Dropping a Random Packet\n";

    return collection->getPacket(collection->getNumPackets() - 1);
}

Register_Packet_Dropper_Function(RandomPacketDropper, selectRandomPacket);
