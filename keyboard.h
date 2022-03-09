#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#define KEYBOARD_DEBOUNCE 5 //debounce*Periodo Timer
void keyboard_init();
char capture_key();
#endif