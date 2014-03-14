#ifndef WORKINGWITHMESSAGE_H
#define WORKINGWITHMESSAGE_H

#ifdef LIB_CAN_NICK

#include <QThread>
#include <QTimer>
#include "../canframe.h"
#include "../can.h"
#include "candriver.h"

namespace CanInternals
{
  extern CanDriver canDrv;

  extern void transmit(CanFrame frame);

  class ReceiveMessageThread : public QThread
  {
    Q_OBJECT
  public:
    ReceiveMessageThread(QString interfaceName);
    void run ();

  signals:
    void messageReceived (CanFrame frame);

  private:

  };
  extern ReceiveMessageThread receiveMessagetLoop;

}

#endif // LIB_CAN_NICK

#endif // WORKINGWITHMESSAGE_H
