
#include "CustomQueue.h"


#include "inet/common/ModuleAccess.h"
#include "inet/common/PacketEventTag.h"
#include "inet/common/Simsignals.h"
#include "inet/common/TimeTag.h"
#include "inet/queueing/function/PacketComparatorFunction.h"
#include "inet/queueing/function/PacketDropperFunction.h"

#include <cstdlib>
#include <ctime>

using namespace inet;
using namespace inet::queueing;


//IPacketSchedulerFunction *CustomQueue::createSchedulerFunction(const char *schedulerClass) const
//{
//    if (strlen(schedulerClass) == 0)
//        return nullptr;
//    else
//        return check_and_cast<IPacketSchedulerFunction *>(createOne(schedulerClass));
//}

cPacket* CustomQueue::fifo(cPacketQueue& queue){
    return queue.front();
}

cPacket* CustomQueue::random(cPacketQueue& queue){
    if (queue.isEmpty()) {
        return nullptr;
    }

    int index = intuniform(0, queue.getLength() - 1);

    EV_INFO << "Pulling packet at index : "<<index<<std::endl;
    return queue.get(index);
}

cPacket* CustomQueue::lifo(cPacketQueue& queue) {
    return queue.back();
}

cPacket* CustomQueue::roundRobin(cPacketQueue& queue) {
    if (queue.isEmpty()) {
        return nullptr;
    }

    lastIndex = (lastIndex + 1) % queue.getLength();
    EV_INFO << "Pulling packet at index : " << lastIndex << std::endl;
    return queue.get(lastIndex);
}

cPacket* CustomQueue::shortestJobFirst(cPacketQueue& queue) {
    if (queue.isEmpty()) {
        return nullptr;
    }

    cPacket* shortestPacket = queue.front();
    for (int i = 1; i < queue.getLength(); i++) {
        if (queue.get(i)->getByteLength() < shortestPacket->getByteLength()) {
            shortestPacket = queue.get(i);
        }
    }

    EV_INFO << "Pulling shortest packet with length : " << shortestPacket->getByteLength()<<std::endl;

//    auto it = pktLength.begin();
//    Packet* shortestPacket = it->second;
//
//    pktLength.erase(it);
//
//    EV_INFO << "Pulling shortest packet with length : " << shortestPacket->getByteLength()<<std::endl;

    return shortestPacket;
}

cPacket* CustomQueue::longestJobFirst(cPacketQueue& queue) {
    if (queue.isEmpty()) {
        return nullptr;
    }

    cPacket* longestPacket = queue.front();
    for (int i = 1; i < queue.getLength(); i++) {
        if (queue.get(i)->getByteLength() > longestPacket->getByteLength()) {
            longestPacket = queue.get(i);
        }
    }

//    auto it = (--pktLength.end());
//    Packet* longestPacket = it->second;
//
//    pktLength.erase(it);

    EV_INFO << "Pulling longest packet with length : " << longestPacket->getByteLength()<<std::endl;
    return longestPacket;
}

cPacket* CustomQueue::fairQueueing(cPacketQueue& queue) {
    if (queue.isEmpty()) {
        return nullptr;
    }

    std::map<int, std::vector<cPacket*>> flowBuckets;

    // Group packets by source module ID
    for (int i = 0; i < queue.getLength(); i++) {
        cPacket* pkt = queue.get(i);
        int sourceId = pkt->getSenderModuleId();  // Get the source module ID
        flowBuckets[sourceId].push_back(pkt);
    }

    // Serve from the flow (source) that was least recently served
    for (auto& [sourceId, packets] : flowBuckets) {
        int& index = lastServedIndex[sourceId];  // Track last served index per source
        index = (index + 1) % packets.size();
        return packets[index];
    }

    return queue.front();  // Default (should never reach here)
}


cPacket* CustomQueue::getScheduledPacket(std::string& scheduler, cPacketQueue& queue){
    if(scheduler == "fifo"){
        return fifo(queue);
    }
    else if(scheduler == "random"){
        return random(queue);
    }
    else if(scheduler == "lifo"){
        return lifo(queue);
    }
    else if(scheduler == "rr"){
        return roundRobin(queue);
    }
    else if(scheduler == "sjf"){
        return shortestJobFirst(queue);
    }
    else if(scheduler == "ljf"){
        return longestJobFirst(queue);
    }
    else if(scheduler == "fairQueuing"){
        return fairQueueing(queue);
    }
    else{
        EV_INFO<<"No such scheduler exists\n";
    }
    return nullptr;
}

