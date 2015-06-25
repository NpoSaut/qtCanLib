#ifndef LINUXSOCKETCANSOCKET_H
#define LINUXSOCKETCANSOCKET_H

#include <QString>

class LinuxSocketCanSocket
{
public:
    LinuxSocketCanSocket (int number, QString interface)
        : number (number), interface (interface)
    { }

    const int number;
    const QString interface;
};

#endif // LINUXSOCKETCANSOCKET_H
