#ifndef SENDWORKER_H
#define SENDWORKER_H

#include "qtDoodahLib/IThreadWorker.h"
#include "qtDoodahLib/queues/IThreadSafeQueue.h"
#include "../IBlockedSender.h"

namespace AsyncCanInternals {

// В петле производит взятие фрейма из queue и отправку его посредством sender
class SendWorker : public IThreadWorker
{
    Q_OBJECT
public:
    explicit SendWorker(IBlockedSender *sender, IThreadSafeQueue<CanFrame> *queue, QObject *parent = 0);

public slots:
    void run ();

private:
    IBlockedSender *sender;
    IThreadSafeQueue<CanFrame> *queue;
};

}

#endif // SENDWORKER_H
