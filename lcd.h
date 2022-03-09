#ifndef LCD_H_
#define LCD_H_

#include "pico/stdlib.h"

typedef union {
    uint8_t reg;
	struct {
		uint8_t DB0P 	: 1;
		uint8_t DB1P 	: 1;
		uint8_t DB2P 	: 1;
		uint8_t DB3P 	: 1;
		uint8_t DB4P 	: 1;
		uint8_t DB5P 	: 1;
		uint8_t DB6P 	: 1;
		uint8_t DB7P 	: 1;
        
	}BITS;
}_lcd_str;

typedef struct {
	uint8_t EP		: 1;
	uint8_t RWP  	: 1;
	uint8_t RSP  	: 1;
	uint8_t 		: 5;
}_lcd_flags;

extern volatile uint8_t lcdCounter;
extern volatile bool lcdDebounce;
extern volatile _lcd_str _lcd;
extern volatile _lcd_flags _lcdFlags;

#define LCD		_lcd.reg
#define DB0		_lcd.BITS.DB0P
#define DB1		_lcd.BITS.DB1P
#define DB2		_lcd.BITS.DB2P
#define DB3		_lcd.BITS.DB3P
#define DB4		_lcd.BITS.DB4P
#define DB5		_lcd.BITS.DB5P
#define DB6		_lcd.BITS.DB6P
#define DB7		_lcd.BITS.DB7P

#define RW		_lcdFlags.RWP
#define RS		_lcdFlags.RSP
#define E		_lcdFlags.EP

#define pRS  26
#define pRW  27
#define pE   18
#define pD4  19
#define pD5  20
#define pD6  21
#define pD7  22
#define buzy 22

#define LCD_DEBOUNCE 100 //debounce*Periodo Timer
#define time_shift_ 	50

extern volatile bool deadline_shift;
extern int num_shift;
extern uint8_t time_shift;

void lcd_init(void);
void lcd_sendData(uint flag);
void lcd_busy(void);
void lcd_display_on_off(bool display,bool cursor,bool blink);
void EntryModSet(bool ID, bool SH);
void lcd_wait(void);

void WriteCommandToLCD(unsigned char Command, uint32_t waitingtime);
void WriteDataToLCD(char LCDChar);
void lcd_set_dd_ram_address(unsigned char Dir);
void writeInnitLCD(unsigned char Command);
void gpio_listOutput(uint ports[6]);
void gpio_output(uint8_t pin);
void gpio_input(uint port);
void WriteManyCharactersPosition(char cadena[], unsigned char Dir);
void WriteManyCharacters(char cadena[]);
void lcd_shift(bool sc, bool rl);
void lcd_clear(void);
void move_display_normal(int var);

#endif