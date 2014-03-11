#include "can.h"
#include "CanNik/workingwithmessage.h"
#include "IsoTp/IsoTpFrame/workingwithframes.h"

using namespace IsoTpFrames;

namespace CanInternals
{
Can canDev;

Can::Can(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<CanFrame>("CanFrame");
    QObject::connect(&CanInternals::receiveMessagetLoop, SIGNAL(messageReceived(CanFrame)), this, SLOT(getMessageFromDriver(CanFrame)));

}

void Can::transmitMessage(CanFrame frame)
{
    CanInternals::transmit(frame);
}

void Can::getMessageFromDriver(CanFrame frame)
{
    emit messageReceived(frame);
}
}
