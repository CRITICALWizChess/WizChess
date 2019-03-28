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

#include <SystemClock.h>
#include <XPD.h>
#include <GPIO.h>
#include <Thread.h>
#include <stdio.h>

#include "main.h"

// Board dimensions 8 units in length and 12 units in width
// Respective player graveyards will be to their right hand side
// Initiate Board
uint16_t board[8][12] =
{
    {0, 0, 8, 9, 10, 11, 12, 10, 9, 8, 0, 0},
    {0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0}
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}
    {0, 0, 2, 3, 4, 5, 6, 4, 3, 2, 0, 0}
};
