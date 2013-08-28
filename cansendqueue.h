#ifndef CANSENDQUEUE_H
#define CANSENDQUEUE_H

#include "qtDoodahLib/queues.h"
#include "canframe.h"

namespace CanInternals
{

    class CanSendQueue : Queues::PriorityQueueBase<CanFrame>
    {
        public:
            CanSendQueue()
                : Queues::PriorityQueueBase<CanFrame>()
            {}
            void push(CanFrame f);

        protected:
            void process(CanFrame f);
            int compare(CanFrame a, CanFrame b);
    };
    extern CanSendQueue canSendQueue;

}

#endif // CANSENDQUEUE_H
