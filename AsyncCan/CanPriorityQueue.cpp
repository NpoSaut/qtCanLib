#include "CanPriorityQueue.h"

using namespace AsyncCanInternals;

CanPriorityQueue::CanPriorityQueue()
    : PriorityThreadSafeQueue(1000)
{ }

int CanPriorityQueue::compare(CanFrame a, CanFrame b)
{
    return b.getId() - a.getId();
}
