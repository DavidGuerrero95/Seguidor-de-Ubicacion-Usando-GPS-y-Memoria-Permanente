#include <stdio.h>
#include "pico/stdlib.h"

#include "keyboard.h"
#include "gpio.h"

uint fil[4] = {2,3,11,12}; //indices de los puertos GPIO
uint col[4] = {6,7,8,9}; //indices de los puertos GPIO
char teclas[4][4] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
bool estado_fil[4] = {0};
bool estado_col[4] = {0};
uint fil_key = 0;
uint col_key = 0;

void keyboard_init(){
    gpio_init_outputs(fil);
    gpio_init_inputs(col);
}
char capture_key(){
    for (int i=0;i<4;i++){
        estado_col[i]= gpio_get(col[i]);
    }
    gpio_init_outputs(col);
    gpio_init_inputs(fil);
    for (int i=0;i<4;i++){
        estado_fil[i]= gpio_get(fil[i]);
    }
    for(int i=0;i<4;i++){
        if(estado_col[i]==1){
            col_key = i;
        }
        if(estado_fil[i]==1){
            fil_key = i;
        }
    }
    gpio_init_outputs(fil);
    gpio_init_inputs(col);
    return teclas[fil_key][col_key];
    
}

