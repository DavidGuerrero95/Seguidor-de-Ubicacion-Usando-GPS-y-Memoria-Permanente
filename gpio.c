#include <stdio.h>
#include "pico/stdlib.h"

#include "gpio.h"
#include "timer.h"
#include "events.h"

volatile uint8_t gpio_req = false;

/* Manejador de interrupción o callback */
void gpio_callback(uint gpio,uint32_t evento) {
    EV_GPIO = 1;    
}

void gpio_init_inputs(uint inputs[]) {
    for(uint i=0;i<4;i++){
        gpio_init(inputs[i]);
        gpio_set_pulls(inputs[i], false, true);
        gpio_set_irq_enabled_with_callback(inputs[i],GPIO_IRQ_EDGE_RISE,true, &gpio_callback);
    }
}

void gpio_init_outputs(uint outputs[]) {
    //gpio_init(PINLED);
    //gpio_set_dir(PINLED, GPIO_OUT);
    for(uint i=0;i<4;i++){
        gpio_init(outputs[i]);
        gpio_set_irq_enabled(outputs[i],GPIO_IRQ_EDGE_RISE,false);
        gpio_set_dir(outputs[i], GPIO_OUT);
        gpio_put(outputs[i],true);
    } 
}