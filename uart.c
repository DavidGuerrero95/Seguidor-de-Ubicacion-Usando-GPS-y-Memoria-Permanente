#include <stdio.h>
#include "events.h"
#include "gpio.h"
#include "uart.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "events.h"

volatile uint8_t contUart = 0;

char data_gps;

void init_uart(void){
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    uart_set_format (UART_ID, DATA_BITS, STOP_BITS, PARITY);
    uart_set_fifo_enabled(UART_ID, false);
    uart_set_irq_enables(UART_ID, true, false);
    irq_set_exclusive_handler(UART_IRQ, interrupt_rx);
    irq_set_enabled(UART_IRQ, true);
    //printf("\nInicializo\n");
}

void interrupt_rx(void){
    data_gps = uart_getc(UART_ID);
    contUart++;
    printf("%c",data_gps);
    EV_UART = 1;
}