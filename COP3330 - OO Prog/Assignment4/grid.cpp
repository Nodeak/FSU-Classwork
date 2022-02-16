/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 4
 *		
 *		Provides a default constructor, 2 param constructor, and 5 param constructor
 *		Can be used to move and turn the mover, pickup and drop items, place blocks, predict
 *		possibility for future movements, set a grid, grow a grid, randomize an exit and mover location
 *		and provides a toggle to see the path you took or not.
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "grid.h"

using namespace std;

//Default Constructor 1x1 w/ EAST mover
Grid::Grid(){
	Set(1,1);
	grid[0][0] = EAST;
	pathTog = false;
}

// 2 param constructor w/ borders, rand exit, rand mover
Grid::Grid(int r, int c){
	
	srand(time(0));
	r = boundaryCheck(40, 3, r);
	c = boundaryCheck(40, 3, c);
	Set(r,c);
	
	int randSide = rand() % 4;
	int randNSExit = rand() % (c - 2) + 1;
	int randEWExit = rand() % (r - 2) + 1;
	int randMoverRow = rand() % (r - 2) + 1;
	int randMoverCol = rand() % (c - 2) + 1;
	int randDir = rand() % 4;
	blockBorder();
	randExit(randSide, randNSExit, randEWExit);
	randMover(randMoverRow, randMoverCol, randDir);
	
	
}

//Specific constructor for exact grid creation
Grid::Grid(int r, int c, int mr, int mc, int d){
		
	r = boundaryCheck(40, 1, r);
	c = boundaryCheck(40, 1, c);
	Set(r,c);
	
	if(d == 0)
		grid[mr][mc] = NORTH;
	else if(d == 1)
		grid[mr][mc] = WEST;
	else if(d == 2)
		grid[mr][mc] = SOUTH;
	else if(d == 3)
		grid[mr][mc] = EAST;
	
	mrows = mr;
	mcols = mc;
	dir = d;
	pathTog = true;
}

//MOVE
bool Grid::Move(int s){
	//temp variables holding old locations and info if there is an item
	int tempr;
	int tempc;
	int rhold = mrows;
	int chold = mcols;
	bool torf = false;
	
	//MOVE NORTH
	if(s == 0)														// doesn't run if move = 0
		return false;
	if(dir == 0 ){
		if(mrows - s < 0)											// out of bounds check
			return false;
		else if(checkBlock(s) == false)								// check for blocks
			return false;
		else{
			if(grid[mrows - s][mcols] == item)						// check for item on ending location
				torf = true;
			while(mrows > rhold - s){								// movers goes forward by 1, replacing previous location with empty spaces
				tempr = mrows;
				grid[mrows - 1][mcols] = grid[mrows][mcols];
				if(pathTog == false)								// pathToggle
					grid[tempr][mcols] = rblank;
				else
					grid[tempr][mcols] = fblank;
				mrows--;
				//Display();
			}
			if(torf == true)										// if end position holds an item, mover turns into an '@'
				grid[mrows][mcols] = sPlace;
			else if(grid[mrows][mcols] == sPlace){					// if it is already an '@', its old position drops the item and the
				grid[rhold][chold] = item;							// mover is put back to its regular direction
				grid[mrows][mcols] = dir;
			}
			else													// sets mover direction
				grid[mrows][mcols] = dir;
			dir = NORTH;											// makes sure dir stays in the correct orientation in case mover's symbol
			return true;											// was changed
		}
	}
	
	//MOVE WEST
	else if(dir == 1){
		if(mcols - s < 0)
			return false;
		else if(checkBlock(s) == false)
			return false;
		else{
			if(grid[mrows][mcols - s] == item)
				torf = true;
			while(mcols > chold - s){
				tempc = mcols;
				grid[mrows][mcols - 1] = grid[mrows][mcols];
				if(pathTog == false)
					grid[mrows][tempc] = rblank;
				else
					grid[mrows][tempc] = fblank;
				mcols--;
				//Display();
			}
			if(torf == true)
				grid[mrows][mcols] = sPlace;
			else if(grid[mrows][mcols] == sPlace){
				grid[rhold][chold] = item;
				grid[mrows][mcols] = dir;
			}
			else
				grid[mrows][mcols] = dir;
			dir = WEST;
			return true;
		}
	}
	
	//MOVE SOUTH
	else if(dir == 2){
		if(mrows + s > rows - 1)
			return false;
		else if(checkBlock(s) == false)
			return false;
		else{
			if(grid[mrows + s][mcols] == item)
				torf = true;
			while(mrows < rhold + s){
				tempr = mrows;
				grid[mrows + 1][mcols] = grid[mrows][mcols];
				if(pathTog == false)
					grid[tempr][mcols] = rblank;
				else
					grid[tempr][mcols] = fblank;
				mrows++;
				//Display();
			}
			if(torf == true)
				grid[mrows][mcols] = sPlace;
			else if(grid[mrows][mcols] == sPlace){
				grid[rhold][chold] = item;
				grid[mrows][mcols] = dir;
			}
			else
				grid[mrows][mcols] = dir;
			dir = SOUTH;
			return true;
		}
	}
	
	//MOVE EAST
	else if(dir == 3){						
		if(mcols + s > cols - 1)
			return false;
		else if(checkBlock(s) == false)
			return false;
		else{
			if(grid[mrows][mcols + s] == item)
				torf = true;
			while(mcols < chold + s){
				tempc = mcols;
				grid[mrows][mcols + 1] = grid[mrows][mcols];
				if(pathTog == false)
					grid[mrows][tempc] = rblank;
				else
					grid[mrows][tempc] = fblank;
				mcols++;
				//Display();
			}
			if(torf == true)
				grid[mrows][mcols] = sPlace;
			else if(grid[mrows][mcols] == sPlace){
				grid[rhold][chold] = item;
				grid[mrows][mcols] = dir;
			}
			else
				grid[mrows][mcols] = dir;
			dir = EAST;
			return true;
		}
	}
	return false;
}

