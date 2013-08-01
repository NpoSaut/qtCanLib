#include "cansendqueue.h"
#include "can.h"

Can canDev;

Can::Can(QObject *parent) :
    QObject(parent)
{
}

void Can::transmitMessage (CanFrame frame)
{
//#if defined WITH_CAN
//    emit transmitToIoDrv ( frame );
//#endif
    CanInternals::canSendQueue.push (frame);
}

#if defined WITH_CAN
void Can::receiveFromIoDrv (CanFrame frame)
{
    emit receiveNewMessage (frame);
}
#endif
