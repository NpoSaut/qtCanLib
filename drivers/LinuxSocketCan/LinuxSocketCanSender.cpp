#include "LinuxSocketCanSender.h"

#include <unistd.h>

LinuxSocketCanSender::LinuxSocketCanSender(LinuxSocketCanSocket *socket)
    : socket (socket),
      driverFrames ()
{
    driverFrames.reserve(socket->txCapacity);
}

void LinuxSocketCanSender::send(const QVector<CanFrame> &frames)
{
    for (int i = 0; i < frames.count(); i ++)
        driverFrames[i] = convert (frames[i]);

    while ( SocketWrite(socket->number, driverFrames.data(), frames.count()) < 0 );
}

int LinuxSocketCanSender::getCapacity()
{
    return socket->txCapacity;
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
