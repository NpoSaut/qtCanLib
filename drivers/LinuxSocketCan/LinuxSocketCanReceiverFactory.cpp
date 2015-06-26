#include "LinuxSocketCanReceiverFactory.h"

#include "LinuxSocketCanSocketFactory.h"
#include "LinuxSocketCanReceiver.h"

LinuxSocketCanReceiverFactory::LinuxSocketCanReceiverFactory(QString interface)
    : interface (interface)
{ }

IBlockedReceiver *LinuxSocketCanReceiverFactory::produce()
{
    auto socket = LinuxSocketCanSocketFactory::produce(interface, 50, 3);
    return new LinuxSocketCanReceiver (socket);
}
