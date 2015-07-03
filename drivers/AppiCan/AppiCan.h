#ifndef APPICAN_H
#define APPICAN_H

#include <QMutex>

#include "../IBlockedReceiver.h"
#include "../IBlockedSender.h"
#include "LibusbDevice.h"

// Позволяет потокобезопасно принимать, отправлять и получать ёмкость буффера отправки АППИ
// Работу по кодированию/декодированию возлагает на наследников
class AppiCan : public IBlockedReceiver, public IBlockedSender
{
public:
    virtual const QVector<CanFrame> &receive ();
    virtual void send (const QVector<CanFrame> &frames);
    virtual int getCapacity ();

protected:
    AppiCan(LibusbDevice *device, int receiveBufferSize, int sendBufferSize, uint8_t receiveEndpoint, uint8_t sendEndpoint, int maxReceivedFrames);

    virtual void parseReceivedBuffer(const std::vector<uint8_t> &buffer, QVector<CanFrame> &frames, int &sendCapacity) = 0;
    virtual void fillSendBuffer(const QVector<CanFrame> &frames, std::vector<uint8_t> &buffer) = 0;

private:
    void setCapacity (int capacity);

    LibusbDevice *device;
    const uint8_t receiveEndpoint, sendEndpoint;
    std::vector<uint8_t> receiveBuffer, sendBuffer;
    QVector<CanFrame> receivedFrames;
    int sendCapacity;

    QMutex usbMutex, capacityMutex;
};

#endif // APPICAN_H
