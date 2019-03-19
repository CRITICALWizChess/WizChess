/*These are prototype functions for the piece movement, move electromagnet one square unless otherwise specified*/
#include <SystemClock.h>
#include <XPD.h>
#include <GPIO.h>
#include <Thread.h>

#define SQUAREDIST 1000
#define DIAGDIST 1300 //is this even needed?

void stepdelay(){
    for (int i = 0; i < 5000; i++){
        sys_clock_wait(10000);
    }
}

void north( int ){ // go one square north
    gpio_write(0x04, GPIO_A); // sets direction, whatever forward is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x01, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    
}
void east( int ){ // go one square east
    gpio_write(0x08, GPIO_A); // sets direction, whatever forward is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x02, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    
}
void south( int ){ // go one square south
    gpio_write(0x00, GPIO_A); // sets direction, whatever reverse is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x01, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    
}
void west( int ){ // go one square west
    gpio_write(0x00, GPIO_A); // sets direction, whatever reverse is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x02, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    
}
void northeast( int ){ // go one square northeast
    gpio_write(0x0C, GPIO_A); // sets direction, whatever forward|forward is
    for (int i = 0; i <= DIAGDIST; i++){
        gpio_write(0x03, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    
}
void southeast( int ){ // go one square southeast
    gpio_write(0x08, GPIO_A); // sets direction, whatever forward|reverse is
    for (int i = 0; i <= DIAGDIST; i++){
        gpio_write(0x03, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    
}
void southwest( int ){ // go one square southwest
    gpio_write(0x00, GPIO_A); // sets direction, whatever reverse|reverse is
    for (int i = 0; i <= DIAGDIST; i++){
        gpio_write(0x03, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    
}
void northeast( int ){ // go one square northwest
    gpio_write(0x04, GPIO_A); // sets direction, whatever reverse|forward is
    for (int i = 0; i <= DIAGDIST; i++){
        gpio_write(0x03, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    
}