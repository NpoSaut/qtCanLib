#if defined WITH_CAN || defined WITH_SERIAL

#ifndef SKTCAN_H
#define SKTCAN_H

#include "iodrvmain.h"

extern int getSocket(char* iface_name);
extern int write_can_frame(int s, can_frame frame);
extern int read_can_frame(int s, struct can_frame* frame);

#endif // SKTCAN_H

#endif
