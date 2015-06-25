#ifndef CANPRIORITYQUEUE_H
#define CANPRIORITYQUEUE_H

#include "../CanFrame.h"
#include "qtDoodahLib/queues/PriorityThreadSafeQueue.h"

namespace AsyncCanInternals {

// Очередь сообщений с естественным для CAN приоритетом по Id
class CanPriorityQueue : public PriorityThreadSafeQueue<CanFrame>
{
public:
    CanPriorityQueue();

private:
    int compare(CanFrame a, CanFrame b);
};

}

#endif // CANPRIORITYQUEUE_H
