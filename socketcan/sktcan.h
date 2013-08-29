#if defined WITH_CAN || defined WITH_SERIALPORT

#ifndef SKTCAN_H
#define SKTCAN_H

#include <linux/can.h>

#include <QString>
#include <QThread>

#include "../canframe.h"

namespace CanInternals
{
    CanFrame convert (const struct can_frame &socketFrame);
    CanFrame convert (const struct can_frame *socketFrame);
    can_frame convert (const CanFrame &canFrame);

    class Socket
    {
        public:
            Socket (QString interfaceName);

        protected:
            int number;
            bool ready;
    };

    class WriteSocket : public Socket
    {
        public:
            WriteSocket (QString interfaceName);

            bool send (CanFrame frame);
    };
    extern WriteSocket writeSocket;

    class ReadSocket : public Socket
    {
        public:
            ReadSocket (QString interfaceName);

            CanFrame read ();
    };

    class ReadSocketThread : public QThread
    {
        Q_OBJECT
    public:
        ReadSocketThread (QString interfaceName);

    signals:
        void messageReceived (CanFrame frame);

    private:
        ReadSocket readSocket;

        void run ();
    };
    extern ReadSocketThread readSocketLoop;

}
#endif // SKTCAN_H

#endif
