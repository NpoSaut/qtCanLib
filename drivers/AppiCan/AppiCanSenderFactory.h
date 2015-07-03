#ifndef APPICANSENDERFACTORY_H
#define APPICANSENDERFACTORY_H

#include "../IBlockedSenderFactory.h"
#include "AppiCan.h"

class AppiCanSenderFactory : public IBlockedSenderFactory
{
public:
    AppiCanSenderFactory(AppiCan *appiCan) : appiCan (appiCan) { }
    virtual IBlockedSender *produce () { return appiCan; }
private:
    AppiCan *appiCan;
};

#endif // APPICANSENDERFACTORY_H
