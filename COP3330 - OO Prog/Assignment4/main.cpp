#include <iostream>
#include "grid.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	
	// set up the initial grid

  Grid g(9,15,2,13,Grid::WEST);

  g.PutDown(2,1);

  for (int i = 0; i < 7; i++)
  {
     g.PlaceBlock(i,11);
     g.PlaceBlock(i,7);
     g.PlaceBlock(i,3);
     g.PlaceBlock(i+2,5);
     g.PlaceBlock(i+2,9);
  }

  g.Display();

  // now start moving

  g.TurnLeft();
  g.Move(5);
  g.Display();

  g.TurnLeft();
  g.TurnLeft();
  g.TurnLeft();
  g.Move(1);
  g.Display();  

  for (int i = 0; i < 2; i++)
  {
    g.Move(2);
    g.Display();

    g.TurnLeft();
    g.TurnLeft();
    g.TurnLeft();
    g.Move(6);
    g.Display();  

    g.PutDown();
    g.Display();  

    g.TurnLeft();
    g.Move(2);
    g.Display();

    g.TurnLeft();
    g.Move(6);
    g.Display();

    g.TurnLeft();
    g.TurnLeft();
    g.TurnLeft();
  }

  g.Move(3);
  g.Display();

  g.TurnLeft();
  g.TurnLeft();
  g.TurnLeft();
  g.Move(5);
  g.Display();

  g.PickUp();
  g.Display();

  g.TurnLeft();
  g.Move(1);
  g.Display();

  g.TogglePath();
  g.Display();
  g.TogglePath();
  g.Display();
  g.PlaceBlock(2,0);
  cout << endl << g.PlaceBlock(2,0) << endl;
	g.Display();
	
	
	
	
	/*Grid t1;
	t1.Display();
	cout << "\n\n\n";
	Grid t2(10,10,4,4,3);
	t2.Display();
	//t2.TogglePath();
	t2.Move(5);
	t2.Display();
	cout << "Moved 3" << endl;
	t2.TurnLeft();
	t2.Move(2);
	t2.Display();
	cout << "Turn left and move 2" << endl;
	cout << "Is right clear?" << t2.RightIsClear() << endl;
	t2.TurnLeft();
	t2.Move(3);
	t2.Display();
	cout << "Turn left and move 3" << endl;
	t2.TurnLeft();
	//t2.Grow(100,100);
	t2.PutDown();
	t2.Display();
	cout << "Turn left and put down item" << endl;
	t2.Move(4);
	t2.Display();
	cout << "Moved 4" << endl;
	//cout << "direction: "<< t2.getDir() << endl;
	//cout << "grid num: " << t2.GetRow() << endl;
	t2.TurnLeft();
	//cout << "direction: "<< t2.getDir() << endl;
	//cout << "grid num: " << t2.GetRow() << endl;
	t2.TurnLeft();
	//cout << "direction: "<< t2.getDir() << endl;
	//cout << "grid num: " << t2.GetRow() << endl;
	t2.Display();
	//cout << "direction: "<< t2.getDir() << endl;
	//cout << "grid num: " << t2.GetRow() << endl;
	cout << "Turn left twice" << endl;
	t2.Move(4);
	t2.Display();
	cout << "Move 4 and direction: "<< t2.getDir() << endl;
	t2.Move(0);
	t2.Display();
	cout << "Displaying again" << endl;\
	t2.PickUp();
	t2.Display();
	cout << "Pick item up and put one down a bit aways" << endl;
	t2.PutDown(2,9);
	t2.TurnLeft();
	//cout << "direction: "<< t2.getDir() << endl;
	t2.TurnLeft();
	//cout << "direction: "<< t2.getDir() << endl;
	t2.TurnLeft();
	//cout << "direction: "<< t2.getDir() << endl;
	t2.Move(1);
	t2.Display();
	//cout << "direction: "<< t2.getDir() << endl;
	cout << "Is front clear?" << t2.FrontIsClear() << endl;
	
	t2.PlaceBlock(6,4);
	t2.Display();
	t2.TurnLeft();
	t2.TurnLeft();
	t2.Move(3);
	t2.TurnLeft();
	t2.Display();
	t2.Move(6);
	t2.Display();
	
	r = rand() % 4;
	cout << "random numba: " << r << endl;
	r = rand() % 4;
	cout << "random numba: " << r << endl;
	r = rand() % 4;
	cout << "random numba: " << r << endl;*/
	
	
	
	
	return 0;
}
