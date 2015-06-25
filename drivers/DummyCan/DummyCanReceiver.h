#ifndef DUMMYCANRECEIVER_H
#define DUMMYCANRECEIVER_H

#include "../IBlockedReceiver.h"

class DummyCanReceiver : public IBlockedReceiver
{
public:
    DummyCanReceiver() {}
    virtual CanFrame receive ()
    {
        forever; // loop
        return CanFrame (); // for silent
    }
};

#endif // DUMMYCANRECEIVER_H
