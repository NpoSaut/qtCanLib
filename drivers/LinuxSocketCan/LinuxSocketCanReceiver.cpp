#include "LinuxSocketCanReceiver.h"

#include <unistd.h>

LinuxSocketCanReceiver::LinuxSocketCanReceiver(LinuxSocketCanSocket *socket, int capacity)
    : socket (socket),
      frames ()
{
    frames.reserve(capacity);
}

const QVector<CanFrame> &LinuxSocketCanReceiver::receive()
{
    frames.resize(0);

    can_frame linuxFrame;
    if ( ::read(socket->number, &linuxFrame, sizeof(struct can_frame)) >= 0 )
        frames.append(convert (linuxFrame));

    return frames;
}

CanFrame LinuxSocketCanReceiver::convert(const can_frame &socketFrame)
{
    return CanFrame ( socketFrame.can_id&0x1FFF, socketFrame.can_dlc,
                      std::vector<unsigned char> (socketFrame.data, socketFrame.data + socketFrame.can_dlc));
}
