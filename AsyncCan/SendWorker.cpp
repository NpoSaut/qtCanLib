#include "SendWorker.h"

using namespace AsyncCanInternals;

SendWorker::SendWorker(IBlockedSender *sender, IThreadSafeQueue<CanFrame> *queue)
    : IThreadWorker (),
      sender (sender),
      queue (queue),
      frames (),
      capacity (0)
{ }

void SendWorker::run()
{
    forever {
        frames.resize(0);
        frames.append (queue->dequeue()); // Первый ждём всегда

        do
            capacity = sender->getCapacity();
        while (capacity <= 0);

        for (int i = 1; i < capacity && !queue->isEmpty(); i++)
            frames.append (queue->dequeue());

        sender->send(frames);
    }
}
