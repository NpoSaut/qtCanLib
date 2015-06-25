#include "ReceiveWorker.h"

using namespace AsyncCanInternals;

ReceiveWorker::ReceiveWorker(IBlockedReceiver *receiver, QObject *parent)
    : IThreadWorker (parent),
      receiver (receiver)
{ }

void ReceiveWorker::run()
{
    forever {
        emit received (receiver->receive());
    }
}
