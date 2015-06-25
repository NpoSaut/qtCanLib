#ifndef IBLOCKEDRECEIVER_H
#define IBLOCKEDRECEIVER_H

#include "../CanFrame.h"

class IBlockedReceiver
{
public:
    virtual CanFrame receive () = 0;
};

#endif // IBLOCKEDRECEIVER_H
