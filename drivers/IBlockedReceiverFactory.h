#ifndef IBLOCKEDRECEIVERFACTORY_H
#define IBLOCKEDRECEIVERFACTORY_H

#include "IBlockedReceiver.h"

class IBlockedReceiverFactory
{
public:
    virtual IBlockedReceiver *produce () = 0;
};

#endif // IBLOCKEDRECEIVERFACTORY_H
