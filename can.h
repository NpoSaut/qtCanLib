#ifndef IODRV_CAN_H
#define IODRV_CAN_H

#include <QObject>
#include <QMetaType>
#include "canframe.h"

class Can : public QObject
{
    Q_OBJECT
public:
    explicit Can(QObject *parent = 0)
        : QObject(parent)
    {
        qRegisterMetaType<CanFrame>("CanFrame");
    }
    
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

// Декоратор Can, блокирующий отправку
class CanSilent : public Can
{
    Q_OBJECT
public:
    explicit CanSilent(Can *parentCan, QObject *parentQObjet = 0)
        : Can (parentQObjet),
          parentCan (parentCan)
    {
        QObject::connect (parentCan, SIGNAL(messageReceived(CanFrame)), this, SLOT(getMessageFromDriver(CanFrame)));
    }

protected:
    void onTransmitMessage (CanFrame frame) { }
    void onGetMessage (CanFrame frame) { emit messageReceived (frame); }

private:
    Can *parentCan;
};

#endif // IODRV_CAN_H
