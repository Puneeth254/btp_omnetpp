#ifndef __INET_CUSTOMUDPAPP_H
#define __INET_CUSTOMUDPAPP_H


#include "inet/applications/udpapp/UdpBasicApp.h"


using namespace inet;

class CustomUdpApp : public UdpBasicApp{
public:
    virtual void sendPacket() override;
};


#endif
