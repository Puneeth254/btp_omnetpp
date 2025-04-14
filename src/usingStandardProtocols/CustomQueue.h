#ifndef __CUSTOM_QUEUE_H
#define __CUSTOM_QUEUE_H


#include "inet/queueing/queue/PacketQueue.h"
#include "inet/queueing/contract/IPacketSchedulerFunction.h"


#include <omnetpp.h>

using namespace inet;
using namespace inet::queueing;


class CustomQueue : public inet::queueing::PacketQueue{
protected:
    int lastIndex;
    std::map<int, int> lastServedIndex;
//    inet::queueing::IPacketSchedulerFunction *packetSchedulerFunction = nullptr;
//    virtual inet::queueing::IPacketSchedulerFunction *createSchedulerFunction(const char *schedulerClass) const;


public:

    virtual Packet *pullPacket(cGate *gate) override;
    virtual void pushPacket(Packet *packet, cGate *gate) override;

    cPacket* fifo(cPacketQueue& queue);
    cPacket* random(cPacketQueue& queue);
    cPacket* lifo(cPacketQueue& queue);
    cPacket* roundRobin(cPacketQueue& queue);
    cPacket* shortestJobFirst(cPacketQueue& queue);
    cPacket* longestJobFirst(cPacketQueue& queue);
    cPacket* fairQueueing(cPacketQueue& queue);
    cPacket* getScheduledPacket(std::string& scheduler, cPacketQueue& queue);


    void customPushPacket(cPacketQueue& queue, Packet *packet, std::string& scheduler);
    void fifo(cPacketQueue& queue, Packet *packet);
    void random(cPacketQueue& queue, Packet *packet);
    void lifo(cPacketQueue& queue, Packet *packet);
    void roundRobin(cPacketQueue& queue, Packet *packet);
    void shortestJobFirst(cPacketQueue& queue, Packet *packet);
    void longestJobFirst(cPacketQueue& queue, Packet *packet);
    std::multimap<int, Packet*>pktLength;

    CustomQueue(){
        lastIndex = -1;
    }

};

#endif

