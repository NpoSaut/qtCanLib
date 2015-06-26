#ifndef LINUXSOCKETCANRECEIVER_H
#define LINUXSOCKETCANRECEIVER_H

#include <sys/socket.h> // for sa_familty_t in linux/can.h
#include <linux/can.h>

#include "../IBlockedReceiver.h"
#include "LinuxSocketCanSocket.h"

class LinuxSocketCanReceiver : public IBlockedReceiver
{
public:
    LinuxSocketCanReceiver(LinuxSocketCanSocket *socket, int capacity = 1);

    virtual const QVector<CanFrame> &receive ();

private:
    LinuxSocketCanSocket *socket;
    QVector<CanFrame> frames;
    CanFrame convert (const struct can_frame &socketFrame);
};

#endif // LINUXSOCKETCANRECEIVER_H
