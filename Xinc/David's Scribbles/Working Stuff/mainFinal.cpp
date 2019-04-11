// David Gingles
// XInC2 Game Board Logic
// tie into motor movement and RPi comm after completion

/*
LOGIC REFERENCE
0 - No piece
1 - Pawn   |  WHITE PIECES 1-6
2 - Rook   |
3 - Knight |
4 - Bishop |  
5 - Queen  |
6 - King   |

7 - Pawn   |  BLACK PIECES 7-12
8 - Rook   |
9 - Knight |
10 - Bishop|
11 - Queen |
12 - King  |
*/

/* MOTOR LOGIC REFERENCE
DIR: HIGH = Forward(NW), LOW = Backwards(SE)
zero switches will be set for bottom SE corner of whites side
therefore any movement after will be in forward direction
*/

#include <SystemClock.h>
#include <XPD.h>
#include <GPIO.h>
#include <Thread.h>
#include <stdio.h>

#include "main.h"

#define STEP_DIST = 1000 // steps required for one motor to move one square length
#define STEP_DIST_DIAG = 1300 // steps required for both motors to move one square length

enum PieceColor {white, Black};

void short_wait(){ // i = 10
  for (int i = 0; i < 10; ++i) {
    sys_clock_wait(10000);
  }
}

void long_wait(){ // i = 5000
  for (int i = 0; i < 5000; ++i) {
    sys_clock_wait(10000);
  }
}

int16_t absolute(int16_t value1, int16_t value2){
    // find difference for move, need diff to be positive always
    // cant use abs() with XInC2. need to do it other way
    // diffX first
    int16_t diff = 0;
    if (value1 > value2){
        diff = value1 - value2;
    }
    else {
        diff = value2 - value1;
    }
    return diff;
}

void zero(){ // Use instead of motorReset
    // space for flags if break doesn't work
    gpio_write(0xC0, GPIO_C); // DIR, SE
    gpio_write(0x80, GPIO_D); //turns magnet off
    while(1){
        uint16_t port_d_state = gpio_read(GPIO_D);
        bool is_NS_pressed = (port_d_state & (1<<5)); //supposedly read pin D5
        bool is_EW_pressed = (port_d_state & (1<<6)); //supposedly D6
        
        if (is_EW_pressed == 1){ // moves if EW axis !zeroed
            gpio_write(0x80, GPIO_A);
            short_wait();
            // xpd_puts("East\n");
        }
        if (is_EW_pressed == 0){ // moves if NS axis !zeroed
            gpio_write(0x40, GPIO_A);
            short_wait();
             // xpd_puts("West\n");
        }
        gpio_write(0x00, GPIO_A);
        short_wait();
        
        if ((is_NS_pressed == 0) && (is_EW_pressed == 0)){ // exit when both are pressed
            xpd_puts("Zero\n");
            break;
        }
        
    }
}

void beginTurn(){
    //North
    gpio_write(0x00, GPIO_C); // DIR
    for (int f = 0; f <= 350; f++)
    {
        gpio_write(0x40, GPIO_A); 
        short_wait();
        gpio_write(0x00, GPIO_A);
        short_wait();
    }
    for (int f = 0; f <= 100; f++)
    {
        gpio_write(0x80, GPIO_A); 
        short_wait();
        gpio_write(0x00, GPIO_A);
        short_wait();
    }
    xpd_puts("Ready\n");
}

/*
void motorReset(int16_t finishX, int16_t finishY){ // resets motor back to 7,11 to hit zero switchs
    // reset stuff, take distance to zero and move motor there
    // make sure electromagnet is off
    int16_t diff = 0;
    gpio_write(0xC0, GPIO_C); // sets DIR for Backwards
    // move smaller distance first
    if (finishX > finishY){
        diff = 11 - finishX;
        for (int f = 0; f <= 1200*diff; f++) // MOVE EAST ONLY
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
        diff = 7 - finishY;
        for (int f = 0; f <= 1200*diff; f++) // MOVE SOUTH ONLY
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    else {
        diff = 7 - finishY;
        for (int f = 0; f <= 1300*diff; f++) // MOVE SOUTH ONLY
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
        diff = 11 - finishX;
        for (int f = 0; f <= 1300*diff; f++) // MOVE EAST ONLY
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
}
*/

void moveToStart(int16_t startX, int16_t startY){ // moves motor to starting position of move
    // reset stuff, take distance to zero and move motor there
    gpio_write(0x01, GPIO_B);// make sure electromagnet is off
    gpio_write(0x00, GPIO_C); // sets DIR for forward
    int16_t moveX = 9 - startX;
    int16_t moveY = 7 - startY;
    for (int f = 0; f <= 1140*moveY; f++) // MOVE NORTH ONLY
    {
        gpio_write(0x40, GPIO_A); 
        short_wait();
        gpio_write(0x00, GPIO_A);
        short_wait();
    }
    for (int f = 0; f <= 1140*moveX; f++) // MOVE WEST ONLY
    {
        gpio_write(0x80, GPIO_A); 
        short_wait();
        gpio_write(0x00, GPIO_A);
        short_wait();
    }
}

