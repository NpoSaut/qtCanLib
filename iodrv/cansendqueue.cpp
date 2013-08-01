
#include "masqarade.h"
#include "sktcan.h"
#include "cansendqueue.h"

using namespace CanInternals;

CanSendQueue CanInternals::canSendQueue;

void CanSendQueue::push(CanFrame f)
{
    this->enqueue(f);
}

void CanSendQueue::process(CanFrame f)
{
    writeSocket.send (f);
}

int CanSendQueue::compare(CanFrame a, CanFrame b)
{
    return b.getId() - a.getId();
}
