#ifndef DUMMYCANSENDER_H
#define DUMMYCANSENDER_H

#include "../IBlockedSender.h"

class DummyCanSender : public IBlockedSender
{
public:
    DummyCanSender() {}
    virtual void send (const QVector<CanFrame> &frames) { Q_UNUSED(frames); }
    virtual int getCapacity () { return 1000; }
};

#endif // DUMMYCANSENDER_H
