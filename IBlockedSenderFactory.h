#ifndef IBLOCKEDSENDERFACTORY_H
#define IBLOCKEDSENDERFACTORY_H

#include "IBlockedSender.h"

class IBlockedSenderFactory
{
public:
    virtual IBlockedSender *produce () = 0;
};

#endif // IBLOCKEDSENDERFACTORY_H
