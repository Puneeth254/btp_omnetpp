
#include "inet/queueing/function/PacketComparatorFunction.h"
//#include "inet/node/base/NodeBase.h"
//#include "inet/queueing/queue/PacketQueue.h"
//#include "inet/queueing/contract/IPacketCollection.h"

using namespace inet;

int fifoComparator(Packet *packet1, Packet *packet2)
{
    EV_INFO <<"FIFO Packet Comparator "<<std::endl;
    return 1;
}

Register_Packet_Comparator_Function(fifoPacketComparator, fifoComparator);



int lifoComparator(Packet *packet1, Packet *packet2)
{
    EV_INFO <<"LIFO Packet Comparator "<<std::endl;
    return -1;
}

Register_Packet_Comparator_Function(lifoPacketComparator, lifoComparator);


int getRandomNumber(int min, int max) {
//    std::srand(std::time(nullptr));
//    return min + (std::rand() % (max - min + 1));
    return 1;
}

int randomComparator(Packet *packet1, Packet *packet2)
{
    return 1;
}
Register_Packet_Comparator_Function(randomPacketComparator, randomComparator);

//static int rrCounter = 0;
//int rrComparator(Packet *packet1, Packet *packet2)
//{
//    return (rrCounter++ % 2) ? 1 : -1;
//}
//
//Register_Packet_Comparator_Function(rrPacketComparator, rrComparator);




int shortestPacket(Packet *packet1, Packet *packet2)
{
    int dif =  (packet1->getByteLength() - packet2->getByteLength());

    EV_INFO <<"Shortest Packet Comparator "<<dif<<std::endl;

    if(dif == 0){
        return 0;
    }
    else if(dif > 0){
        return 1;
    }
    return -1;
}

Register_Packet_Comparator_Function(shortestPacketComparator, shortestPacket);




int longestPacket(Packet *packet1, Packet *packet2)
{
    int dif = (packet2->getByteLength() - packet1->getByteLength());

    EV_INFO <<"Longest Packet Comparator "<<dif<<std::endl;

    if(dif == 0){
        return 0;
    }
    else if(dif > 0){
        return 1;
    }
    return -1;
}

Register_Packet_Comparator_Function(longestPacketComparator, longestPacket);
