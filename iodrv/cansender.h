#ifndef CANSENDER_H
#define CANSENDER_H

#include "queues.h"
#include "canframe.h"

namespace CanInternals
{

    class CanSender : Queues::PriorityQueueBase<CanFrame>
    {
        public:
            CanSender()
                : Queues::PriorityQueueBase<CanFrame>()
            {}
            void Push(CanFrame f);

        protected:
            void process(CanFrame f);
            int compare(CanFrame a, CanFrame b);
    };

}
#endif // CANSENDER_H
