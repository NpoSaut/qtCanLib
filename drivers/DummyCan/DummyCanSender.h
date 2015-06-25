#ifndef DUMMYCANSENDER_H
#define DUMMYCANSENDER_H

#include "../IBlockedSender.h"

class DummyCanSender : public IBlockedSender
{
public:
    DummyCanSender() {}
     virtual void send (CanFrame frame) { Q_UNUSED(frame); }
};

#endif // DUMMYCANSENDER_H
