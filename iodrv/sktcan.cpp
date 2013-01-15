#include "sktcan.h"

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

int write_can_frame(int s, struct can_frame* frame)
{
    if (!s)
    {
        printf("send_can_frame: сокет не существует\n");
        fflush(stdout);
    }

    errno = 0;
    int bytes_sent = write(s, frame, sizeof(struct can_frame));
    if(bytes_sent < 0)
    {
        int errsv = errno;
        fprintf(stderr, "send_can_frame: ошибка при отправке: %d\n", errsv);
        fflush(stderr);
        return 0;
    }
/*
//#ifdef DEBUG
    //printf("Успешно отправлено %d байт на %s\n", bytes_sent, iface_name);
    printf("send_can_frame: успешно отправлено %d байт\n", bytes_sent);
//#endif // DEBUG
*/
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
    if(bytes_read < 0)
    {
        int errsv = errno;
        fprintf(stderr, "read_can_frame: ошибка при чтении: %d\n", errsv);
        fflush(stderr);
        return 0;
    }
/*
//#ifdef DEBUG
    printf("read_can_frame: принято сообщение:\n");
    printf("длина: %d\n", (*frame).can_dlc);
    printf("id: %d\n", (*frame).can_id);
    printf("data: [");
    int i;
    for(i = 0; i < 8; i++)
        printf("0x%02x, ", (*frame).data[i]);
    printf("]\n");
//#endif // DEBUG
*/
    return 1;
}

