#ifndef APPIBLOCKCAN1_H
#define APPIBLOCKCAN1_H

#include "AppiCan.h"

class AppiBlockCan1 : public AppiCan
{
public:
    AppiBlockCan1(LibusbDeviceFactory *usbFactory);
    ~AppiBlockCan1();

private:
    virtual void parseReceivedBuffer(const std::vector<uint8_t> &buffer, QVector<CanFrame> &frames, int &sendCapacity);
    virtual void fillSendBuffer(const QVector<CanFrame> &frames, std::vector<uint8_t> &buffer);

    LibusbDevice *device;
};

#endif // APPIBLOCKCAN1_H
