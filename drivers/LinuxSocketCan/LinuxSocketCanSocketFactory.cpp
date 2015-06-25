#include "LinuxSocketCanSocketFactory.h"

#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <errno.h>
#include <QDebug>

LinuxSocketCanSocketFactory::LinuxSocketCanSocketFactory()
{
}

LinuxSocketCanSocket *LinuxSocketCanSocketFactory::produce(QString interfaceName)
{
    // Создаем сокет
    int number = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if(number >= 0)
    {
        // Определяем индекс интерфейса
        struct ifreq ifr;
        strcpy(ifr.ifr_name, interfaceName.toStdString ().c_str ());
        ioctl(number, SIOCGIFINDEX, &ifr); // Полученный индес будет записан в поле ifr.ifr_ifindex
        if(ifr.ifr_ifindex >= 0)
        {
            // Биндим сокет на нужный интерфейс
            struct sockaddr_can addr;
            addr.can_family = AF_CAN;
            addr.can_ifindex = ifr.ifr_ifindex;
            bind(number, (struct sockaddr*)&addr, sizeof(addr));
        }
        else
        {
            int errsv = errno;
            qDebug("Не найден интерфейс %s, ошибка: %d\n", interfaceName.toStdString ().c_str (), errsv);
            number = -1;
        }
    }
    else
    {
        int errsv = errno;
        qDebug("Ошибка при открытии сокета: %d\n", errsv);
    }

    if (number < 0)
        return nullptr;
    else
        return new LinuxSocketCanSocket (number, interfaceName);
}
