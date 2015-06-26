#include "LinuxSocketCanSender.h"

#include <unistd.h>

LinuxSocketCanSender::LinuxSocketCanSender(LinuxSocketCanSocket *socket)
    : socket (socket)
{ }

void LinuxSocketCanSender::send(const QVector<CanFrame> &frames)
{
    can_frame linuxFrame = convert (frames[0]);
    while ( write(socket->number, &linuxFrame, sizeof(struct can_frame)) < 0 );
}

int LinuxSocketCanSender::getCapacity()
{
    return 1;
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
