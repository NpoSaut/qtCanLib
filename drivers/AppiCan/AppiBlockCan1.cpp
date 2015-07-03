#include "AppiBlockCan1.h"

AppiBlockCan1::AppiBlockCan1(LibusbDeviceFactory *usbFactory)
    : AppiCan (
          device = usbFactory->produce(0x1992, 0x1972, 1),
          2048,
          2048,
          2,
          1,
          45)
{
}

AppiBlockCan1::~AppiBlockCan1()
{
    delete device;
}

void AppiBlockCan1::parseReceivedBuffer(const std::vector<uint8_t> &buffer, QVector<CanFrame> &frames, int &sendCapacity)
{
    frames.resize( buffer[6] );
    sendCapacity = 50 - (int (buffer[18]) << 8 ) + buffer[17];

    auto i = buffer.begin() + 24;
    for (auto &f : frames)
    {
        int id = (int (*i++) << 8) + *i++;
        int len = id & 0xF;
        id = id >> 4;
        std::vector<unsigned char> data (i, i+8); i+=8;
        f = CanFrame (id, len, data);
    }
}

void AppiBlockCan1::fillSendBuffer(const QVector<CanFrame> &frames, std::vector<uint8_t> &buffer)
{
    buffer[0] = 2;
    buffer[1] = 2; // CAN1
    buffer[3] = frames.count();

    auto i = buffer.begin() + 10;
    for (auto &f : frames)
    {
        *i++ = uint8_t (f.getDescriptor() >> 8);
        *i++ = uint8_t (f.getDescriptor());
        std::copy(f.getData().begin(), f.getData().end(), i);
        i += 8;
    }
}
