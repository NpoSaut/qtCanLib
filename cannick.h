#ifndef CANNICK_H
#define CANNICK_H

#ifdef LIB_CAN_NICK

#include "can.h"

class CanNick : public Can
{
public:
    explicit CanNick(QObject *parent = 0);
protected:
    void onTransmitMessage(CanFrame frame);
    void onGetMessage(CanFrame frame);
};

#endif // LIB_CAN_NICK

#endif // CANNICK_H
