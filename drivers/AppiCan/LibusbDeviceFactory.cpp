#include "LibusbDeviceFactory.h"

#include <iostream>
using namespace std;

LibusbDeviceFactory::LibusbDeviceFactory(int debugLevel)
    : debugLevel (debugLevel)
{
    if ( libusb_init(context) >= 0 )
        libusb_set_debug(context, debugLevel);
    else if (debugLevel > 0)
        cerr << "LibUSB init error" << endl;
}

LibusbDeviceFactory::~LibusbDeviceFactory()
{
    libusb_exit(context);
}

LibusbDevice *LibusbDeviceFactory::produce(uint16_t vid, uint16_t pid)
{
    libusb_device **devs;
    ssize_t number = libusb_get_device_list(context, devs);
    if (number < 0)
    {
        if (debugLevel > 0)
            cerr << "LibUSB: Get device list error" << endl;
        return nullptr;
    }

    auto handle = libusb_open_device_with_vid_pid(context, vid, pid);
    libusb_free_device_list(devs, 1); // free and unref
    if (handle == NULL)
    {
        if (debugLevel > 0)
            cerr << "LibUSB: Cannot open device (" << vid << "," << pid << ")" << endl;
        return nullptr;
    }
    else
        return new LibusbDevice (handle);
}
