#ifndef LINUXSOCKETCANSOCKETFACTORY_H
#define LINUXSOCKETCANSOCKETFACTORY_H

#include <QString>
#include "LinuxSocketCanSocket.h"

class LinuxSocketCanSocketFactory
{
public:
    LinuxSocketCanSocketFactory();

    static LinuxSocketCanSocket *produce (QString interfaceName);

};

#endif // LINUXSOCKETCANSOCKETFACTORY_H
