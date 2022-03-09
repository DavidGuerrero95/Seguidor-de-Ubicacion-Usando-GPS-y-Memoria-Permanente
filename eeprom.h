#ifndef _EEPROM_H
#define _EEPROM_H

#define I2C_PORT i2c0
#define id          0x50
#define SCL         5
#define SDA         4

void write_eeprom(float x, float y);
void init_eeprom(uint32_t addresInit);
void concatenate(uint8_t addr[], uint8_t data[], uint8_t cant, uint8_t c[]);
bool read_eeprom(uint8_t readbuf[], uint8_t cant);
bool pos_eeprom(uint32_t addr);

extern volatile uint8_t saveData;
extern volatile uint8_t contBytes;
extern volatile uint16_t contAddress;
extern volatile uint32_t addrMem;
extern volatile uint32_t contMem;

#define LEN     4

typedef union {
    float val;
    uint8_t bytes[LEN];
} _mystr;



// Conversión para enviar la dirección de escritura/lectura en dos bytes (24LC32, 24LC64, 24LC128, 24LC256)
#define MSB_ADDRESS(X)  ((X >> 8) & 0xFF)
#define LSB_ADDRESS(X)  ((X) & 0xFF)

#endif