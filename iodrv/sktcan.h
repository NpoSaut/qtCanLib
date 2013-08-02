#if defined WITH_CAN || defined WITH_SERIAL

#ifndef SKTCAN_H
#define SKTCAN_H

#include <QString>
#include <QThread>

#include "canframe.h"

namespace CanInternals
{
    int getSocket(char* iface_name);
//    int write_can_frame(int s, can_frame frame);
    int read_can_frame(int s, struct can_frame* frame);

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

    class ReadSocketLoop : public QThread
    {
        Q_OBJECT
    public:
        ReadSocketLoop (QString interfaceName);

    signals:
        void newMessageReceived (CanFrame frame);

    private:
        ReadSocket readSocket;

        void run ();
    };
    extern ReadSocketLoop readSocketLoop;

}
#endif // SKTCAN_H

#endif
