// partest.cpp
// David Gingles

#include <SystemClock.h>
#include <XPD.h>
#include <GPIO.h>
#include <Thread.h>
#include <stdio.h>

#include "main.h"

void short_wait(){ // i = 10
  for (int i = 0; i < 10; ++i) {
    sys_clock_wait(10000);
  }
}

void long_wait(){ // i = 5000
  for (int i = 0; i < 20000; ++i) {
    sys_clock_wait(10000);
  }
}

int16_t par_receive(){ // parallel recieve from RPi
    int16_t data = 0;
    while(1){
        uint16_t is_ready = gpio_read(GPIO_E);
        if (is_ready & (1<<3)){
            break;
        }
    }
    
    while(data == 0){
        uint16_t port_e_state = gpio_read(GPIO_E); // read port E each time
        //first bit will be on E4 and fill in to E7
        bool bit8 = (port_e_state & (1<<4));
        bool bit4 = (port_e_state & (1<<5));
        bool bit2 = (port_e_state & (1<<6));
        bool bit1 = (port_e_state & (1<<7));
        if (bit1){ // pin 7
            data += 1;
            xpd_putc('1');
            xpd_putc('\n');
        }
        if (bit2){ // pin 6
            data += 2;
            xpd_putc('2');
            xpd_putc('\n');
        }
        if (bit4){ // pin 5
            data += 4;
            xpd_putc('4');
            xpd_putc('\n');
        }
        if (bit8){ // pin 4?
            data += 8;
            xpd_putc('8');
            xpd_putc('\n');
        }
    }
    // port_e_state = 0;
    // toggle the latch pin
    gpio_write(0x04 , GPIO_I);
    short_wait();
    gpio_write(0x00, GPIO_I);
    short_wait();
    
    return data;
}

int main(void)
{
    int16_t board[8][10] =
    {
        {0,  2, 3, 4, 5, 6, 4, 3, 2, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 7, 7, 7, 7, 7, 7, 7, 7, 0},
        {0, 8, 9, 10, 11, 12, 10, 9, 8, 0},
    };

    gpio_set_config((0x00 << 8), GPIO_E); // set as inputs, pins 4,5,6,7 for data
    gpio_set_config((0x04 << 8), GPIO_I); // set pin I 2 as an output
    
    // declare variables for starting position
    int16_t startX = 0;
    int16_t startY = 0;
    // Variables for future position
    int16_t finishX = 0;
    int16_t finishY = 0;
    long_wait();
    
    while(1){
        xpd_puts("Start");
        xpd_putc('\n');
        startX = par_receive();
        xpd_echo_int(startX,XPD_Flag_UnsignedDecimal); // StartX
        xpd_putc('\n');
        startY = par_receive();
        xpd_echo_int(startY, XPD_Flag_UnsignedDecimal); // StartY
        xpd_putc('\n');
        finishX = par_receive();
        xpd_echo_int(finishX, XPD_Flag_UnsignedDecimal); // FinishX
        xpd_putc('\n');
        finishY = par_receive();
        xpd_echo_int(finishY, XPD_Flag_UnsignedDecimal); // FinishY
        xpd_putc('\n');
        xpd_puts("finish");
        xpd_putc('\n');
        for (int i = 0; i < 4; i++){
            long_wait();
        }

    }
    

}