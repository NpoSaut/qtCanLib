#include "AppiCan.h"

#include <unistd.h>

AppiCan::AppiCan(LibusbDevice *device, int receiveBufferSize, int sendBufferSize, uint8_t receiveEndpoint, uint8_t sendEndpoint, int maxReceivedFrames)
    : device (device),
      receiveEndpoint (receiveEndpoint),
      sendEndpoint (sendEndpoint),
      receiveBuffer(receiveBufferSize, 0),
      sendBuffer(sendBufferSize, 0),
      receivedFrames(),
      sendCapacity(0),
      usbMutex(),
      capacityMutex()
{
    receiveBuffer.reserve(receiveBufferSize);
    sendBuffer.reserve(sendBufferSize);
    receivedFrames.reserve(maxReceivedFrames);
}

const QVector<CanFrame> &AppiCan::receive()
{
    usbMutex.lock();

    if ( device->receieve(receiveEndpoint, receiveBuffer, 100) )
    {
        int newCapacity;
        parseReceivedBuffer(receiveBuffer, receivedFrames, newCapacity);
        setCapacity(newCapacity);
    }
    else
    {
        receivedFrames.resize(0);
        usleep(1000);
    }

    usbMutex.unlock();
    return receivedFrames;
}

void AppiCan::send(const QVector<CanFrame> &frames)
{
    usbMutex.lock();

    setCapacity(getCapacity() - frames.count());

    fillSendBuffer(frames, sendBuffer);
    device->send(sendEndpoint, sendBuffer, 100);

    usbMutex.unlock();
}

int AppiCan::getCapacity()
{
    capacityMutex.lock();
    int capacity = sendCapacity;
    capacityMutex.unlock();
    return capacity;
}

void AppiCan::setCapacity(int capacity)
{
    capacityMutex.lock();
    sendCapacity = capacity;
    capacityMutex.unlock();
}
