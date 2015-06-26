#ifndef LINUXSOCKETCANRECEIVER_H
#define LINUXSOCKETCANRECEIVER_H

extern "C"
{
#include "cSocketCanLib/src/SocketCanLib.h"
}

#include "../IBlockedReceiver.h"
#include "LinuxSocketCanSocket.h"

class LinuxSocketCanReceiver : public IBlockedReceiver
{
public:
    LinuxSocketCanReceiver(LinuxSocketCanSocket *socket);

    virtual const QVector<CanFrame> &receive ();

private:
    LinuxSocketCanSocket *socket;
    QVector<CanFrame> outputFrames;
    QVector<FrameBag> driverFrames;
    CanFrame convert (const struct can_frame &socketFrame);
};

#endif // LINUXSOCKETCANRECEIVER_H
