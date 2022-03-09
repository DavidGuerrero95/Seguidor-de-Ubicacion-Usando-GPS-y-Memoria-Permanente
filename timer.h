#ifndef _TIMER_H
#define _TIMER_H

#define TIMER_PERIOD_MS      10         // 10 ms for Timer Interrupt Request

extern struct repeating_timer timer;

bool timerInitialization(uint32_t);

#endif