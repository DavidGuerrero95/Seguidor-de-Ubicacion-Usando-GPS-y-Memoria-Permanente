#ifndef _GENERAL_H
#define _GENERAL_H

#define SYSTEM_HALT() { printf("¡Sistema detenido!\n"); while(true) {}; }
#define WAITFORINT()  __asm volatile ("wfi")
#endif