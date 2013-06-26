#include "can.h"

Can canDev;

Can::Can(QObject *parent) :
    QObject(parent)
{
}

void Can::transmitMessage (CanFrame frame)
{
    emit transmitToIoDrv ( frame );
}

#if defined WITH_CAN
void Can::receiveFromIoDrv (CanFrame frame)
{
    emit receiveNewMessage (frame);
}
#endif
