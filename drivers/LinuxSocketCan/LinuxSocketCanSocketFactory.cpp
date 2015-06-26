#include "LinuxSocketCanSocketFactory.h"

extern "C"
{
#include "cSocketCanLib/src/SocketCanLib.h"
}

LinuxSocketCanSocketFactory::LinuxSocketCanSocketFactory()
{
}

LinuxSocketCanSocket *LinuxSocketCanSocketFactory::produce(QString interfaceName, int rxCapacity, int txCapacity)
{
    int number = SocketOpen(interfaceName.toStdString().c_str(), rxCapacity, txCapacity);
    return number > 0 ?
                new LinuxSocketCanSocket (number, interfaceName, rxCapacity, txCapacity)
              : nullptr;
}
