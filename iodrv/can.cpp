#include "can.h"

Can canDev;

Can::Can(QObject *parent) :
    QObject(parent)
{
}

void Can::transmitMessage (CanFrame frame)
{
#if defined WITH_CAN
    emit transmitToIoDrv ( frame );
#endif
}

#if defined WITH_CAN
void Can::receiveFromIoDrv (CanFrame frame)
{
    emit receiveNewMessage (frame);
}
#endif
