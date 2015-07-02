#ifndef LIBUSBDEVICEFACTORY_H
#define LIBUSBDEVICEFACTORY_H

#include "libusb.h"

#include "LibusbDevice.h"

class LibusbDevice;

// Открывает libusb-сессию при создании объекта и закрывает при уничтожени
// produce (vid, pid) запрашивает нужное устройство
class LibusbDeviceFactory
{
public:
    LibusbDeviceFactory(int debugLevel = 1);
    ~LibusbDeviceFactory();

    LibusbDevice *produce (uint16_t vid, uint16_t pid, int interface);

private:
    libusb_context *context;
    int debugLevel;
};

#endif // LIBUSBDEVICEFACTORY_H
