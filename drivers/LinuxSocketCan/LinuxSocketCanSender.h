#ifndef LINUXSOCKETCANSENDER_H
#define LINUXSOCKETCANSENDER_H

extern "C"
{
#include "cSocketCanLib/src/SocketCanLib.h"
}

#include "../IBlockedSender.h"
#include "LinuxSocketCanSocket.h"

class LinuxSocketCanSender : public IBlockedSender
{
public:
    LinuxSocketCanSender(LinuxSocketCanSocket *socket);

    virtual void send (const QVector<CanFrame> &frames);
    virtual int getCapacity ();

private:
    LinuxSocketCanSocket *socket;
    QVector<can_frame> driverFrames;
    can_frame convert (const CanFrame &canFrame);
};

#endif // LINUXSOCKETCANSENDER_H
