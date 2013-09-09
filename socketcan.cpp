#ifndef WIN32

#include "can.h"

#include "socketcan.h"
#include "socketcan/sktcan.h"
#include "socketcan/cansendqueue.h"

SocketCan::SocketCan(QObject *parent) :
    Can(parent)
{
    qRegisterMetaType<CanFrame>("CanFrame");

    QObject::connect (&CanInternals::readSocketLoop, SIGNAL(messageReceived(CanFrame)),
                      this, SLOT(getMessageFromDriver(CanFrame)));

    // It can't be done, because CanSendQueue is not QObject child
//    QObject::connect (this, SIGNAL(messageToTransmitAppear(CanFrame)),
//                      &CanInternals::canSendQueue, SLOT(push(CanFrame)));
}

void SocketCan::onTransmitMessage (CanFrame frame)
{
    CanInternals::canSendQueue.push (frame);
}

void SocketCan::onGetMessage (CanFrame frame)
{
    emit messageReceived (frame);
}

#endif
