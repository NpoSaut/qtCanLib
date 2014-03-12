#ifndef CANNICK_H
#define CANNICK_H

#include "can.h"

class CanNick : public Can
{
public:
    explicit CanNick(QObject *parent = 0);
protected:
    void onTransmitMessage(CanFrame frame);
    void onGetMessage(CanFrame frame);
};


#endif // CANNICK_H
