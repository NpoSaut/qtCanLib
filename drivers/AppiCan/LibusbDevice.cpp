#include "LibusbDevice.h"

#include <iostream>

LibusbDevice::LibusbDevice(libusb_device_handle *handle, int interface, bool debug)
    : handle (handle), interface (interface), debug (debug), claimed (false)
{
    if (libusb_kernel_driver_active(handle, 0) == 1)
        libusb_detach_kernel_driver(handle, 0);

    claimed = libusb_claim_interface(handle, interface) == 0;
    if (!claimed)
        if (debug)
            std::cerr << "LibUSB: Cannot claim interface " << interface << std::endl;
}

LibusbDevice::~LibusbDevice()
{
    if (claimed)
        if ( libusb_release_interface(handle, interface) != 0 )
            if (debug)
                std::cerr << "Cannot Release Interface " << interface << std::endl;

    libusb_close(handle);
}

bool LibusbDevice::send(uint8_t endpoint, const std::vector<uint8_t> &data, unsigned timeoutMs)
{
    int actual = -1;
    int ret = libusb_bulk_transfer(handle, endpoint & ~LIBUSB_ENDPOINT_IN, const_cast<uint8_t *> (data.data()), data.size(), &actual, timeoutMs);
    bool success = (ret == 0 && data.size() == actual);

    if (!success)
        if (debug)
            std::cerr << "LibUSB: Cannot send to device, error code:" << ret << std::endl;
    return success;
}

bool LibusbDevice::receieve(uint8_t endpoint, std::vector<uint8_t> &data, unsigned timeoutMs)
{
    int actual = -1;
    int ret = libusb_bulk_transfer(handle, endpoint | LIBUSB_ENDPOINT_IN, data.data(), data.size(), &actual, timeoutMs);
    bool success = (ret == 0);

    if (!success)
        if (debug)
            std::cerr << "LibUSB: Cannot receieve from device, error code:" << ret << std::endl;

    data.resize(actual);
    return success;
}

