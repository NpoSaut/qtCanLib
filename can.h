#ifndef IODRV_CAN_H
#define IODRV_CAN_H

#include <QObject>

#include "canframe.h"

class Can : public QObject
{
    Q_OBJECT
public:
    explicit Can(QObject *parent = 0);
    
// Interaction with user
signals:
    void messageReceived (CanFrame frame);
public slots:
    void transmitMessage (CanFrame frame);

// Interaction with underlying CAN driver
signals:
    void messageToTransmitAppear (CanFrame frame);
private slots:
    void getMessageFromDriver (CanFrame frame);
    
};

extern Can can;

#endif // IODRV_CAN_H
