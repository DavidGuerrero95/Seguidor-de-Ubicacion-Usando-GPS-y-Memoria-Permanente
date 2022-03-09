#include <stdio.h>
#include "lcd.h"
#include "hardware/gpio.h"

volatile uint8_t lcdCounter = 0;
volatile bool lcdDebounce = false;
volatile _lcd_str _lcd;
volatile _lcd_flags _lcdFlags;
int num_shift=0;
uint8_t time_shift = time_shift_;
volatile bool deadline_shift = false;

uint ports[6] = {pRS,pRW,pD7,pD6,pD5,pD4};

/*inicializacion del LCD*/
void lcd_init(void){
    gpio_listOutput(ports);
    gpio_output(pE);
    sleep_ms(15);
    sleep_ms(15);
    writeInnitLCD(0x30);
    sleep_us(4200);
    writeInnitLCD(0x30);
    sleep_us(100);
    writeInnitLCD(0x30);
    writeInnitLCD(0x20);
    WriteCommandToLCD(0x28, 42);    // Set Function
    lcd_display_on_off(1,0,0);  
    WriteCommandToLCD(0x01,1640);    // Display Clear
}

/*Set Display*/
void lcd_display_on_off(bool display,bool cursor,bool blink){
    // Parpadeo o no
    DB7 = 0;
    DB6 = 0;
    DB5 = 0;
    DB4 = 0;
    DB3 = 1;
    DB2 = display;
    DB1 = cursor;
    DB0 = blink;
    WriteCommandToLCD(LCD,42);
}

void lcd_set_dd_ram_address(unsigned char Dir){
    LCD = 0x80 | (Dir & 0x7F);
    WriteCommandToLCD(LCD,42);
}

void writeInnitLCD(unsigned char Command){
    RS = 0;
    RW = 0;
    LCD = Command;
    lcd_sendData(1);
    lcd_wait();
}

void WriteCommandToLCD(unsigned char Command, uint32_t waitingtime){
    RS = 0;
    RW = 0;
    LCD = Command;
    lcd_sendData(0);
    lcd_wait();
    LCD = Command<<4;
    lcd_sendData(1);
    lcd_wait();
    sleep_us(waitingtime);
}

void WriteDataToLCD(char LCDChar) {
    RS = 1;
    RW = 0;
    LCD = (LCDChar&0xF0);
    lcd_sendData(0);
    lcd_wait();
    LCD = ((LCDChar<<4)&0xF0);
    lcd_sendData(1);
    lcd_wait();
}

/*Entry Mod Set*/
void EntryModSet(bool ID, bool SH){
    DB7 = 0;
    DB6 = 0;
    DB5 = 0;
    DB4 = 0;
    DB3 = 0;
    DB2 = 1;
    DB1 = ID;
    DB0 = SH;
    WriteCommandToLCD(LCD, 42);
}

void lcd_wait(void){
    E = 1;
    gpio_put(pE,E);
    sleep_us(45);
    E = 0;
    gpio_put(pE,E);
    sleep_us(45);
}

void lcd_shift(bool sc, bool rl){
    DB7 = 0;
    DB6 = 0;
    DB5 = 0;
    DB4 = 1;
    DB3 = sc;
    DB2 = rl;
    DB1 = 0;
    DB0 = 0;
    WriteCommandToLCD(LCD, 42);
}

void WriteManyCharactersPosition(char cadena[], unsigned char Dir){
    char *p;
    p = cadena;
    lcd_set_dd_ram_address(Dir);
    while (*p != '\0'){
        WriteDataToLCD(*p);
        p++;
    }
}

void WriteManyCharacters(char cadena[]){
    char *p;
    p = cadena;
    while (*p != '\0'){
        WriteDataToLCD(*p);
        p++;
    }
}

/*Busy LCD*/
void lcd_busy(void){
    
    gpio_input(pD7);
    RS = 0;
    RW = 1;
    DB6 = 0;
    DB5 = 0;
    DB4 = 0;
    DB7 = 1;
    E = 1;
    lcd_sendData(1);
    while(gpio_get(pD7)){
        E = 0;
    }
    gpio_output(pD7);
}

/*Enviar datos*/
void lcd_sendData(uint flag){
    uint outputs[6] = {RS,RW,DB7,DB6,DB5,DB4};
    switch (flag) {
    case 0:
        for(uint i=0; i<6; i++){
            gpio_put(ports[i], outputs[i]);
        }
        break;
    case 1:
        for(uint i=2; i<6; i++){
            gpio_put(ports[i], outputs[i]);
        }
        break;
    default:
        for(uint i=0; i<6; i++){
            gpio_put(ports[i], outputs[i]);
        }
        break;
    } 
}

void lcd_clear(void){
    WriteCommandToLCD(0x01,1640); // LCD CLEAR
}

void gpio_listOutput(uint ports[6]){
    
    for(uint8_t i=0; i<=6 ; i++){
        gpio_init(ports[i]); // Se inicializan los pins del LCD 
        gpio_set_dir(ports[i], GPIO_OUT); // Se configuran como salidas
    } 
}

void gpio_output(uint8_t pin){
    gpio_init(pin); // Se inicializan los pins del LCD 
    gpio_set_dir(pin, GPIO_OUT); // Se configuran como salidas
}

void gpio_input(uint port){
    gpio_init(port);
    gpio_set_dir(port,GPIO_IN);
}

void move_display_normal(int var){
    if(deadline_shift){
        if(num_shift<var){
            num_shift++;
            lcd_shift(1,0);
        }else if(num_shift>=var && num_shift<(var*2)){
            num_shift++;
            lcd_shift(1,1);
            }else {
                num_shift = 0;
            }
            deadline_shift=false;
            time_shift=time_shift_;
    }
}