#include "ReceiveWorker.h"

using namespace AsyncCanInternals;

ReceiveWorker::ReceiveWorker(IBlockedReceiver *receiver, QObject *parent)
    : IThreadWorker (parent),
      receiver (receiver)
{ }

void ReceiveWorker::run()
{
    forever {
        auto frames = receiver->receive();
        for (auto &f : frames)
            emit received(f);
    }
}
