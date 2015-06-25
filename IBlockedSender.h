#ifndef IBLOCKEDSENDER_H
#define IBLOCKEDSENDER_H

#include "CanFrame.h"

class IBlockedSender
{
public:
    virtual void send (CanFrame frame) = 0;
};

#endif // IBLOCKEDSENDER_H
