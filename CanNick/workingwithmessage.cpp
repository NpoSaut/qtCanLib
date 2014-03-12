#include "workingwithmessage.h"

namespace CanInternals
{
CanDriver canDrv;

void transmit(CanFrame frame)
{
    TransmitData td;
    td.control = 1;
    td.counter = 1;
    td.id = frame.getId() << 18 ;
    td.period = 50;
    td.dataLength = 8;
    for(int i = 0; i < 8; i++)
        td.data[i] = frame[i+1];
    canDrv.transmitMessage(td);
}

std::vector<CanFrame> receive()
{
    auto receivedMessages = canDrv.receiveMessage();
    std::vector<CanFrame> outFrames ( receivedMessages.size() );
    for (int i = 0; i < outFrames.size(); i ++)
    {
        outFrames[i].setId (receivedMessages[i].id >> 18);
        std::vector<byte> v (receivedMessages[i].data, receivedMessages[i].data + receivedMessages[i].datalen);
        outFrames[i].setData (v);
    }
    return outFrames;
}

ReceiveMessageThread receiveMessagetLoop ("can0");

ReceiveMessageThread::ReceiveMessageThread(QString interfaceName)
{
    this->start();
}

void ReceiveMessageThread::run()
{
    while(true)
    {
        msleep(1);
        auto receivedMessages = receive();
        for (int i = 0; i < receivedMessages.size(); i ++)
        {
            emit messageReceived(receivedMessages[i]);
        }
    }
}
}


