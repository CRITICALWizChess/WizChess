/*These are prototype functions for the piece movement, move electromagnet one square unless otherwise specified*/
#include <SystemClock.h>
#include <XPD.h>
#include <GPIO.h>
#include <Thread.h>

#define SQUAREDIST 1000
#define DIAGDIST 1300 //is this even needed?
#define N_NW 0x04 // north direction
#define NE 0x0C //whatever dir NE is
#define E_SE 0x08 //etc
#define S_SW_W 0x00 // honestly we can probably just pick a convention and wire the motors accordingly

void stepdelay(){
    for (int i = 0; i < 5000; i++){
        sys_clock_wait(10000);
    }
}

void north(){ // go one square north
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
    gpio_write(N_NW, GPIO_A); // sets direction, whatever reverse|forward is
    for (int i = 0; i <= DIAGDIST; i++){
        gpio_write(0x03, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
}
void knorth(){ //knight to forward right
    gpio_write(NE, GPIO_A); //whatever dir NE is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(N_NW, GPIO_A); // whatever direction N is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x01, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(NE, GPIO_A); //whatever dir NE is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
}
void knortheast(){ //knight to right forward
    gpio_write(NE, GPIO_A); 
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(E_SE, GPIO_A); // whatever direction E is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x02, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(NE, GPIO_A); //whatever dir NE is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
}
void keast(){ // knight to right backward
    gpio_write(E_SE, GPIO_A); //whatever dir SE is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(E_SE, GPIO_A); // whatever direction E is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x02, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(E_SE, GPIO_A); //whatever dir SE is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
}
void ksoutheast(){ // knight to backward right
    gpio_write(E_SE, GPIO_A); //whatever dir SE is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(S_SW_W, GPIO_A); // whatever direction S is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x01, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(E_SE, GPIO_A); //whatever dir SE is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
}
void ksouth(){ // knight to backward left
    gpio_write(S_SW_W, GPIO_A); //whatever dir SW is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(S_SW_W, GPIO_A); // whatever direction S is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x01, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(S_SW_W, GPIO_A); //whatever dir SW is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
}
void ksouthwest(){ // knight to left backward
    gpio_write(S_SW_W, GPIO_A); //whatever dir SW is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(S_SW_W, GPIO_A); // whatever direction W is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x02, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(S_SW_W, GPIO_A); //whatever dir SW is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
}
void kwest(){ // knight to left forward
    gpio_write(N_NW, GPIO_A); //whatever dir NW is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(S_SW_W, GPIO_A); // whatever direction W is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x02, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(N_NW, GPIO_A); //whatever dir NW is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
}
void knorthwest(){ // knight to forward left
    gpio_write(N_NW, GPIO_A); //whatever dir NW is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(N_NW, GPIO_A); // whatever direction N is
    for (int i = 0; i <= SQUAREDIST; i++){
        gpio_write(0x01, GPIO_A); //replace with the pin config you plan on changing
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
    gpio_write(N_NW, GPIO_A); //whatever dir NW is
    for (int i = 0; i <= (DIAGDIST/2); i++){
        gpio_write(0x03, GPIO_A);
        stepdelay();
        gpio_write(0x00, GPIO_A);
        stepdelay();
    }
}
// zeros the motors to a known position
void zero(){
    // space for flags if break doesn't work
    while(true){
        uint16_t port_b_state = gpio_read(GPIO_B);
        bool is_NS_pressed = (port_b_state & (1<<2)); //supposedly read pin 2 
        bool is_EW_pressed = (port_b_state & (1<<3)); //supposedly 3
        gpio_write(0x08, GPIO_A); //towards the motors, we are going to have to figure this out
        if (!is_NS_pressed){ // moves if NS axis !zeroed
            gpio_write(0x01, GPIO_A);
            stepdelay();
        }
        if (!is_EW_pressed){ // moves if EW axis !zeroed
            gpio_write(0x02, GPIO_A);
            stepdelay();
        }
        gpio_write(0x00, GPIO_A);
        stepdelay();
        if (is_NS_pressed && is_EW_pressed){
            break;
        }
    }
}
// moves the electromagnet to specified square. does not activate magnet
void movementbuild(uint16_t direct, uint16_t squares){ 
    
        switch(direct){
            case 1:
                for (int i = 0; i <= squares; i++){
                    north();
                }
                if (squares = 0){
                    knorth();
                }
            case 2:
                for (int i = 0; i <= squares; i++){
                    northeast();
                }
                if (squares = 0){
                    knortheast();
                }
            case 3:
                for (int i = 0; i <= squares; i++){
                    neast();
                }
                if (squares = 0){
                    keast();
                }
            case 4:
                for (int i = 0; i <= squares; i++){
                    southeast();
                }
                if (squares = 0){
                    ksoutheast();
                }
            case 5:
                for (int i = 0; i <= squares; i++){
                    south();
                }
                if (squares = 0){
                    ksouth();
                }
            case 6:
                for (int i = 0; i <= squares; i++){
                    southwest();
                }
                if (squares = 0){
                    ksouthwest();
                }
            case 7:
                for (int i = 0; i <= squares; i++){
                    west();
                }
                if (squares = 0){
                    kwest();
                }
            case 8:
                for (int i = 0; i <= squares; i++){
                    northwest();
                }
                if (squares = 0){
                    knorthwest();
                }
        }
    
}
uint16_t gameplaymove(){
    //i honestly don't know where I want to go with this at this point
    error = 0;
    return error;
}