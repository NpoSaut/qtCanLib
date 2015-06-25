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
        sender->send(queue->dequeue());
    }
}
