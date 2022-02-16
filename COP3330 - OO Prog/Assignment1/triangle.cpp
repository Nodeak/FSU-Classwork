/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 1
 *		
 *		File sets triangle's size, border, & filler characters,
 *		calculates area and perimeter, grows/shrinks the triangle,
 *		draws the triangle and provides a summary.
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include "triangle.h"

using namespace std;

Triangle::Triangle(int tSide, char tBorder, char tFill)
{
	if (tSide < 1)				// ensuring triangle stays within 1-39 range
		side = 1;
	else if (tSide > 39)
		side = 39;
	else
		side = tSide;
	border = tBorder;
	fill = tFill;
}

int Triangle::GetSize() const
{
	return side;
}

int Triangle::Perimeter() const
{
	return side * 3;
}

double Triangle::Area() const
{
	return (sqrt(3) / 4) * side * side;
}

void Triangle::Grow()
{
	if (side != 39)
		side = side + 1;
}

void Triangle::Shrink()
{
	if (side != 1)
		side = side - 1;
}

void Triangle::SetBorder(char param)
{
	if (param < '!' || param > '~')		// sets default border to # if out of character range
		border = '#';
	else
		border = param;
	
}

void Triangle::SetFill(char param)
{
	if (param < '!' || param > '~')		// same as border but for filler
		fill = '*';
	else
		fill = param;
}

void Triangle::Draw() const
{
	for (int i = 1; i <= side; i++)			// loop for each row
    {
		for(int j = 1; j <= side-i; j++)	// loop for spacing before first character of each row
            cout << ' ';
		cout << border;						// prints first character (which is always a border)
		if (i != side){						
			for (int k = 1; k <= i-2; k++)	// loop for printing fill char as long as it's not the last row
				cout << " " << fill;
		}
		else if(i = side){
			for (int k = 1; k <= i-2; k++)
				cout << " " << border;		// prints final row of border chars
		}
		if (i != 1)							//prints right side of triangle as border chars
			cout << " " << border;
		cout << endl;
    }
}

void Triangle::Summary() const
{
	cout << "Size of triangle's side = " << side << " units." << endl;
	cout << "Perimeter of triangle = " << Perimeter() << " units." << endl;
	cout << "Area of triangle = " << setprecision(2) << fixed << Area() << " units." << endl;		// summary of area to 2 decimal places
	cout << "Triangle looks like:" << endl;
	Draw();
}
