#ifndef DUMMYCANRECEIVER_H
#define DUMMYCANRECEIVER_H

#include "../IBlockedReceiver.h"

class DummyCanReceiver : public IBlockedReceiver
{
public:
    DummyCanReceiver() {}
    virtual QVector<CanFrame> receive ()
    {
        return QVector<CanFrame> ();
    }
};

#endif // DUMMYCANRECEIVER_H
