#include "candriver.h"
#include "Log/logwriter.h"
namespace CanInternals
{
CanDriver::CanDriver(QObject *parent) :
    QObject(parent)
{
    canEnable = false;
//    start();
}

void CanDriver::start()
{
    driverHandle = CreateFile(name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING,  FILE_ATTRIBUTE_NORMAL, 0);
    DWORD dw = 0x03e43;
    deviceIo(ioctlCanInit, (LPVOID*)&dw, 4, (LPVOID*)&dw, 4);
    canEnable = true;
}

void CanDriver::stop()
{
    deviceIo(ioctlCanClear, NULL, 0, NULL, 0);
    if(driverHandle != INVALID_HANDLE_VALUE)
        CloseHandle(driverHandle);
    canEnable = false;
}

bool CanDriver::deviceIo(DWORD code, LPVOID *inBuffer, DWORD inBufferSize, LPVOID* outBuffer, DWORD outBufferSize)
{
    DWORD br;
    if (driverHandle == INVALID_HANDLE_VALUE)
        return false;
    else
        return DeviceIoControl(driverHandle, code, inBuffer, inBufferSize, outBuffer, outBufferSize, &br, NULL);
}

int CanDriver::getNumberOfMessageInQueue()
{
    int count = 0;
    deviceIo(ioctlCanInQueue, NULL, 0, (LPVOID*) &count, 4);
    return count;
}

std::vector<StructForDrv> CanDriver::receiveMessage()
{
    quint32 count = getNumberOfMessageInQueue();
    std::vector<StructForDrv> outBuf(count);

    if (count != 0)
    {
        byte *data = new byte[count*13];
        WaitForSingleObject(receiveMutex, INFINITE);
        deviceIo(ioctlCanRead, (LPVOID*) &count, 4, (LPVOID*) data, count*13);
        ReleaseMutex(receiveMutex);

        for (int i = 0; i < count; i ++)
        {
            for (int j = 0; j < 13; j ++)
                outBuf[i].rawData[j] = data[i*13+j];
        }

        delete[] data;
    }

    return outBuf;
}

int CanDriver::transmitMessage(TransmitData &td)
{

    int error;
    WaitForSingleObject(transmitMutex, INFINITE);
    if(deviceIo(ioctlCanTransmit, (LPVOID*) &td, sizeof(td), (LPVOID*) &error, 4))
    {
        ReleaseMutex(transmitMutex);
        return 0;
    }
    else if(error == 0)
    {
        ReleaseMutex(transmitMutex);
        return 1;
    }
    else
    {
        ReleaseMutex(transmitMutex);
        return error;
    }
}

void CanDriver::transmitLog(const TransmitData &td)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, FOREGROUND_RED+FOREGROUND_GREEN);
    qDebug("%02x | %02x %02x %02x %02x %02x %02x %02x %02x", (td.id >> 18) * 0x20 + 0x8, td.data[0], td.data[1], td.data[2], td.data[3], td.data[4], td.data[5], td.data[6], td.data[7]);
    SetConsoleTextAttribute(h, FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);
}

void CanDriver::readLog(StructForDrv &cm)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, FOREGROUND_BLUE + FOREGROUND_GREEN);
    qDebug("%02x | %02x %02x %02x %02x %02x %02x %02x %02x", (cm.id >> 18) * 0x20 + 0x8, cm.data[0], cm.data[1], cm.data[2], cm.data[3], cm.data[4], cm.data[5], cm.data[6], cm.data[7]);
    SetConsoleTextAttribute(h, FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);
}

CanDriver::~CanDriver()
{

}


}
