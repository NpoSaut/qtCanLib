#ifdef LIB_CAN_NICK

#include "cannick.h"

#include <QMetaType>

#include "CanNick/workingwithmessage.h"

CanNick::CanNick(QObject *parent) :
    Can(parent)
{
    qRegisterMetaType<CanFrame>("CanFrame");

    QObject::connect(&CanInternals::receiveMessagetLoop, SIGNAL(messageReceived(CanFrame)),
                     this, SLOT(getMessageFromDriver(CanFrame)));

}

void CanNick::onTransmitMessage(CanFrame frame)
{
    CanInternals::transmit(frame);
}

void CanNick::onGetMessage(CanFrame frame)
{
    emit messageReceived(frame);
}

#endif // LIB_CAN_NICK
