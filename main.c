#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "timer.h"
#include "gpio.h"
#include "general.h"
#include "events.h"
#include "keyboard.h"
#include "lcd.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "eeprom.h"
#include "uart.h"
#include "plantilla.h"

_main_states states = SmenuWOConnection;
uint32_t  addresInitMem = 0x0000;
uint8_t readBuf[LEN*2];
uint32_t contMemory = 0;
void binToFloat(uint8_t ch[LEN*2]);
volatile _mystr latitud, longitud;
volatile bool flagUsb;

int main() {
    // STDIO: inicialización de USB-UART para entrada/salida
    stdio_init_all();
    if(!stdio_usb_connected()) flagUsb = false;
    keyboard_init();    // inicializamos el keyboard 
    lcd_init();         // inicializar lcd
    init_uart();        // inicializar el UART
    init_eeprom(addresInitMem); // Inicializar memoria eeprom
    if (!timerInitialization(TIMER_PERIOD_MS)) {
        printf("Timer initialization error.\n");
        SYSTEM_HALT();
    }

    while (true) {
        if (!PENDING_EVENTS) {
			WAITFORINT();
		}
        eventGpio();
        eventUart();
        eventTimer();
        
       // if(!VALIDITY)  states = SmenuWOConnection;
        
        if(VALIDITY && states == WaitMenu2){
            states = SmenuWConnection;
            //printf("%d",VALIDITY);
        } 
        
        if(key == 'A' && states == WaitMenu) {
            states = WriteData;
            //printf("%c",key);
        }
            
        else if(key == 'B' && states == WaitMenu && contMemory ==0){
            if(!flagUsb){
                lcd_clear();
                WriteManyCharacters(msjMenu8);
                while(!stdio_usb_connected());
            }
            states = ReadData1;
            //printf("%c",key);
            key = 0;
        }
            
        //else if(!stdio_usb_connected())
         //   states = ErrorUsb;

        if(key == 'C') {
            states = SmenuWConnection;
            //printf("2: %d",VALIDITY);
            key = 0;
        } if(key == 'D'){
            states = SmenuWConnection;
        }

        if(ERROR) states = ErrorMem;

        switch (states) {
        case SmenuWOConnection:
            lcd_clear();
            WriteManyCharacters(msjMenu1);
            states = WaitMenu2;
            break;
        case SmenuWConnection:
            lcd_clear();
            WriteManyCharactersPosition(msjMenu2,0x00);
            WriteManyCharactersPosition(msjMenu3,0x40);
            states = WaitMenu;
            break;
        case WriteData:
            if(SAVE_DATA){
                //printf("\nSAVEDATA");
            SAVE_DATA = 0;
            if(DATA_READY){
                //printf("\nDATAREADY");
                DATA_READY = 0;
                //printf("\nEscribio");
                //write_eeprom(finalLat,finalLon);
                lcd_clear();
                WriteManyCharactersPosition(msjMenu4,0x00);
                WriteManyCharactersPosition(msjMenu5,0x40);
                write_eeprom(finalLon,finalLat);
                //printf("\nLATITUD: %f, LONGITUD: %f\n",finalLat,finalLon);
                }
            }
            break;
        case ReadData1:
            imprimir_plantilla1();
            if(loadPrueba){
                loadData = false;
                if(pos_eeprom(addresInitMem) && contMemory < contMem){
                    if(read_eeprom(readBuf, LEN*2)){
                        /*printf("\nValor --> ");
                        for(int i=0; i<LEN*2; i++){
                            printf("Hexa %d: %x",i,readBuf[i]);
                        }*/
                        contMemory += LEN*2;
                        addresInitMem += LEN*2;
                        binToFloat(readBuf);
                        printf("%f,%f",longitud.val, latitud.val);
                        imprimir_plantilla2();
                        states = ReadData2;
                    }
                }
            }
            break;
        case ReadData2:
            if(loadPrueba){
                loadData = false;
                if(pos_eeprom(addresInitMem) && contMemory < contMem){
                    if(read_eeprom(readBuf, LEN*2)){
                        /*printf("\nValor --> ");
                        for(int i=0; i<LEN*2; i++){
                            printf("Hexa %d: %x",i,readBuf[i]);
                        }*/
                        contMemory += LEN*2;
                        addresInitMem += LEN*2;
                        binToFloat(readBuf);
                        printf("%f,%f\n", latitud.val,longitud.val);
                    }
                }
            }
            if(contMemory >= contMem){
                imprimir_plantilla3();
                lcd_clear();
                WriteManyCharacters("LECTURA COMPLETA");
                states = WaitMenu;
            }
            break;
        case WaitMenu:
            if (key == 'D'){
                contMem = 0;
                addrMem = addresInitMem;
                key = 0;
                contMemory = 0;
            }
            
            break;
        case WaitMenu2:
            break;
        case ErrorMem:
            lcd_clear();
            WriteManyCharacters(msjMenu7);
            states = WaitMenu;
            break;
        case ErrorUsb:
            lcd_clear();
            WriteManyCharacters(msjMenu6);
            states = WaitMenu;
            break;
        default:
            break;
        }
    }
}

void binToFloat(uint8_t ch[LEN*2]){
    for (int i=LEN; i>0; i--){           // Preparar los 4 bytes del valor a escribir
        //printf("\nLONGITUD EN :%d ----> %x",i,ch[i+3]);
        //printf("\nLATITUD EN :%d ----> %x\n",i,ch[i-1]);
        longitud.bytes[i-1] = ch[i+3];
        latitud.bytes[i-1] = ch[i-1];
    }
}


