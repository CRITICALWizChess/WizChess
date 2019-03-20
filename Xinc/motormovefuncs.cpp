/*These are prototype functions for the piece movement, move electromagnet one square unless otherwise specified*/
#include <SystemClock.h>
#include <XPD.h>
#include <GPIO.h>
#include <Thread.h>

#define SQUAREDIST 1000
#define DIAGDIST 1300 //is this even needed?
#define N_NW 0x04
#define NE 0x0C
#define E_SE 0x08
#define S_SW_W 0x00

void stepdelay(){
    for (int i = 0; i < 5000; i++){
        sys_clock_wait(10000);
    }
}

void north( int ){ // go one square north
    gpio_write(N_NW, GPIO_A); // sets direction, whatever forward is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x01, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    
}
void east(){ // go one square east
    gpio_write(E_SE, GPIO_A); // sets direction, whatever forward is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x02, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    
}
void south(){ // go one square south
    gpio_write(S_SW_W, GPIO_A); // sets direction, whatever reverse is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x01, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    
}
void west(){ // go one square west
    gpio_write(S_SW_W, GPIO_A); // sets direction, whatever reverse is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x02, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    
}
void northeast(){ // go one square northeast
    gpio_write(NE, GPIO_A); // sets direction, whatever forward|forward is
    for (int i = 0; i <= DIAGDIST; i++){
        gpio_write(0x03, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    
}
void southeast(){ // go one square southeast
    gpio_write(E_SE, GPIO_A); // sets direction, whatever forward|reverse is
    for (int i = 0; i <= DIAGDIST; i++){
        gpio_write(0x03, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    
}
void southwest(){ // go one square southwest
    gpio_write(S_SW_W, GPIO_A); // sets direction, whatever reverse|reverse is
    for (int i = 0; i <= DIAGDIST; i++){
        gpio_write(0x03, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    
}
void northwest(){ // go one square northwest
    gpio_write(0x04, GPIO_A); // sets direction, whatever reverse|forward is
    for (int i = 0; i <= DIAGDIST; i++){
        gpio_write(0x03, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    
}
void knorth(){ //knight to forward right
    gpio_write(0x0C, GPIO_A); //whatever dir NE is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(0x04, GPIO_A); // whatever direction N is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x01, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(0x0C, GPIO_A); //whatever dir NE is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
}
void knortheast(){ //knight to right forward
    gpio_write(0x0C, GPIO_A); //whatever dir NE is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(0x08, GPIO_A); // whatever direction E is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x01, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(0x0C, GPIO_A); //whatever dir NE is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
}
void keast(){ // knight to right backward
    gpio_write(0x08, GPIO_A); //whatever dir SE is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(0x08, GPIO_A); // whatever direction 8 is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x01, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(0x08, GPIO_A); //whatever dir SE is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
}
void ksoutheast(){ // FINISH THIS
    gpio_write(0x0C, GPIO_A); //whatever dir NE is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(0x04, GPIO_A); // whatever direction N is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x01, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(0x0C, GPIO_A); //whatever dir NE is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
}