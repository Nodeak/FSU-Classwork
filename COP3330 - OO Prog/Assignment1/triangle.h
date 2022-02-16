/*		Kaedon Hamm
		COP 3330 Section 7
		Assignment 1
		
		Header file for Triangle class that provides prototype for functions
		as well as declares private variables that the class has access to.
*/	
	
class Triangle
{
	
	public:																// prototypes for functions
		Triangle(int tSide, char tBorder = '#', char tFill = '*');		// constructor for triangle.cpp that sets defaults for border and fill
		int GetSize() const;
		int Perimeter() const;
		double Area() const;
		void Grow();
		void Shrink();
		void SetBorder(char param);
		void SetFill(char param);
		void Draw() const;
		void Summary() const;	
		
		
	private:															// private variables for class (limits access to them by user)
		int side;
		char border;
		char fill;
	
};