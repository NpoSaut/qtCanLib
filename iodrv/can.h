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
    void receiveNewMessage (CanFrame frame);

#if defined WITH_CAN
    void transmitToIoDrv (CanFrame frame);
#endif
    
public slots:
    void transmitMessage (CanFrame frame);

#if defined WITH_CAN
    void receiveFromIoDrv (CanFrame frame);
#endif
    
};

extern Can canDev;

#endif // IODRV_CAN_H
