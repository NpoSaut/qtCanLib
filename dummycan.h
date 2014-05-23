#ifndef DUMMYCAN_H
#define DUMMYCAN_H

#include "qtCanLib/can.h"

// Класс-заглушка для Can-а: ничего не отправляет и ничего не передаёт
class DummyCan : public Can
{
    Q_OBJECT
public:
    explicit DummyCan(QObject *parent = 0)
        : Can (parent)
    { }

protected:
    void onTransmitMessage(CanFrame frame) { }
    void onGetMessage(CanFrame frame) { }
};

#endif // DUMMYCAN_H
