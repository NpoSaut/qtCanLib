#ifndef LINUXSOCKETCANSENDER_H
#define LINUXSOCKETCANSENDER_H

#include <sys/socket.h> // for sa_familty_t in linux/can.h
#include <linux/can.h>

#include "../IBlockedSender.h"
#include "LinuxSocketCanSocket.h"

class LinuxSocketCanSender : public IBlockedSender
{
public:
    LinuxSocketCanSender(LinuxSocketCanSocket *socket);

    virtual void send (QVector<CanFrame> frames);
    virtual int getCapacity ();

private:
    LinuxSocketCanSocket *socket;

    can_frame convert (const CanFrame &canFrame);
};

#endif // LINUXSOCKETCANSENDER_H