void moveToLine(int16_t direction){ // Moves piece to corner of square in order to move between pieces
    // any of the four edges of the square depending on direction input
    // from white perspective going cw 1-N, 2-E, 3-S, 4-W
    // NOTE: magnet is not toggled in this function
    int16_t move = 570;
    if (direction == 1) { //North
        gpio_write(0x00, GPIO_C); // DIR
        for (int f = 0; f <= move; f++)
        {
            gpio_write(0x40, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    else if (direction == 2){ //East
        gpio_write(0x80, GPIO_C); // DIR
        for (int f = 0; f <= move; f++)
        {
            gpio_write(0x80, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    else if (direction == 3){ //South
        gpio_write(0x40, GPIO_C); // DIR
        for (int f = 0; f <= move; f++)
        {
            gpio_write(0x40, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    else if (direction == 4){ //West
        gpio_write(0x00, GPIO_C); // DIR
        for (int f = 0; f <= move; f++)
        {
            gpio_write(0x80, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
}

void moveToCorner(int16_t direction){ // Moves piece to corner of square in order to move between pieces
    // any of the four courners depending on direction input
    // from white perspective going cw 1-NE, 2-SE, 3-SW, 4-NW
    // NOTE: magnet is not toggled in this function
    int16_t move = 570;
    if (direction == 1) { //NE corner
        gpio_write(0x80, GPIO_C); // DIR
        for (int f = 0; f <= move; f++)
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    else if (direction == 2){ //SE corner
        gpio_write(0xC0, GPIO_C); // DIR
        for (int f = 0; f <= move; f++)
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    else if (direction == 3){ //SW corner
        gpio_write(0x40, GPIO_C); // DIR
        for (int f = 0; f <= move; f++)
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    else if (direction == 4){ //NW corner
        gpio_write(0x00, GPIO_C); // DIR
        for (int f = 0; f <= move; f++)
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
}

void moveStraight(int16_t direction, int16_t distance){
    // Straight line movement handled by either motor
    // direction codes: 1-North, 2-East, 3-South, 4-West
    // gpio_write(0x01, GPIO_B); // Magnet On
    int16_t move = (1140*distance);
    if (direction == 1){
        gpio_write(0x00, GPIO_C); // set for forward
        for (int f = 0; f <= (move); f++) // ONLY MOVE NORTH
        {
            gpio_write(0x40, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    if (direction == 2){
        gpio_write(0x80, GPIO_C); // set for backwards
        for (int f = 0; f <= move; f++) // ONLY MOVE EAST
        {
            gpio_write(0x80, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    if (direction == 3){
        gpio_write(0x40, GPIO_C); // set for backwards
        for (int f = 0; f <= move; f++) // ONLY MOVE SOUTH
        {
            gpio_write(0x40, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    if (direction == 4){
        gpio_write(0x00, GPIO_C); // set for forward
        for (int f = 0; f <= move; f++) // ONLY MOVE WEST
        {
            gpio_write(0x80, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }

}

void moveDiagonal(int16_t direction, int16_t distance){
    // diagonal line movement handled by both motors simaltaniously
    // direction codes: 1-NE, 2-SE, 3-SW, 4-NW (from white perspective)
    // gpio_write(0x01, GPIO_B); // Magnet on
    int16_t move = (1140*distance);
    if (direction == 1){
        gpio_write(0x80, GPIO_C); // DIR
        for (int f = 0; f <= move; f++) // NE
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    if (direction == 2){
        gpio_write(0xC0, GPIO_C); // DIR
        for (int f = 0; f <= move; f++) // SE
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    if (direction == 3){
        gpio_write(0x40, GPIO_C); // DIR
        for (int f = 0; f <= move; f++) // SW
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    if (direction == 4){
        gpio_write(0x00, GPIO_C); // DIR
        for (int f = 0; f <= move; f++) // NW
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }

}

void centerPiece(int16_t move){
    // no change to direction pins
    // move is either 1 for N/S, 2 for E/W
    // int16_t dist = 140;
    if (move == 1){
        for (int f = 0; f <= (220); f++) // N/S
        {
            gpio_write(0x40, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    else if (move == 2){
        for (int f = 0; f <= (220); f++) // E/W
        {
            gpio_write(0x80, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    else if (move == 3){
        for (int f = 0; f <= (150); f++) // dia
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
}

void pieceRemoval(int16_t finishX, int16_t finishY, int16_t graveLocation[2]){
    // handles piece removal
    int16_t graveX = 0, graveY = 0;    
    graveX = absolute(graveLocation[1], finishX); // adjusted to work with the corner movement
    graveY = absolute(graveLocation[0], finishY) - 1;
    gpio_write(0x00,GPIO_D); // magnet on
    // proceed with movement for removal, first figure out whose turn it is from graveyard selected
    // move Y axis then X
    if (graveLocation[1] == 0){ // white piece taken
        // movement to west side grave
        if (finishY > 3){ // bottom half of board
            moveToLine(1); // North
            moveStraight(4,graveX); // West
            moveToLine(1);
        }
        else{
            moveToLine(3); // South line
            moveStraight(4,graveX); // West
            moveToLine(3);
        }
    }
    else {
        // movement to east side grave
        if (finishY > 3){ // bottom half of board
            moveToLine(1); // North
            moveStraight(2,graveX); // East
            moveToLine(1);
        }
        else{
            moveToLine(3); // South line
            moveStraight(2,graveX); // East
            moveToLine(3);
        }
    }
    gpio_write(0x80,GPIO_D); // magnet off
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

int main(void){
    // this loop will never end
    while(1){
        // Board dimensions 8 units in length and 12 units in width
        // Respective player graveyards will be to their right hand side
        // Initiate Board
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

        gpio_set_config((0xC0 << 8), GPIO_C); //sets pins 6 and 7 on C to output
        gpio_set_config((0xC0 << 8), GPIO_A); //sets pins 6 and 7 on A to output
        gpio_set_config((0x80 << 8), GPIO_D); //sets pins on B to input for zeroing
        gpio_set_config((0x00 << 8), GPIO_E); // pins 4,5,6,7 for data, pin 3 reading complete
        gpio_set_config((0x04 << 8), GPIO_I); // set pin I 2 as an output for comm

        //char recieve[] = "4247"; // variabe for comm with RPi 
        int16_t turns = 1; // number of turns in game
        bool is_white_turn = 1;
        int16_t piece = 0; // to track piece that is selected
        int16_t graveWhite[2] = {1,0}; // y,x
        int16_t graveBlack[2] = {6,9}; // y,x
        //int16_t deadwhite = 0, deadblack = 0;
        // declare variables for starting position
        int16_t startX = 0;
        int16_t startY = 0;
        // Variables for future position
        int16_t finishX = 0;
        int16_t finishY = 0;
        // Variables for difference of position
        int16_t diffX = 0;
        int16_t diffY = 0;

        while(1){

            long_wait();
            zero();     // make sure motor is zero
            beginTurn();
            /*
            for (int i=0; i<4; i++){ // Assign the recieve values
                if (i==0){
                   startX = (recieve[i] - '0'); // compensate for Graveyard
                }
                else if (i==1){
                    startY = (recieve[i] - '0') - 1;
                }
                else if (i==2){
                    finishX = (recieve[i] - '0');
                }
                else if (i==3){
                    finishY = (recieve[i] - '0') - 1;
                }
            }
            // This is all for testing purposes
            xpd_echo_int(startX,XPD_Flag_UnsignedDecimal);
            xpd_echo_int(startY, XPD_Flag_UnsignedDecimal);
            xpd_echo_int(finishX, XPD_Flag_UnsignedDecimal);
            xpd_echo_int(finishY, XPD_Flag_UnsignedDecimal);
            xpd_putc('\n');
            */
        
            // location assignment from RPi
            xpd_puts("Start");
            xpd_putc('\n');
            startX = par_receive();
            xpd_echo_int(startX,XPD_Flag_UnsignedDecimal); // StartX
            xpd_putc('\n');
            if (startX == 9){
                break;
            }
            startY = par_receive() - 1;
            xpd_echo_int(startY, XPD_Flag_UnsignedDecimal); // StartY
            xpd_putc('\n');
            finishX = par_receive();
            xpd_echo_int(finishX, XPD_Flag_UnsignedDecimal); // FinishX
            xpd_putc('\n');
            finishY = par_receive() - 1;
            xpd_echo_int(finishY, XPD_Flag_UnsignedDecimal); // FinishY
            xpd_putc('\n');
            xpd_puts("finish");
            xpd_putc('\n');
            

            diffX = absolute(startX, finishX); // calculate x axis move distance 
            diffY = absolute(startY, finishY); // calculate y axis move distance

            // Is it a capture move? piece removal here
            if (board[finishY][finishX] != 0){
                //piece = board[finishY][finishX];
                board[finishY][finishX] = 0;
                if (is_white_turn) {  // If its whites turn they are capturing black pieces
                    moveToStart(finishX,finishY); // move to capture location
                    pieceRemoval(finishX,finishY,graveBlack);
                    //board[graveBlack[0]][graveBlack[1]] = piece;
                    graveBlack[0] = graveBlack[0] - 1;
                    if (graveBlack[0] == 1){
                        graveBlack[0] = 6;
                    }
                    xpd_puts("Black piece taken\n");
                }
                else {
                    moveToStart(finishX, finishY); // move to capture location
                    pieceRemoval(finishX,finishY,graveWhite);
                    //board[graveWhite[0]][graveWhite[1]] = piece;
                    graveWhite[0] = graveWhite[0] + 1;
                    if (graveWhite[0] == 6){
                        graveWhite[0] = 0;
                    }
                    xpd_puts("White piece taken\n");
                }
                zero(); // zero after capture
                beginTurn();
            }
            // piece location ol' swapperoo
            piece = board[startY][startX]; // swap piece position with end position
            board[startY][startX] = 0;
            board[finishY][finishX] = piece;

            // display board state for rows 2 and 4
            xpd_echo_int(diffX, XPD_Flag_UnsignedDecimal);
            xpd_putc('\n');
            xpd_echo_int(diffY, XPD_Flag_UnsignedDecimal);
            xpd_putc('\n');

            //while(1){} /////////////////////////////////////////////////////////////////////// IT'S A TRAP /////////////////////////////////////////////////

            moveToStart(startX, startY); // move motors to start position

            gpio_write(0x00, GPIO_D); // Magnet on

            // Is the knight moving?  (diffX != 0) && (diffY != 0) && (diffX != diffY)
            if ((piece == 3) | (piece == 9)){
                //knight is moving somewhere
                // 8 options for knight move, 4 to the north and 4 to the south
                if (startY < finishY){
                    // 4 south options
                    // figure out east or west
                    if (startX < finishX){
                        // SE, find difference on last two options
                        moveToLine(2); // move to SE corner
                        moveToLine(3);
                        if (diffX > diffY){
                            moveStraight(2,1); // move east 1 square
                        }
                        else {
                            moveStraight(3,1); // move south 1 square
                        }
                        moveToCorner(2); // move to center of square
                        centerPiece(3);
                    }
                    else{
                        // SW, find the last two options
                        moveToLine(4); // move to SW corner
                        moveToLine(3);
                        if (diffX > diffY){
                            moveStraight(4,1); // west
                        }
                        else{
                            moveStraight(3,1); // south
                        }
                        moveToCorner(3); // move back to center of square
                        centerPiece(3);
                    }
                }
                else if (startY > finishY){
                    // 4 north options, figure out east or west
                    if (startX < finishX){
                        // NE, find difference on last two
                        moveToLine(2);
                        moveToLine(1);
                        if (diffX > diffY){
                            moveStraight(2,1); // East
                        }
                        else{
                            moveStraight(1,1); // North
                        }
                        moveToCorner(1); // move back to center of square
                        centerPiece(3);
                    }
                    else if (startX > finishX){
                        // NW, find difference between last two
                        moveToLine(4);
                        moveToLine(1);
                        if (diffX > diffY){
                            moveStraight(4,1); // West
                        }
                        else {
                            moveStraight(1,1); // North
                        }
                        moveToCorner(4); // move back to center of square
                        centerPiece(3);
                    }
                }
            }
            // Diagonal
            else if (diffX == diffY){
                if (startX < finishX){ // EAST
                    if (startY < finishY){ 
                        moveDiagonal(2,diffX); //SE
                    }
                    else if (startY > finishY){
                        moveDiagonal(1,diffX); //NE
                    }
                }
                else if (startX > finishX){ // WEST
                    if (startY < finishY){
                        moveDiagonal(3,diffX); //SW
                    }
                    else if (startY > finishY){
                        moveDiagonal(4,diffX); //NW
                    }
                }
                centerPiece(3);
            }
            // analyze the X or row direction (horizontal movement)
            else if (diffY == 0){
                if (startX < finishX){
                    moveStraight(2,diffX); // East
                }
                else{
                    moveStraight(4,diffX); // West
                }
                centerPiece(2);
            }
            // analyze the Y or Column direction (vertical movement)
            else if (diffX == 0){
                if (startY < finishY){
                    moveStraight(3,diffY); // South
                    xpd_puts("South\n");
                }
                else{
                    moveStraight(1,diffY); // North
                    xpd_puts("North\n");
                }
                centerPiece(1);
            }

            gpio_write(0x80, GPIO_D); // Magnet off

            if (turns % 2) {
                // end of whites turn, switch to black
                is_white_turn = 0;
                xpd_puts("Black's turn\n");
            }
            else {
                // end of blacks turn, switch to white
                is_white_turn = 1;
                xpd_puts("White's turn\n");
            }
            turns += 1;
            //zero(); // zero the motor   

            //while(1){} /////////////////////////////////////////////////////////////////////// IT'S A TRAP /////////////////////////////////////////////////
        }
    }
    return 0;
}