void Grid::TogglePath(){
	if(pathTog == true){									// go through entire grid and replace fblanks '.' with rblank ' '
		for(int i = 0; i < GetNumRows(); i++){				// fblanks and empty's look the same, but allow for path to be toggled on and off
			for(int j = 0; j < GetNumCols(); j++){
				if(grid[i][j] == fblank)
					grid[i][j] = rblank;
			}
		}
		pathTog = false;									// changes path to false so if called again, the else if will trigger
	}
	else if (pathTog == false){								// same as above but reverse
		for(int i = 0; i < GetNumRows(); i++){
			for(int j = 0; j < GetNumCols(); j++){
				if(grid[i][j] == rblank)
					grid[i][j] = fblank;
			}
		}
		pathTog = true;	
	}
}

void Grid::TurnLeft(){
	if(dir < 3)								// unless east, add one
		dir++;
	else									// east needs to be reset to 0 
		dir = 0;
	if (grid[mrows][mcols] != sPlace)		// sets mover to point in the show as pointing in the right direction IF not an '@' character
		grid[mrows][mcols] = dir;
}

void Grid::PutDown(){
	grid[mrows][mcols] = sPlace;		// "places" an item by changing mover symbol. Item is then left in that position if Move function
}										// is called

bool Grid::PutDown(int r, int c){
	grid[r][c] = item;					
}

bool Grid::PickUp(){
	if(grid[mrows][mcols] == sPlace){		// if mover is "on" and item, changes mover to dir and return true
		grid[mrows][mcols] = dir;
		return true;
	}
	else
		return false;
}

bool Grid::PlaceBlock(int r, int c){
	if(r > rows - 1 || c > cols - 1 || r < 0 || c < 0 )		// checks to see if placing out of bound or on a mover
		return false;
	else if(r ==mrows && c == mcols)
		return false;
	else if(grid[r][c] == empty || grid[r][c] == fblank || grid[r][c] == rblank){
		grid[r][c] = block;
		return true;
	}
}

void Grid::Grow(int gr, int gc){
	int oldrows = rows;
	int oldcols = cols;
	
	if(rows + gr > 40){									// check for out of bounds, sets to 40 if true
		rows = 40;
		while(oldrows < rows){							// places empty characters in newly made area
			for(int i = 0; i < cols; i++){
			grid[oldrows][i] = empty;
			}
			oldrows++;
		}
	}
	else{
		rows = rows + gr;
		while(oldrows < rows){
			for(int i = 0; i < cols; i++){
			grid[oldrows][i] = empty;
			}
			oldrows++;
		}
	}
	
	if(cols + gc > 40){
		cols = 40;
		while(oldcols < cols){
			for(int i = 0; i < rows; i++){
			grid[i][oldcols] = empty;
			}
			oldcols++;
		}
	}
	else{
		cols = cols + gc;
		while(oldcols < cols){
			for(int i = 0; i < rows; i++){
			grid[i][oldcols] = empty;
			}
			oldcols++;
		}
	} 
}

void Grid::Display() const{

	
	for(int i = 0; i < GetNumRows(); i++){				// changes array from numbers to symbols
		for(int j = 0; j < GetNumCols(); j++){
			cout << symbolReturn(i,j);
			cout << " ";
		}
	cout << endl;
	}
	cout << endl;
	//system("sleep 0.2");
	//system("clear");
}

