#ifndef ICAN_H
#define ICAN_H

#include <QObject>
#include "CanFrame.h"

class ICan : public QObject
{
    Q_OBJECT
public:
    explicit ICan(QObject *parent = 0);

signals:
    void received (CanFrame);

public slots:
    virtual void send (CanFrame) = 0;
};

#endif // ICAN_H
