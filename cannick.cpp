#include "cannick.h"

#include "CanNick/workingwithmessage.h"


CanNick::CanNick(QObject *parent) :
    Can(parent)
{
    qRegisterMetaType<CanFrame>("CanFrame");

    QObject::connect(&CanInternals::receiveMessagetLoop, SIGNAL(messageReceived(CanFrame)),
                     this, SLOT(getMessageFromDriver(CanFrame)));

}

void Can::transmitMessage(CanFrame frame)
{
    CanInternals::transmit(frame);
}

void Can::getMessageFromDriver(CanFrame frame)
{
    emit messageReceived(frame);
}
