//#define DEBUG_CAN_READ
//#define DEBUG_CAN_SEND


#if defined WITH_CAN

#include "sktcan.h"

#include <QMutex>

 QMutex mutex;

 using namespace CanInternals;

// getSocket создает и настраивает сокет на CAN-интерфейсе iface_name
int getSocket(char* iface_name)
{
    int errsv = 0;

    // Создаем сокет
    errno = 0;
    int s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if(s < 0)
    {
        errsv = errno;
        fprintf(stderr, "Ошибка при открытии сокета: %d\n", errsv);
        fflush(stderr);
        return 0;
    }

    // Определяем индекс интерфейса
    struct ifreq ifr;
    strcpy(ifr.ifr_name, iface_name);
    // Полученный индес будет записан в поле ifr.ifr_ifindex
    errno = 0;
    ioctl(s, SIOCGIFINDEX, &ifr);
    if(ifr.ifr_ifindex < 0)
    {
        errsv = errno;
        fprintf(stderr,"Не найден интерфейс %s, ошибка: %d\n", iface_name, errno);
        fflush(stderr);
        return 0;
    }
    printf("Найден CAN интерфейс: %d\n", ifr.ifr_ifindex);

    // Биндим сокет на нужный интерфейс
    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    bind(s, (struct sockaddr*)&addr, sizeof(addr));

    return s;
}

int write_can_frame(int s, can_frame frame)
{
    if (!s)
    {
        printf("send_can_frame: сокет не существует\n");
        fflush(stdout);
    }

    errno = 0;

    #ifdef DEBUG_CAN_SEND

    //printf("\033[0;36;40m >>\033[0;37;40m");
    //printf("\033[1;36;40m %d\033[0;37;40m\n", frame.can_id);

    fprintf(stderr, "\033[0;33;40mSend -> sock %d \033[0;37;40m", s );

    printf("\033[0;33;40m | \033[0;30;43m0x%04x\033[0;33;40m | \033[0;37;40m", frame.can_id*0x20+frame.can_dlc); fflush(stderr);
    for(int iii = 0; iii < frame.can_dlc; iii++)
        printf("\033[0;33;40m%02x \033[0;37;40m", frame.data[iii]); fflush(stderr);
    printf("\033[0;33;40m | \033[0;37;40m");fflush(stderr);
    #endif

    // !!! WARNING !!!
    // Мы не знаем, почему это нужно
    mutex.lock();
    usleep(100);
    int bytes_sent = write(s, &frame, sizeof(struct can_frame));
    usleep(100);
    mutex.unlock();

    if(bytes_sent < 0)
    {
        int errsv = errno;
        #ifdef DEBUG_CAN_SEND
        fprintf(stderr, "\033[1;30;43mErr %3d\033[0;37;40m", errsv );fflush(stderr);
        printf("\033[0;37;40m\n");
        fflush(stderr);
        #endif

        return 0;
    }
    #ifdef DEBUG_CAN_SEND
    else
    {
        fprintf(stderr, "\033[0;33;40mOK    \033[0;37;40m");fflush(stderr);
        printf("\033[0;37;40m\n");
        fflush(stderr);
    }
    #endif

    return 1;
}

int read_can_frame(int s, struct can_frame* frame)
{
    if (!s)
    {
        printf("read_can_frame: сокет не существует\n");
        fflush(stdout);
    }

    errno = 0;

    int bytes_read = read(s, frame, sizeof(struct can_frame));
    #ifdef DEBUG_CAN_READ
    fprintf(stderr, "\033[0;36;40mRead <- sock %d \033[0;37;40m", s );

    printf("\033[0;36;40m | \033[0;30;46m0x%04x\033[0;36;40m | \033[0;37;40m", frame->can_id*0x20+frame->can_dlc);fflush(stderr);
    for(int iii = 0; iii < frame->can_dlc; iii++)
        printf("\033[0;36;40m%02x \033[0;37;40m", frame->data[iii]);fflush(stderr);
    printf("\033[0;36;40m | \033[0;37;40m");fflush(stderr);
    #endif

    if(bytes_read < 0)
    {
        int errsv = errno;

        #ifdef DEBUG_CAN_READ
        fprintf(stderr, "\033[1;30;46mErr %3d\033[0;37;40m", errsv );fflush(stderr);
        printf("\033[0;37;40m\n");
        fflush(stderr);
        #endif

        return 0;
    }
    #ifdef DEBUG_CAN_READ
    else
    {
        fprintf(stderr, "\033[0;36;40mOK    \033[0;37;40m");fflush(stderr);
        printf("\033[0;37;40m\n");
        fflush(stderr);
    }
    #endif

    return 1;
}

#endif
