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

void motorReset(int16_t finishX, int16_t finishY){ // resets motor back to 7,11 to hit zero switchs
    // reset stuff, take distance to zero and move motor there
    // make sure electromagnet is off
    int16_t diff = 0;
    gpio_write(0x00, GPIO_C); // sets DIR for Backwards
    // move smaller distance first
    if (finishX > finishY){
        diff = 11 - finishX;
        for (int f = 0; f <= 1300*diff; f++) // MOVE EAST ONLY
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
        diff = 7 - finishY;
        for (int f = 0; f <= 1300*diff; f++) // MOVE SOUTH ONLY
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

void moveToStart(int16_t startX, int16_t startY){ // moves motor to starting position of move
    // reset stuff, take distance to zero and move motor there
    // make sure electromagnet is off
    gpio_write(0x81, GPIO_C); // sets DIR for forward
    // move smaller distance first
    if (startX > startY){
        for (int f = 0; f <= 1300*startX; f++) // MOVE WEST ONLY
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
        for (int f = 0; f <= 1300*startY; f++) // MOVE NORTH ONLY
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    else {
        for (int f = 0; f <= 1300*startY; f++) // MOVE NORTH ONLY
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
        for (int f = 0; f <= 1300*startX; f++) // MOVE WEST ONLY
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
}

void moveToCorner(int16_t direction){ // Moves piece to corner of square in order to move between pieces
    // any of the four courners depending on direction input
    // from white perspective going cw 1-NE, 2-SE, 3-SW, 4-NW
    if (direction == 1) { //NE corner
        // need DIR pin set here
        for (int f = 0; f <= 1300; f++)
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    else if (direction == 2){ //SE corner
        gpio_write(0x00, GPIO_C);
        for (int f = 0; f <= 1300; f++)
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    else if (direction == 3){ //SW corner
        //need DIR pin set here
        for (int f = 0; f <= 1300; f++)
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    else if (direction == 4){ //NW corner
        gpio_write(0x81, GPIO_C);
        for (int f = 0; f <= 1300; f++)
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
    if (direction == 1){
        gpio_write(0x81, GPIO_C); // set for forward
        for (int f = 0; f <= (1000*distance); f++) // ONLY MOVE NORTH
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    if (direction == 2){
        gpio_write(0x00, GPIO_C); // set for backwards
        for (int f = 0; f <= 1300*distance; f++) // ONLY MOVE EAST
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    if (direction == 3){
        gpio_write(0x00, GPIO_C); // set for backwards
        for (int f = 0; f <= 1300*distance; f++) // ONLY MOVE SOUTH
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    if (direction == 4){
        gpio_write(0x81, GPIO_C); // set for forward
        for (int f = 0; f <= 1300*distance; f++) // ONLY MOVE WEST
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }

}

void moveDiagonal(int16_t direction, int16_t distance){
    // diagonal line movement handled by both motors simaltaniously
    // direction codes: 1-NE, 2-SE, 3-SW, 4-NW (from white perspective)
    if (direction == 1){
        // need DIR pin set here
        for (int f = 0; f <= 1300*distance; f++) // NE
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    if (direction == 2){
        gpio_write(0x00, GPIO_C); // Set for backwards
        for (int f = 0; f <= 1300*distance; f++) // SE
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    if (direction == 3){
        // need DIR pin set here
        for (int f = 0; f <= 1300*distance; f++) // SW
        {
            gpio_write(0xC0, GPIO_A); 
            short_wait();
            gpio_write(0x00, GPIO_A);
            short_wait();
        }
    }
    if (direction == 4){
        gpio_write(0x81, GPIO_C); // set for forward
        for (int f = 0; f <= 1300*distance; f++) // NW
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
    graveX = graveLocation[1] - finishX;
    graveY = graveLocation[0] - finishY;
    // proceed with movement for removal

}

int main(void){
    // Board dimensions 8 units in length and 12 units in width
    // Respective player graveyards will be to their right hand side
    // Initiate Board
    int16_t board[8][12] =
    {
        {0, 0,  2, 3, 4, 5, 6, 4, 3, 2, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0},
        {0, 0, 8, 9, 10, 11, 12, 10, 9, 8, 0, 0},
    };
 
    char recieve[] = "3234"; // variabe for comm with RPi 
    int16_t turn = 0; // white turn = 0, Black turn = 1
    int16_t piece = 0; // to track piece that is selected
    int16_t graveWhite[2] = {0,0};
    int16_t graveBlack[2] = {7,11};
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
    // Values for Step calculation
    int16_t moveX = 0;
    int16_t moveY = 0;

    while(1){

        long_wait();
        for (int i=0; i<4; i++){
            if (i==0){
               startX = (recieve[i] - '0') + 1; // compensate for Graveyard
            }
            else if (i==1){
                startY = (recieve[i] - '0') - 1;
            }
            else if (i==2){
                finishX = (recieve[i] - '0') + 1;
            }
            else if (i==3){
                finishY = (recieve[i] - '0') - 1;
            }
        }
        // find difference for move -need diff to be positive always
        // cant use abs() with XInC2. need to do it other way
        // diffX first
        if (startX > finishX){
            diffX = startX - finishX;
        }
        else {
            diffX = finishX - startX;
        }
        // diffY second
        if (startY > finishY){
            diffY = startY - finishY;
        }
        else{
            diffX = finishY - startY;
        }

        // Is it a capture move? 
        if (board[finishY][finishX] != 0){
            piece = board[finishY][finishX];
            board[finishY][finishX] = 0;
            if (turn == 0){  // If its whites turn they are capturing black pieces
                pieceRemoval(finishX,finishY,graveBlack);
                board[graveBlack[0]][graveBlack[1]] = piece;
                graveBlack[0] = graveBlack[0] - 1;
                if (graveBlack[0] == 0){
                    graveBlack[1] = 10;
                    graveBlack[0] = 7;
                }
            }
            else if (turn == 1){
                pieceRemoval(finishX,finishY,graveWhite);
                board[graveWhite[0]][graveWhite[1]] = piece;
                graveWhite[0] = graveWhite[0] + 1;
                if (graveWhite[0] == 7){
                    graveWhite[1] = 1;
                    graveWhite[0] = 0;
                }
            }

        }
        // piece location ol' swapperoo
        piece = board[startY][startX]; // swap piece position with end position
        board[startY][startX] = 0;
        board[finishY][finishX] = piece;

        // This is all for testing purposes
        xpd_echo_int(startX,XPD_Flag_UnsignedDecimal);
        xpd_echo_int(startY, XPD_Flag_UnsignedDecimal);
        xpd_echo_int(finishX, XPD_Flag_UnsignedDecimal);
        xpd_echo_int(finishY, XPD_Flag_UnsignedDecimal);
        xpd_putc('\n');
        xpd_echo_arr(board[1],12);
        xpd_putc('\n');
        xpd_echo_arr(board[3],12);

        while(1){} /////////////////////////////////////////////////////////////////////// IT'S A TRAP /////////////////////////////////////////////////

        moveToStart(startX, startY); // move motors to start position

        // Is the knight moving?  (diffX != 0) && (diffY != 0) && (diffX != diffY)
        if ((piece == 3) | (piece == 9)){
    	    //knight is moving somewhere
            // 8 options for knight move, 4 to the north and 4 to the south
            if (startY < finishY){
                // 4 south options
                // figure out east or west
                if (startX < finishX){
                    // SE, find difference on last two options
                    moveToCorner(2); // move to SE corner
                    if (diffX > diffY){
                        moveStraight(2,1); // move east 1 square
                    }
                    else {
                        moveStraight(3,1); // move south 1 square
                    }
                    moveToCorner(2); // move to center of square
                }
                else{
                    // SW, find the last two options
                    moveToCorner(3); // move to SW corner
                    if (diffX > diffY){
                        moveStraight(4,1); // west
                    }
                    else{
                        moveStraight(3,1); // south
                    }
                    moveToCorner(3); // move back to center of square
                }
            }
            else if (startY > finishY){
                // 4 north options, figure out east or west
                if (startX < finishX){
                    // NE, find difference on last two
                    moveToCorner(1);
                    if (diffX > diffY){
                        moveStraight(2,1); // East
                    }
                    else{
                        moveStraight(1,1); // North
                    }
                    moveToCorner(1); // move back to center of square
                }
                else if (startX > finishX){
                    // NW, find difference between last two
                    moveToCorner(4);
                    if (diffX > diffY){
                        moveStraight(4,1); // West
                    }
                    else {
                        moveStraight(1,1); // North
                    }
                    moveToCorner(4); // move back to center of square
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
        }
        // analyze the X or row direction (horizontal movement)
        else if (diffX != 0){
            if (startX > finishX){
                moveStraight(4,diffX); // West
            }
            else{
                moveStraight(2,diffX); // East
            }
        }
        // analyze the Y or Column direction
        else if (diffY != 0){
            if (startY > finishY){
                moveStraight(1,diffY); // North
            }
            else{
                moveStraight(3,diffY); // South
            }
        }
    }
    
    return 0;
}

