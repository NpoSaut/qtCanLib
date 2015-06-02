#ifndef SKTCAN_H
#define SKTCAN_H

#if defined LIB_SOCKET_CAN
#include <linux/socket.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
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

            bool read (CanFrame &frame);
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

#endif // LIB_SOCKET_CAN

#endif // SKTCAN_H
