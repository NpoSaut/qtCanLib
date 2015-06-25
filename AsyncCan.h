#ifndef ASYNCCAN_H
#define ASYNCCAN_H

#include "ICan.h"
#include "drivers/IBlockedReceiverFactory.h"
#include "drivers/IBlockedSenderFactory.h"
#include "qtDoodahLib/ThreadWithWorker.h"
#include "AsyncCan/CanPriorityQueue.h"

// С помощью переданных фабрик создаст отправителя и принимателя с блокирующим API,
// поместит их в отдельный для каждого поток,
// создаст очереди к ним и возможность асинхронной работы
class AsyncCan : public ICan
{
    Q_OBJECT
public:
    explicit AsyncCan(IBlockedReceiverFactory *receiverFactory, IBlockedSenderFactory *senderFactory, QObject *parent = 0);

public slots:
    void start ();
    virtual void send (CanFrame frame);

private slots:
    void pushReceiveSignal (CanFrame frame);

private:
    AsyncCanInternals::CanPriorityQueue queue;
    ThreadWithWorker receiveThread;
    ThreadWithWorker sendThread;
};

#endif // ASYNCCAN_H
