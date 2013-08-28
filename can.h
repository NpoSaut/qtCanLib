#ifndef IODRV_CAN_H
#define IODRV_CAN_H

#if defined WITH_CAN
#include <linux/can.h>
#endif

#include <QObject>

#include "canframe.h"

class Can : public QObject
{
    Q_OBJECT
public:
    explicit Can(QObject *parent = 0);
    
signals:
    void messageReceived (CanFrame frame);

public slots:
    void transmitMessage (CanFrame frame);

#if defined WITH_CAN
    void receiveFromSocketCan (CanFrame frame);
#endif
    
};

extern Can can;

#endif // IODRV_CAN_H
