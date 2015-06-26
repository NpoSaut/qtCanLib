#ifndef LINUXSOCKETCANSOCKET_H
#define LINUXSOCKETCANSOCKET_H

#include <QString>

class LinuxSocketCanSocket
{
public:
    LinuxSocketCanSocket (int number, QString interface, int rxCapacity, int txCapacity)
        : number (number), interface (interface), rxCapacity (rxCapacity), txCapacity (txCapacity)
    { }

    const int number;
    const QString interface;
    const int rxCapacity;
    const int txCapacity;
};

#endif // LINUXSOCKETCANSOCKET_H
