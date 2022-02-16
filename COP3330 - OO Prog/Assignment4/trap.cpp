/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 4
 *		
 *		Finds the fastest way out by heading straight to a wall and following it until it finds the
 *		exit somewhere on its right hand side
*/
#include <iostream>
#include "grid.h"

using namespace std;

int main(){
	
	char temp;
	int r, c;
	
	cout << "How large do you want your cell to be? (Ex: 7,9 will give cell 7 rows by 9 columns): ";
	cin >> r >> temp >> c;
	cout << "Good luck!" << endl;
	
	Grid g(r,c);
	g.Display();
	
	while(g.FrontIsClear() == true)
		g.Move(1);
	g.TurnLeft();
	while(g.FrontIsClear() == true && g.RightIsClear() == false){
		g.Move(1);
		while(g.FrontIsClear() == false && g.RightIsClear() == false)
			g.TurnLeft();
	}
	g.TurnLeft();
	g.TurnLeft();
	g.TurnLeft();
	g.Move(1);
	g.Display();
	cout << "Congrats! You escaped...barely." << endl;
	
	return 0;
}