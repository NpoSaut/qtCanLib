#include "can.h"

Can canDev;

Can::Can(QObject *parent) :
    QObject(parent)
{
}

void Can::transmitMessage (CanFrame frame)
{
#if defined WITH_CAN
    can_frame linuxFrame = frame;
    emit transmitToIoDrv ( &linuxFrame );
#endif
}

#if defined WITH_CAN
void Can::receiveFromIoDrv (const struct can_frame* frame)
{
    emit receiveNewMessage (CanFrame (frame));
}
#endif
