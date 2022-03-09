#ifndef MYEVENTS_H_
#define MYEVENTS_H_

#include "pico/stdlib.h"

typedef union {
	uint8_t reg;
	struct {
		uint8_t flag0 : 1;
		uint8_t flag1 : 1;
		uint8_t flag2 : 1;
		uint8_t flag3 : 1;
		uint8_t flag4 : 1;
		uint8_t flag5 : 1;
		uint8_t flag6 : 1;
		uint8_t flag7 : 1;
	}flags;
}_events_str;

extern volatile _events_str _events;

#define PENDING_EVENTS	_events.reg
#define EV_TIMER		_events.flags.flag0
#define EV_GPIO			_events.flags.flag1
#define EV_RTC			_events.flags.flag2
#define EV_UART			_events.flags.flag3


typedef union {
	uint8_t reg;
	struct {
		uint8_t flag0 : 1;
		uint8_t flag1 : 1;
		uint8_t flag2 : 1;
		uint8_t flag3 : 1;
		uint8_t flag4 : 1;
		uint8_t flag5 : 1;
		uint8_t flag6 : 1;
		uint8_t flag7 : 1;
	}flags;
}_events_code;

extern volatile _events_code _flags;

#define VALIDITY		_flags.flags.flag0
#define DATA_READY		_flags.flags.flag1
#define SAVE_DATA		_flags.flags.flag2
#define ERROR			_flags.flags.flag3

typedef enum {SwaitString, Swaitcmd, Sskipcommas1, Svalidity, SgetLat, SgetCardinal1, SgetLong, SgetCardinal2, SLatDouble, SLonDouble} _states;
typedef enum {SmenuWOConnection,SmenuWConnection,WriteData,ReadData1,ReadData2,WaitMenu, ErrorUsb, ErrorMem, WaitMenu2} _main_states;


extern volatile char key;
extern bool key_pressed;

extern float finalLat;
extern float finalLon;

extern volatile bool loadPrueba;
extern volatile uint8_t saveData;
extern volatile uint8_t loadData;

#define NUM_CHARS_IN_NMEA 5
#define NUM_CHARS_IN_LAT_LON 8
#define MAX_CHRS 6
#define LON_LAT_LN 11
#define P_CARDINAL 2

#define DEBOUNCECOUNT	3			// Timer generates INTs each 10ms (3x10ms = 30ms for debouncing)
#define LEDDEBOUNCE		6000
#define SECOND			200

void eventTimer(void);
void eventGpio(void);
void eventRtc(void);
void eventUart(void);
void getLatLon(char chrReceived);
float conversor_decimal(char data[]);
#endif