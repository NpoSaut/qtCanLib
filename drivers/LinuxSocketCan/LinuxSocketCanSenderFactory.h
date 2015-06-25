#ifndef LINUXSOCKETCANSENDERFACTORY_H
#define LINUXSOCKETCANSENDERFACTORY_H

#include <QString>

#include "../IBlockedSenderFactory.h"

class LinuxSocketCanSenderFactory : public IBlockedSenderFactory
{
public:
    LinuxSocketCanSenderFactory(QString interface);

    IBlockedSender *produce ();

private:
    QString interface;
};

#endif // LINUXSOCKETCANSENDERFACTORY_H
