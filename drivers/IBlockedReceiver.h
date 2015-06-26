#ifndef IBLOCKEDRECEIVER_H
#define IBLOCKEDRECEIVER_H

#include <QVector>

#include "../CanFrame.h"

class IBlockedReceiver
{
public:
    virtual const QVector<CanFrame> &receive () = 0;
};

#endif // IBLOCKEDRECEIVER_H
