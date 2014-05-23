#ifndef SOCKETCAN_H
#define SOCKETCAN_H

#ifdef LIB_SOCKET_CAN

#include "can.h"

class SocketCan : public Can
{
public:
    explicit SocketCan(QObject *parent = 0);
protected:
    void onTransmitMessage(CanFrame frame);
    void onGetMessage(CanFrame frame);
};

#endif // LIB_SOCKET_CAN

#endif // SOCKETCAN_H
