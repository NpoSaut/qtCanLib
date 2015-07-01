#include "LibusbDevice.h"

#include <iostream>

LibusbDevice::LibusbDevice(libusb_device_handle *handle, bool debug)
    : handle (handle), debug (debug), vid (-1), pid (-1), claimed (false)
{
    libusb_device_descriptor *desc;
    if ( libusb_get_device_descriptor( libusb_get_device(handle), desc ) )
    {
        vid = desc->idVendor;
        pid = desc->idProduct;
    }

    if (libusb_kernel_driver_active(handle, 0) == 1)
        libusb_detach_kernel_driver(dev_handle, 0);

    claimed = libusb_claim_interface(dev_handle, 0) < 0;
    if (!claimed)
        if (debug)
            std::cerr << "LibUSB: Cannot Claim Interface 0 for device ("
                      << vid << ", " << pid << ")" << endl;
}

LibusbDevice::~LibusbDevice()
{
    if (claimed)
        if ( libusb_release_interface(handle, 0) != 0 )
            if (debug)
                std::cerr << "Cannot Release Interface 0 for device ("
                          << vid << ", " << pid << ")" << endl;

    libusb_close(handle);
}

bool LibusbDevice::send(uint8_t endpoint, const std::vector<uint8_t> &data, unsigned timeoutMs)
{
    int actual = -1;
    int ret = libusb_bulk_transfer(handle, endpoint & LIBUSB_ENDPOINT_OUT, data.data(), data.size(), actual, timeoutMs);
    bool success = (ret == 0 && data.size() == actual);

    if (!success)
        if (debug)
            std::cerr << "LibUSB: Cannot send to device ("
                      << vid << ", " << pid << "), error code:" << ret << endl;
    return success;
}

bool LibusbDevice::receieve(uint8_t endpoint, std::vector<uint8_t> &data, unsigned timeoutMs)
{
    int actual = -1;
    int ret = libusb_bulk_transfer(handle, endpoint | LIBUSB_ENDPOINT_IN, data.data(), data.size(), actual, timeoutMs);
    bool success = (ret == 0);

    if (!success)
        if (debug)
            std::cerr << "LibUSB: Cannot receieve from device ("
                      << vid << ", " << pid << "), error code:" << ret << endl;

    data.resize(actual);
    return success;
}

