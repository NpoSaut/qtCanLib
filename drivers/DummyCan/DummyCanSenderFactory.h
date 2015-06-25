#ifndef DUMMYCANSENDERFACTORY_H
#define DUMMYCANSENDERFACTORY_H

#include "../IBlockedSenderFactory.h"
#include "DummyCanSender.h"

class DummyCanSenderFactory : public IBlockedSenderFactory
{
public:
    DummyCanSenderFactory() {}
    IBlockedSender *produce () { return new DummyCanSender; }
};

#endif // DUMMYCANSENDERFACTORY_H
