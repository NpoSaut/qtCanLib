#include "LinuxSocketCanReceiver.h"

#include <unistd.h>

LinuxSocketCanReceiver::LinuxSocketCanReceiver(LinuxSocketCanSocket *socket)
    : socket (socket)
{ }

CanFrame LinuxSocketCanReceiver::receive()
{
    can_frame linuxFrame;
    while ( ::read(socket->number, &linuxFrame, sizeof(struct can_frame)) < 0 );
    return convert (linuxFrame);
}

CanFrame LinuxSocketCanReceiver::convert(const can_frame &socketFrame)
{
    return CanFrame ( socketFrame.can_id&0x1FFF, socketFrame.can_dlc,
                      std::vector<unsigned char> (socketFrame.data, socketFrame.data + socketFrame.can_dlc));
}
