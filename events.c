#include <stdio.h>
#include <string.h>
#include "events.h"
#include "general.h"
#include "gpio.h"
#include "lcd.h"
#include "keyboard.h"
#include "uart.h"
#include "hardware/uart.h"
#include "eeprom.h"
#include <math.h>

volatile _events_str _events;
volatile _events_code _flags;
volatile uint8_t debounceCounter = 0;
volatile bool    pendingCounting = false;
volatile uint8_t counter = 0;
bool init_debounce = true;
bool key_pressed = false;
bool led_alarm = false;
uint16_t led_debounce = 0;

bool flagData = false;

uint8_t time_debounce = KEYBOARD_DEBOUNCE;
uint16_t show_lcd_debounce = LCD_DEBOUNCE;

volatile char key = 0;
int pos = 0;
float min = 0.0;
float sec = 0.0;

char lat[LON_LAT_LN];
char lon[LON_LAT_LN];
char pCardinal[P_CARDINAL];
char readStringFromGPS[MAX_CHRS];
uint8_t cntReadStringFromGPS;
uint8_t cntCommas;
uint8_t cntLatLon;
char Nmea[MAX_CHRS] = "GPRMC\0";
float finalLat = 0.0;
float finalLon = 0.0;
_states currentState = SwaitString;

volatile uint8_t saveData = SECOND;
volatile uint8_t loadData = SECOND;

volatile bool loadPrueba = false;

void eventTimer(void){
	if(EV_TIMER){
		EV_TIMER = 0;
		
		if(--loadData == 0){
			loadPrueba = true;
			loadData = SECOND;
		}

		if(--saveData == 0) {
			SAVE_DATA = 1;
			saveData = SECOND;
		}

		if(--show_lcd_debounce == 0){
			lcdDebounce = true;
			show_lcd_debounce = LCD_DEBOUNCE;
		}

		if((--time_debounce == 0) & init_debounce){
            init_debounce=false;
            key = capture_key();
			key_pressed = true;
        }

		if(--time_shift ==0){
            deadline_shift=true;
        }
	}
}

void eventGpio(void){
	if(EV_GPIO){
		EV_GPIO = 0;
		time_debounce = KEYBOARD_DEBOUNCE;
        init_debounce = true;
	}
}

void eventRtc(void){
	if(EV_RTC){
		EV_RTC = 0;
		led_alarm = true;
		led_debounce = LEDDEBOUNCE;
	}
}

void eventUart(void){
	if(EV_UART){
		EV_UART = 0;
		getLatLon(data_gps);
	}
}

void getLatLon(char chrReceived){
	switch (currentState) {
        case SwaitString:
            if (chrReceived == '$'){
				cntReadStringFromGPS = 0;
				cntCommas = 0;
                currentState = Swaitcmd;
				VALIDITY = 0;
			}
            break;
        case Swaitcmd:
            readStringFromGPS[cntReadStringFromGPS++] = chrReceived;
            if (cntReadStringFromGPS == NUM_CHARS_IN_NMEA) {
				readStringFromGPS[MAX_CHRS-1] = '\0';
				if(strcmp(readStringFromGPS,Nmea) == 0)	{
					currentState = Sskipcommas1;
				}
                else  currentState = SwaitString;
			}
            break;
		case Sskipcommas1:
			cntLatLon = 0;
			if(chrReceived == ',') cntCommas++;
			if(cntCommas == 2) currentState = Svalidity;
			break;
		case Svalidity:
			if(chrReceived == 'A') VALIDITY = 1;
			else if(chrReceived == 'V'){
				VALIDITY = 0;
				currentState = SwaitString;
			}else if(chrReceived == ',' && VALIDITY) currentState = SgetLat;
			break;
        case SgetLat:
			if(chrReceived == ',')
				currentState = SgetCardinal1;
			else if(cntLatLon < LON_LAT_LN)
				lat[cntLatLon++] = chrReceived;
			break;
		case SgetCardinal1:
			cntLatLon = 0;
			if(chrReceived == ',') currentState = SgetLong;
			else pCardinal[0] = chrReceived;
			break;
		case SgetLong:
			if(chrReceived == ',') 
				currentState = SgetCardinal2;			
			else if(cntLatLon < LON_LAT_LN)
				lon[cntLatLon++] = chrReceived;
			break;
		case SgetCardinal2:
			pCardinal[1] = chrReceived;
			currentState = SLonDouble;
			break;
		case SLonDouble:
			finalLat = conversor_decimal(lat);
			finalLon = conversor_decimal(lon);
			if(pCardinal[0] == 'S') finalLat *= -1;
			if(pCardinal[1] == 'W') finalLon *= -1;
			if(VALIDITY) DATA_READY = 1;
			else DATA_READY = 0;
			currentState = SwaitString;
			break;
		default:
			break;
    }
}

float conversor_decimal(char data[]){
	float result = 0.0;
	pos = 0;
	min = 0.0, sec = 0.0;
	for(int i =0; i<LON_LAT_LN; i++){
		if(data[i] == '.') pos = i;
	}
	for(int i=0; i<pos-2;i++) {
		result = result*10 + (data[i]&0x0F); 
	}
	for(int i=pos-2;i<pos;i++){
		min = min*10 + (data[i]&0x0F);
	}
	for(int i=pos+1;i<LON_LAT_LN;i++){
		float segundo = (data[i]&0x0F);
		if(i<=pos+2)
			sec = sec*10 + segundo;
		else 
			sec += segundo/pow(10,i-(pos+2));
	}
	if(sec >= 60){
		min += 1;
		sec -= 60;
	}
	if(min >= 60) {
		result += 1;
		min -= 60;
	}
	min /= 60;
	sec /= 3600;
	result += (min + sec);
	return result;
}