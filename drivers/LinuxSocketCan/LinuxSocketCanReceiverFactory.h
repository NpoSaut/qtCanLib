#ifndef LINUXSOCKETCANRECEIVERFACTORY_H
#define LINUXSOCKETCANRECEIVERFACTORY_H

#include <QString>

#include "../IBlockedReceiverFactory.h"

class LinuxSocketCanReceiverFactory : public IBlockedReceiverFactory
{
public:
    LinuxSocketCanReceiverFactory(QString interface);

    IBlockedReceiver *produce ();

private:
    QString interface;
};

#endif // LINUXSOCKETCANRECEIVERFACTORY_H