Packet *CustomQueue::pullPacket(cGate *gate)
{
    Enter_Method("pullPacket");

    std::string scheduler = par("scheduler").stdstringValue();

    EV_INFO << "Scheduler is "<< scheduler << std::endl;

    cPacket* pkt = getScheduledPacket(scheduler, queue);

    auto packet = check_and_cast<Packet *>(pkt);

    EV_INFO << "Pulling packet" << EV_FIELD(packet) << EV_ENDL;
    if (buffer != nullptr) {
        queue.remove(packet);
        buffer->removePacket(packet);
    }
    else
        queue.remove(packet);
    auto queueingTime = simTime() - packet->getArrivalTime();
    auto packetEvent = new PacketQueuedEvent();
    packetEvent->setQueuePacketLength(getNumPackets());
    packetEvent->setQueueDataLength(getTotalLength());
    insertPacketEvent(this, packet, PEK_QUEUED, queueingTime, packetEvent);
    increaseTimeTag<QueueingTimeTag>(packet, queueingTime, queueingTime);
    emit(packetPulledSignal, packet);
    animatePullPacket(packet, outputGate);
    updateDisplayString();
    return packet;
}

void CustomQueue::fifo(cPacketQueue& queue, Packet *packet){
    queue.insert(packet);
}

void CustomQueue::random(cPacketQueue& queue, Packet *packet){
    queue.insert(packet);
}

void CustomQueue::lifo(cPacketQueue& queue, Packet *packet){
    queue.insert(packet);
}

void CustomQueue::roundRobin(cPacketQueue& queue, Packet *packet){
    queue.insert(packet);
}

void CustomQueue::shortestJobFirst(cPacketQueue& queue, Packet *packet){
    queue.insert(packet);
    pktLength.insert({packet->getByteLength(), packet});
}

void CustomQueue::longestJobFirst(cPacketQueue& queue, Packet *packet){
    queue.insert(packet);
    pktLength.insert({packet->getByteLength(), packet});
}

void CustomQueue::customPushPacket(cPacketQueue& queue, Packet *packet, std::string& scheduler){
    if(scheduler == "fifo"){
        fifo(queue, packet);
    }
    else if(scheduler == "random"){
        random(queue, packet);
    }
    else if(scheduler == "lifo"){
        lifo(queue, packet);
    }
    else if(scheduler == "rr"){
        roundRobin(queue, packet);
    }
    else if(scheduler == "sjf"){
        shortestJobFirst(queue, packet);
    }
    else if(scheduler == "ljf"){
        longestJobFirst(queue, packet);
    }
//    else if(scheduler == "fairQueuing"){
//        return fairQueueing(queue);
//    }
    else{
        EV_INFO<<"No such scheduler exists\n";
    }
}

void CustomQueue::pushPacket(Packet *packet, cGate *gate){
    Enter_Method("pushPacket");
    take(packet);
    cNamedObject packetPushStartedDetails("atomicOperationStarted");
    emit(packetPushStartedSignal, packet, &packetPushStartedDetails);
    EV_INFO << "Pushing packet" << EV_FIELD(packet) << EV_ENDL;

    std::string scheduler = par("scheduler").stdstringValue();

    EV_INFO << "Scheduler is "<< scheduler << std::endl;

//    customPushPacket(queue, packet, scheduler);
    queue.insert(packet);
    if (buffer != nullptr)
        buffer->addPacket(packet);
    else if (packetDropperFunction != nullptr) {
        while (isOverloaded()) {
            auto packet = packetDropperFunction->selectPacket(this);
            EV_INFO << "Dropping packet" << EV_FIELD(packet) << EV_ENDL;
            queue.remove(packet);
            dropPacket(packet, QUEUE_OVERFLOW);
        }
    }
    ASSERT(!isOverloaded());
    if (collector != nullptr && getNumPackets() != 0)
        collector->handleCanPullPacketChanged(outputGate->getPathEndGate());
    cNamedObject packetPushEndedDetails("atomicOperationEnded");
    emit(packetPushEndedSignal, nullptr, &packetPushEndedDetails);
    updateDisplayString();
}

Define_Module(CustomQueue);
