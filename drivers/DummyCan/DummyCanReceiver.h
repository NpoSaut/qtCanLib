#ifndef DUMMYCANRECEIVER_H
#define DUMMYCANRECEIVER_H

#include "../IBlockedReceiver.h"

class DummyCanReceiver : public IBlockedReceiver
{
public:
    DummyCanReceiver() : frames() {}
    virtual const QVector<CanFrame> &receive () { return frames; }

private:
    QVector<CanFrame> frames;
};

#endif // DUMMYCANRECEIVER_H
