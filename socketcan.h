#ifndef SOCKETCAN_H
#define SOCKETCAN_H

#include "can.h"

class SocketCan : public Can
{
public:
    explicit SocketCan(QObject *parent = 0);
protected:
    void onTransmitMessage(CanFrame frame);
    void onGetMessage(CanFrame frame);
};


#endif // SOCKETCAN_H
