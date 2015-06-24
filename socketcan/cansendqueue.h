#ifndef CANSENDQUEUE_H
#define CANSENDQUEUE_H

#ifdef LIB_SOCKET_CAN

#include "qtDoodahLib/queues.h"
#include "../CanFrame.h"

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

#endif // LIB_SOCKET_CAN

#endif // CANSENDQUEUE_H
