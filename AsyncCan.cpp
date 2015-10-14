#include "AsyncCan.h"
#include "AsyncCan/ReceiveWorker.h"
#include "AsyncCan/SendWorker.h"

using namespace AsyncCanInternals;

AsyncCan::AsyncCan(IBlockedReceiverFactory *receiverFactory, IBlockedSenderFactory *senderFactory, QObject *parent) :
    ICan(parent),
    queue (),
    receiveThread (new ReceiveWorker(receiverFactory->produce()), this),
    sendThread (new SendWorker(senderFactory->produce(), &queue), this)
{
    QObject::connect (receiveThread.worker, SIGNAL(received(CanFrame)), this, SLOT(pushReceiveSignal(CanFrame)), Qt::QueuedConnection);
}

void AsyncCan::start()
{
    receiveThread.start();
    sendThread.start();
}

void AsyncCan::send(CanFrame frame)
{
    queue.enqueue(frame);
}

void AsyncCan::pushReceiveSignal(CanFrame frame)
{
    emit received(frame);
}
