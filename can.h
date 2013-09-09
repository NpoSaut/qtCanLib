#ifndef IODRV_CAN_H
#define IODRV_CAN_H

#include <QObject>
#include "canframe.h"

class Can : public QObject
{
    Q_OBJECT
public:
    explicit Can(QObject *parent = 0)
        : QObject(parent)
    { }
    
// Interaction with user
signals:
    void messageReceived (CanFrame frame);
public slots:
    void transmitMessage (CanFrame frame) { onTransmitMessage(frame); }

// Interaction with underlying CAN driver
signals:
    void messageToTransmitAppear (CanFrame frame);
private slots:
    void getMessageFromDriver (CanFrame frame) { onGetMessage(frame); }

protected:
    // Конкретная реализация отправки и приёма сообщений
    virtual void onTransmitMessage(CanFrame frame) = 0;
    virtual void onGetMessage(CanFrame frame) = 0;
};

#endif // IODRV_CAN_H
