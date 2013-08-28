#include "can.h"

#include "socketcan/sktcan.h"
#include "socketcan/cansendqueue.h"

Can can;

Can::Can(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<CanFrame>("CanFrame");

    QObject::connect (&CanInternals::readSocketLoop, SIGNAL(messageReceived(CanFrame)),
                      this, SLOT(getMessageFromDriver(CanFrame)));

    // It can't be done, because CanSendQueue is not QObject child
//    QObject::connect (this, SIGNAL(messageToTransmitAppear(CanFrame)),
//                      &CanInternals::canSendQueue, SLOT(push(CanFrame)));
}

void Can::transmitMessage (CanFrame frame)
{
    CanInternals::canSendQueue.push (frame);
}

void Can::getMessageFromDriver (CanFrame frame)
{
    emit messageReceived (frame);
}
