#ifndef SENDWORKER_H
#define SENDWORKER_H

#include "qtDoodahLib/IThreadWorker.h"
#include "qtDoodahLib/queues/IThreadSafeQueue.h"
#include "../drivers/IBlockedSender.h"

namespace AsyncCanInternals {

// В петле производит взятие фрейма из queue и отправку его посредством sender
class SendWorker : public IThreadWorker
{
    Q_OBJECT
public:
    explicit SendWorker(IBlockedSender *sender, IThreadSafeQueue<CanFrame> *queue);

public slots:
    void run ();

private:
    IBlockedSender *sender;
    IThreadSafeQueue<CanFrame> *queue;
    QVector<CanFrame> frames;
    int capacity;
};

}

#endif // SENDWORKER_H
