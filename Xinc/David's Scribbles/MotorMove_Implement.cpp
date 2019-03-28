// Motor movement code for chesslogic
// David Gingles
// to be implemented directly to chesslogic file inside movePiece() function

// declare variables for starting position
uint16_t startX
uint16_t startY
// Variables for future position
uint16_t finishX
uint16_t finishY
// Variables for difference of position
int16_t diffX
int16_t diffY
// Values for Step calculation
int16_t moveX
int16_t moveY

enum PieceColor {white, Black};

// assign start position (Make sure Row and Column values have been converted to hex)
startX = present.iRow;
startY = present.iColumn;
// assign end position
finishX = future.iRow;
finishY = future.iColumn;

// find difference for move
diffX = startX - finishX;
diffY = startY - finishY;

// Steps = diff * 1000 
moveX = 1000*diffX;
moveY = 1000*diffY;



// Is the knight moving?
if ((diffX != 0) && (diffY != 0) && (diffX != diffY)){
	//knight is moving somewhere
}

// analyze the X or row direction
switch (diffX)
{
	case(diffX = 0)
	{
		//no movement required
	}
	case(diffX < 0)
	{
		// reverse DIR pin
	}
	case(diffX < 0)
	{
		// dont change DIR pin
	}
}

// analyze the Y or Column direction
switch (diffY)
{
	case(diffY = 0)
	{
		//no movement required
	}
	case(diffY < 0)
	{
		// reverse DIR pin
	}
	case(diffY < 0)
	{
		// dont change DIR pin
	}
}

