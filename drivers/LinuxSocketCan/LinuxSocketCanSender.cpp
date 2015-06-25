#include "LinuxSocketCanSender.h"

#include <unistd.h>

LinuxSocketCanSender::LinuxSocketCanSender(LinuxSocketCanSocket *socket)
    : socket (socket)
{ }

void LinuxSocketCanSender::send(CanFrame frame)
{
    can_frame linuxFrame = convert (frame);
    while ( write(socket->number, &linuxFrame, sizeof(struct can_frame)) < 0 );
}

can_frame LinuxSocketCanSender::convert(const CanFrame &canFrame)
{
    can_frame frame;

    frame.can_id = canFrame.getId();
    frame.can_dlc = canFrame.getData().size();

    unsigned i = 0;
    for( ; i < canFrame.getData().size (); i ++ )
        frame.data[i] = canFrame.getData()[i];
    for ( ; i < 8; i ++ )
        frame.data[i] = 0;

    return frame;
}
