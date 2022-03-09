#include <stdio.h>
#include "pico/stdlib.h"

#include "timer.h"
#include "events.h"

struct repeating_timer timer;

/* callback for Timer Interrupt */
bool timerCallback(struct repeating_timer *t) {
    EV_TIMER = 1;
    return true;
}

/* Rutina para preparar el timer */
bool timerInitialization(uint32_t delay_ms) {
    if (!add_repeating_timer_ms(-delay_ms, timerCallback, NULL, &timer))
        return false;
    else
        return true;    
}