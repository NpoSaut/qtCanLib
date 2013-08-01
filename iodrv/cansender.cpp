#include "cansender.h"
#include "masqarade.h"

using namespace CanInternals;

void CanSender::Push(CanFrame f)
{
}

void CanSender::process(CanFrame f)
{
    this->enqueue(f);
}

int CanSender::compare(CanFrame a, CanFrame b)
{
    return b.getId() - a.getId();
}
