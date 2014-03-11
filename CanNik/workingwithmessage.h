#ifndef WORKINGWITHMESSAGE_H
#define WORKINGWITHMESSAGE_H

#include <QThread>
#include <QTimer>
#include "candriver.h"
#include "Can/canframe.h"
#include "Can/can.h"

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
#endif // WORKINGWITHMESSAGE_H
