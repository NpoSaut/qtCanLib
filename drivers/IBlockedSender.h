#ifndef IBLOCKEDSENDER_H
#define IBLOCKEDSENDER_H

#include <QVector>

#include "../CanFrame.h"

class IBlockedSender
{
public:
    virtual void send (QVector<CanFrame> frames) = 0;
    virtual int getCapacity () = 0;
};

#endif // IBLOCKEDSENDER_H
