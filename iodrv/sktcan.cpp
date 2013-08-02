//#define DEBUG_CAN_READ
//#define DEBUG_CAN_SEND


#if defined WITH_CAN

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <unistd.h>

#include <QMutex>
#include <QDebug>

#include "sktcan.h"


QMutex mutex;

using namespace CanInternals;


Socket::Socket(QString interfaceName)
    : number (0), ready (false)
{
    // Создаем сокет
    number = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if(number < 0)
    {
        int errsv = errno;
        qDebug("Ошибка при открытии сокета: %d\n", errsv);
        return;
    }

    // Определяем индекс интерфейса
    struct ifreq ifr;
    strcpy(ifr.ifr_name, interfaceName.toStdString ().c_str ());

    // Полученный индес будет записан в поле ifr.ifr_ifindex
    ioctl(number, SIOCGIFINDEX, &ifr);
    if(ifr.ifr_ifindex < 0)
    {
        int errsv = errno;
        qDebug("Не найден интерфейс %s, ошибка: %d\n", interfaceName.toStdString ().c_str (), errsv);
        return;
    }
    qDebug("Найден CAN интерфейс: %d\n", ifr.ifr_ifindex);

    // Биндим сокет на нужный интерфейс
    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    bind(number, (struct sockaddr*)&addr, sizeof(addr));

    ready = (number != 0);
}

WriteSocket CanInternals::writeSocket ("can0");

WriteSocket::WriteSocket(QString interfaceName)
    : Socket(interfaceName)
{ }

bool WriteSocket::send(CanFrame frame)
{
    if (!Socket::ready)
    {
        qDebug("WriteSocket: сокет не существует\n");
        return false;
    }
    else
    {
        #ifdef DEBUG_CAN_SEND
        //printf("\033[0;36;40m >>\033[0;37;40m");
        //printf("\033[1;36;40m %d\033[0;37;40m\n", frame.can_id);

        fprintf(stderr, "\033[0;33;40mSend -> sock %d \033[0;37;40m", Socket::number );

        printf("\033[0;33;40m | \033[0;30;43m0x%04x\033[0;33;40m | \033[0;37;40m", frame.getDescriptor ()); fflush(stderr);
        for(int iii = 0; iii < frame.getData ().size (); iii++)
            printf("\033[0;33;40m%02x \033[0;37;40m", frame.getData ()[iii]); fflush(stderr);
        printf("\033[0;33;40m | \033[0;37;40m");fflush(stderr);
        #endif

        can_frame linuxFrame = frame;
        int bytes_sent = write(Socket::number, &linuxFrame, sizeof(struct can_frame));

        if(bytes_sent < 0)
        {
            #ifdef DEBUG_CAN_SEND
            int errsv = errno;
            fprintf(stderr, "\033[1;30;43mErr %3d\033[0;37;40m", errsv );fflush(stderr);
            printf("\033[0;37;40m\n");
            fflush(stderr);
            #endif
        }
        #ifdef DEBUG_CAN_SEND
        else
        {
            fprintf(stderr, "\033[0;33;40mOK    \033[0;37;40m");fflush(stderr);
            printf("\033[0;37;40m\n");
            fflush(stderr);
        }
        #endif

        return (bytes_sent >= 0);
    }
}


ReadSocket::ReadSocket(QString interfaceName)
    : Socket (interfaceName)
{ }

CanFrame ReadSocket::read()
{
    if (!Socket::ready)
    {
        qDebug("ReadSocket: сокет не существует");
        return CanFrame();
    }
    else
    {
        can_frame linuxFrame;
        int bytes_read = -1;
        while (bytes_read < 0)
            bytes_read = ::read(Socket::number, &linuxFrame, sizeof(struct can_frame));
        CanFrame frame (linuxFrame);

        #ifdef DEBUG_CAN_READ
        fprintf(stderr, "\033[0;36;40mRead <- sock %d \033[0;37;40m", Socket::number );

        printf("\033[0;36;40m | \033[0;30;46m0x%04x\033[0;36;40m | \033[0;37;40m", frame.getDescriptor ());fflush(stderr);
        for(int iii = 0; iii < frame.getData ().size (); iii++)
            printf("\033[0;36;40m%02x \033[0;37;40m", frame.getData ()[iii]);fflush(stderr);
        printf("\033[0;36;40m | \033[0;37;40m");fflush(stderr);

        if(bytes_read < 0)
        {
            int errsv = errno;
            fprintf(stderr, "\033[1;30;46mErr %3d\033[0;37;40m", errsv );fflush(stderr);
            printf("\033[0;37;40m\n");
            fflush(stderr);
        }
        else
        {
            fprintf(stderr, "\033[0;36;40mOK    \033[0;37;40m");fflush(stderr);
            printf("\033[0;37;40m\n");
            fflush(stderr);
        }
        #endif

        return frame;
    }
}

ReadSocketThread CanInternals::readSocketLoop ("can0");

ReadSocketThread::ReadSocketThread(QString interfaceName)
    : readSocket (interfaceName)
{
    this->start ();
}

void ReadSocketThread::run()
{
    while (true)
    {
        emit messageReceived (readSocket.read ());
    }
}

#endif

