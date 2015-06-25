#ifndef RECEIVEWORKER_H
#define RECEIVEWORKER_H

#include "qtDoodahLib/IThreadWorker.h"
#include "../IBlockedReceiver.h"

namespace AsyncCanInternals {

// В петле принимает фреймы из receiver и испускает сигналы с ними
class ReceiveWorker : public IThreadWorker
{
    Q_OBJECT
public:
    explicit ReceiveWorker(IBlockedReceiver *receiver, QObject *parent = 0);

signals:
    void received (CanFrame );

public slots:
    void run ();

private:
    IBlockedReceiver *receiver;
};

}

#endif // RECEIVEWORKER_H
