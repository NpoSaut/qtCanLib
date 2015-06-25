#ifndef DUMMYCAN_H
#define DUMMYCAN_H

#include "ICan.h"

class DummyCan : public ICan
{
    Q_OBJECT
public:
    explicit DummyCan(QObject *parent = 0);

public slots:
    void send (CanFrame);
};

#endif // DUMMYCAN_H
