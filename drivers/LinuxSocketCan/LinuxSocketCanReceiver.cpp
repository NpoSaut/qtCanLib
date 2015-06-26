#include "LinuxSocketCanReceiver.h"

LinuxSocketCanReceiver::LinuxSocketCanReceiver(LinuxSocketCanSocket *socket)
    : socket (socket),
      outputFrames (),
      driverFrames ()
{
    outputFrames.reserve(socket->rxCapacity);
    driverFrames.reserve(socket->rxCapacity);
}

const QVector<CanFrame> &LinuxSocketCanReceiver::receive()
{
    int readNumber = SocketRead(socket->number, driverFrames.data(), socket->rxCapacity, 1000);
    outputFrames.resize(readNumber);

    for (int i = 0; i < readNumber; i ++)
        outputFrames[i] = convert(driverFrames[i].Frame);

    return outputFrames;
}

CanFrame LinuxSocketCanReceiver::convert(const can_frame &socketFrame)
{
    return CanFrame ( socketFrame.can_id&0x1FFF, socketFrame.can_dlc,
                      std::vector<unsigned char> (socketFrame.data, socketFrame.data + socketFrame.can_dlc));
}