bool Grid::FrontIsClear() const{
	if(dir == 0){										// NORTH
		if(mrows - 1 < 0)								// out of bounds check
			return false;
		else if(grid[mrows - 1][mcols] == block)		// block check
			return false;
		else											// clear
			return true;
	}
	else if(dir == 1){
		if(mcols - 1 < 0)
			return false;
		else if(grid[mrows][mcols - 1] == block)
			return false;
		else
			return true;
	}
	else if(dir == 2){
		if(mrows + 1 > rows - 1)
			return false;
		else if(grid[mrows + 1][mcols] == block)
			return false;
		else
			return true;
	}
	else if(dir == 3){
		if(mcols + 1 > cols - 1)
			return false;
		else if(grid[mrows][mcols + 1] == block)
			return false;
		else
			return true;
	}
	return false;
}

bool Grid::RightIsClear() const{
	if(dir == 0){										// NORTH
		if(mcols + 1 < 0)								// out of bounds check
			return false;
		else if(grid[mrows][mcols + 1] == block)		// block check
			return false;
		else											// right is clear
			return true;
	}
	else if(dir == 1){
		if(mrows - 1 < 0)
			return false;
		else if(grid[mrows - 1][mcols] == block)
			return false;
		else
			return true;
	}
	else if(dir == 2){
		if(mcols - 1 > cols - 1)
			return false;
		else if(grid[mrows][mcols - 1] == block)
			return false;
		else
			return true;
	}
	else if(dir == 3){
		if(mrows + 1 > rows - 1)
			return false;
		else if(grid[mrows + 1][mcols] == block)
			return false;
		else
			return true;
	}
	return false;
}

int Grid::GetRow() const{
	return grid[mrows][mcols];
}

int Grid::GetCol() const{
	return mcols;
}

int Grid::GetNumRows() const{
	return rows;
}

int Grid::GetNumCols() const{
	return cols;
}

void Grid::Set(int x, int y){						// set a grid to given rows and cols
	rows = x;
	cols = y;
	grid[rows][cols];
	
	for(int i = 0; i < GetNumRows(); i++){			// fills it with empty characters
		for(int j = 0; j < GetNumCols(); j++){
			grid[i][j] = empty;
		}
	}
}

int Grid::boundaryCheck(int max, int min, int num) const{
	
	if(num > max)									// if number is out of bounds, set it to max/min
		num = max;
	if(num < min)
		num = min;
}

char Grid::symbolReturn(int x, int y) const{		// converts the array of numbers to look like an array of symbols
	if(grid[x][y] == 0)			
		return '^';
	else if(grid[x][y] == 1)
		return '<';
	else if(grid[x][y] == 2)
		return 'v';
	else if(grid[x][y] == 3)
		return '>';
	else if(grid[x][y] == 4)
		return '.';
	else if(grid[x][y] == 5)
		return '0';
	else if(grid[x][y] == 6)
		return '#';
	else if(grid[x][y] == 7)
		return '@';
	else if(grid[x][y] == 8)
		return '.';
	else if(grid[x][y] == 9)
		return ' ';
	
	
}

bool Grid::checkBlock(int s) const{					// used in Move function, checks to see if anywhere in front of mover (within the given
													// s movement) is a block, if so, returns false
	if(dir == 0){
		for(int  i = 0; mrows - i >= mrows - s; i++){
			if(grid[mrows - i][mcols] == block)
				return false;
		}
	}
	else if(dir == 1){
		for(int i = 0; mcols - i >= mcols - s; i++){
			if(grid[mrows][mcols - i] == block)
				return false;
		}
	}
	else if(dir == 2){
		for(int i = 0; mrows + i <= mrows + s; i++){
			if(grid[mrows + i][mcols] == block)
				return false;
		}
	}
	else if(dir == 3){
		for(int i = 0; mcols + i <= mcols + s; i++){
			if(grid[mrows][mcols + i] == block)
				return false;
		}
	}
	return true;	
}

void Grid::blockBorder(){							// used in 2 param Grid Constructor, generates a 1 line thick border full of blocks
	for(int i = 0; i < rows; i++){
		if(i == 0 || i == rows - 1)
			for(int j = 0; j < cols; j++)
				grid[i][j] = block;
		else{
			grid[i][0] = block;
			grid[i][cols - 1] = block;
		}
	}
}

void Grid::randExit(int side, int ns, int ew){		// takes in 3 random numbers created in the constructor and finds a random exit that
													// isn't in a corner
	if(side == 0 || side == 2){						// for North and South sides
		if (side == 0){
			grid[0][ns] = empty;
		}
		else if (side == 2){
			grid[rows - 1][ns] = empty;
		}
	}
	if(side == 1 || side == 3){						// for East and West sides
		if (side == 1){
			grid[ew][0] = empty;
		}
		else if (side == 3){
			grid[ew][cols - 1] = empty;
		}
	}
}

void Grid::randMover(int r, int c, int d){			// generates random mover location and direction based on params
	grid[r][c] = d;
	mrows = r;
	mcols = c;
	dir = d;	
}