#ifndef DUMMYCANRECEIVERFACTORY_H
#define DUMMYCANRECEIVERFACTORY_H

#include "../IBlockedReceiverFactory.h"
#include "DummyCanReceiver.h"

class DummyCanReceiverFactory : public IBlockedReceiverFactory
{
public:
    DummyCanReceiverFactory() { }
    IBlockedReceiver *produce () { return new DummyCanReceiver; }
};

#endif // DUMMYCANRECEIVERFACTORY_H
