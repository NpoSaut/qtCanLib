#include "SendWorker.h"

using namespace AsyncCanInternals;

SendWorker::SendWorker(IBlockedSender *sender, IThreadSafeQueue<CanFrame> *queue, QObject *parent)
    : IThreadWorker (parent),
      sender (sender),
      queue (queue)
{ }

void SendWorker::run()
{
    forever {
        QVector<CanFrame> frames;
        frames.append (queue->dequeue()); // Первый ждём всегда

        int capacity = sender->getCapacity();
        for (int i = 1; i < capacity && !queue->isEmpty(); i++)
            frames.append (queue->dequeue());

        sender->send(frames);
    }
}
