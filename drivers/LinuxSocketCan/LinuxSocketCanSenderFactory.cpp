#include "LinuxSocketCanSenderFactory.h"

#include "LinuxSocketCanSocketFactory.h"
#include "LinuxSocketCanSender.h"

LinuxSocketCanSenderFactory::LinuxSocketCanSenderFactory(QString interface)
    : interface (interface)
{ }

IBlockedSender *LinuxSocketCanSenderFactory::produce()
{
    auto socket = LinuxSocketCanSocketFactory::produce(interface, 3, 50);
    return new LinuxSocketCanSender (socket);
}
