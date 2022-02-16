/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 4
 *		
 *		Provides prototypes for every function in grid.cpp, keeping them const
 * 		if they can be
*/

// Grid class


class Grid
{
public:
   // public static class constants, for direction indicators
	static const int NORTH = 0;
	static const int WEST = 1;
	static const int SOUTH = 2;
	static const int EAST = 3;
   	static const int empty = 4;
	static const int item = 5;
	static const int block = 6;
	static const int sPlace = 7;
	static const int fblank = 8;
	static const int rblank = 9;

   // public member functions

   Grid();			// build 1 x 1 grid with mover in only
				//  square, facing east
   Grid(int r, int c);		// build grid with r rows, c cols,
   //  and random mover position and direction

   Grid(int r, int c, int mr, int mc, int d);
			// build empty grid with r rows, c cols, and mover
                        //  at row mr, col mc, and facing direction d

   bool Move(int s);		// move forward s spaces, if possible
   void TogglePath();		// toggle whether or not moved path is shown
   void TurnLeft();		// turn the mover to the left
   void PutDown();		// put down an item at the mover's position
   bool PutDown(int r, int c);  // put down an item at (r,c), if possible
   bool PickUp();		// pick up item at current position
   bool PlaceBlock(int r, int c);	// put a block at (r,c), if possible
   void Grow(int gr, int gc);	// grow the grid by gr rows, gc columns


   void Display() const;	// display the grid on screen

   // Accessors
   bool FrontIsClear() const;	// check to see if space in front of 
				//  mover is clear
   bool RightIsClear() const;	// check to see if space to right of 
				//  mover is clear
   int GetRow() const;		// return row of the mover
   int GetCol() const;		// return column of the mover
   int GetNumRows() const;	// return number of rows in the grid
   int GetNumCols() const;	// return number of columns in the grid
   
private:
	int rows;				// total rows
	int cols;				// total cols
	int dir;				// keeps track of dir in case symbol is changed
	int mrows;				// movers rows tracker
	int mcols;				// movers cols tracker
	int grid[40][40];		// generates a grid with a max size of 40x40
	bool pathTog;			// keeps track of TogglePath ON/OFF
	
	void Set(int x, int y);									// set a grid to given rows and cols
	void blockBorder();										// used in 2 param Grid Constructor, generates a 1 line thick border full of blocks
	void randExit(int side, int ns, int ew);				// generates a rand side and exit location
	void randMover(int r, int c, int d);					// generates a rand mover location and direction
	bool checkBlock(int s) const;							// checks to see if block is in path of movement
	int boundaryCheck(int max, int min, int num) const;		// checks to see if input is in boundaries
	char symbolReturn(int x, int y) const;					// returns all numbers as specific symbols


};
