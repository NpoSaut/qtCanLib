#ifndef APPICANRECEIVERFACTORY_H
#define APPICANRECEIVERFACTORY_H

#include "../IBlockedReceiverFactory.h"
#include "AppiCan.h"

class AppiCanReceiverFactory : public IBlockedReceiverFactory
{
public:
    AppiCanReceiverFactory(AppiCan *appiCan) : appiCan (appiCan) { }
    virtual IBlockedReceiver *produce () { return appiCan; }
private:
    AppiCan *appiCan;
};

#endif // APPICANRECEIVERFACTORY_H
