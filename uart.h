#ifndef _UART_H
#define _UART_H

#define UART_ID uart0
#define BAUD_RATE 9600
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define UART_IRQ UART0_IRQ

extern char data_gps;
extern volatile uint8_t contUart;

void init_uart(void);
void interrupt_rx(void);

#endif