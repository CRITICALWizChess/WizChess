// parallel comm with rpi
// David Gingles
// most basic form of communication, we will use 5 pins
// 4 pins will send the respective bits of the number
// last pin will relay completion signal

// PIN LIST FOR RPi 
// Data: 37,35,33,31
// latch: 29

#include <SystemClock.h>
#include <XPD.h>
#include <GPIO.h>
#include <Thread.h>

#include "main.h"

void short_wait(){ // i = 10
  for (int i = 0; i < 20; ++i) {
    sys_clock_wait(10000);
  }
}

void long_wait(){ // i = 5000
  for (int i = 0; i < 5000; ++i) {
    sys_clock_wait(10000);
  }
}

int16_t data_convert(char recieve[]){ // takes char to number for one byte
    if (recieve == "0001"){
        return 1;
    }
    else if (recieve == "0010"){
        return 2;
    }
    else if (recieve == "0011"){
        return 3;
    }
    else if (recieve == "0100"){
        return 4;
    }
    else if (recieve == "0101"){
        return 5;
    }
    else if (recieve == "0110"){
        return 6;
    }
    else if (recieve == "0111"){
        return 7;
    }
    else if (recieve == "1000"){
        return 8;
    }
}

int16_t par_receive(){
    bool port_e_state = gpio_read(GPIO_E);
    int16_t data = 0;

    while(1){
        //first bit will be on E4 and fill in to E7
        if (port_e_state & (1<<3)){ // does this really check pin 4?
            data += 1;
        }
        if (port_e_state & (1<<4)){ // pin 5
            data += 2;
        }
        if (port_e_state & (1<<5)){ // pin 6
            data += 4;
        }
        if (port_e_state & (1<<6)){ // pin 7
            data += 8;
        }
    }
    
    //data = data_convert(recieve);
    return data;
}

int main(void)
{
    int16_t latch = 1;
    int16_t data0,data1,data2,data3;
    char final_move[5] = "0000";
    gpio_set_config((0xC0 << 8), GPIO_C); // pins 4,5,6,7 for data, pin 3 for latch
    // recieve the data bit by bit
    // sends on high signal
    // first byte is sent right away
    

}




