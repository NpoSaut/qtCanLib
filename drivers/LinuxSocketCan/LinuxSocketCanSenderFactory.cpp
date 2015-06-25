#include "LinuxSocketCanSenderFactory.h"

#include "LinuxSocketCanSocketFactory.h"
#include "LinuxSocketCanSender.h"

LinuxSocketCanSenderFactory::LinuxSocketCanSenderFactory(QString interface)
    : interface (interface)
{ }

IBlockedSender *LinuxSocketCanSenderFactory::produce()
{
    auto socket = LinuxSocketCanSocketFactory::produce(interface);
    return new LinuxSocketCanSender (socket);
}
