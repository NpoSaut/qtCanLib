#include "sktcan.h"
#include "cansendqueue.h"
#include "can.h"

Can can;

Can::Can(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<CanFrame>("CanFrame");
    QObject::connect (&CanInternals::readSocketLoop, SIGNAL(messageReceived(CanFrame)),
                      this, SLOT(receiveFromSocketCan(CanFrame)));
}

void Can::transmitMessage (CanFrame frame)
{
    CanInternals::canSendQueue.push (frame);
}

#if defined WITH_CAN
void Can::receiveFromSocketCan(CanFrame frame)
{
    emit messageReceived (frame);
}
#endif
