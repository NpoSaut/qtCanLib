#ifndef LIBUSBDEVICE_H
#define LIBUSBDEVICE_H

#include <vector>
#include "libusb.h"

#include "LibusbDeviceFactory.h"

// При создании (создаётся фабрикой) клеймит интерфейс
// Позволяет отправлять и принимать в синхрнном режиме
class LibusbDevice
{
public:
    ~LibusbDevice ();

    bool send (uint8_t endpoint, const std::vector<uint8_t> &data, unsigned timeoutMs = 0);
    bool receieve (uint8_t endpoint, std::vector<uint8_t> &data, unsigned timeoutMs = 0);

private:
    LibusbDevice(libusb_device_handle *handle, bool debug);

    libusb_device_handle *handle;
    bool debug;
    int vid, pid;
    bool claimed;

friend class LibusbDeviceFactory;
};

#endif // LIBUSBDEVICE_H
