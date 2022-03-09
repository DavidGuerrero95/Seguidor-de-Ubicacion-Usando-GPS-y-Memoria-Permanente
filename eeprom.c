#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "eeprom.h"
#include "events.h"
#include "lcd.h"

volatile uint8_t contBytes = 0;
volatile uint16_t contAddress = 0;
volatile uint32_t addrMem;
volatile uint32_t contMem = 0;

uint8_t data[(LEN*2)+2] = {0x00, 0x00};
uint8_t readData[LEN];

void init_eeprom(uint32_t addresInit){
    i2c_init(I2C_PORT, 100000);
    gpio_set_function(SDA, GPIO_FUNC_I2C);
    gpio_set_function(SCL, GPIO_FUNC_I2C);
    gpio_pull_up(SDA);
    gpio_pull_up(SCL);
    addrMem = addresInit;
}

void write_eeprom(float x, float y){
    char mylat[20], mylon[20];
    volatile _mystr lat, lon;
    lat.val = x;
    lon.val = y;
    data[0] = MSB_ADDRESS(addrMem);
    data[1] = LSB_ADDRESS(addrMem);
    sprintf(mylat,"%f",x);
    sprintf(mylon,"%f",y);
    WriteManyCharactersPosition(mylat,0x05);
    WriteManyCharactersPosition(mylon,0x45);
    for (int i=0; i<LEN; i++){
        data[2+i] = lat.bytes[i];
        data[6+i] = lon.bytes[i];
    }
    
    if(i2c_write_blocking(I2C_PORT, id, data, (LEN*2)+2, false) != PICO_ERROR_GENERIC && addrMem < 8192){
        contMem += (LEN*2);
        addrMem += (LEN*2);
    } else if(addrMem >= 8192)
        ERROR = 1;
}

bool pos_eeprom(uint32_t addr){
    data[0] = MSB_ADDRESS(addr);
    data[1] = LSB_ADDRESS(addr);
    if(i2c_write_blocking(I2C_PORT, id, data, 2, true) != PICO_ERROR_GENERIC) return true;
    return false;
}

bool read_eeprom(uint8_t readbuf[], uint8_t cant){
    if(i2c_read_blocking(I2C_PORT, id, readbuf, cant, false) != PICO_ERROR_GENERIC) return true;
    return false;
}

void concatenate(uint8_t addr[], uint8_t data[], uint8_t cant, uint8_t c[]){
    for(int i=0; i<2; i++){
        c[i] = addr[i];
        printf("Valor addr: %d\n",addr[i]);
    }
    for(int i=0;i<cant;i++){
        c[2+i] = data[i];
        printf("Valor data: %d\n",data[i]);
    }
    return;
}
