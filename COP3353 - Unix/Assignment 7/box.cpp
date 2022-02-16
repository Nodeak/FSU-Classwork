#include "box.h"
#include <iostream>
using namespace std;

// *****************************************************************
// *****************************************************************
// *                                                               *
// *  Function Name:  ValidChar                                    *
// *  Description: Accepts as a parameter a constant character     *
// *   and checks to see if it is the range of LOWERBOUD           *
// *   to UPPERBOUND.  
// *   Returns a true if so , false otherwise.                     *
// *                                                               *
// * Parameter Description:  const char inchar - a character       *
// *   to be checked for validity.                                 *
// * Date:  October 1st, 2011                                      *
// * Author: David A. Gaitros                                      *
// *****************************************************************
// *****************************************************************


bool ValidChar( const char inchar)
{
  if(inchar>=LOWERBOUND && inchar <=UPPERBOUND) return true;
  else return false;
}

// *****************************************************************
// *****************************************************************
// *                                                               *
// *  Function Name:  Center                                       *
// *  Description: Padds the front of the box with sufficient      *
// *    characters to center them within range of characters.      *
// *    It does this by subtracting the size of the box (which     *
// *    is 2 times it's size because of padding characters),       *
// *    dividing this number by 2 to show the number of characters *
// *    to the left and right of the box.                          *
// *                                                               *
// * Parameter Description: const int s - Size of the box.         *
// *   to be checked for validity.                                 *
// * Date:  October 1st, 2011                                      *
// * Author: David A. Gaitros                                      *
// *****************************************************************
// *****************************************************************

void Center(const int s)
{
  int padding = (PADDINGSIZE-s*2)/2; 
     for (int i=1; i<padding; i++)
        cout << ' ';
}


// *****************************************************************
// *****************************************************************
// *                                                               *
// *  Member Function Name:  Box                                   *
// *  Description: Constructor for the Class Box.  Creates the     *
// *    object for the class Box.  Assigns the initial values      *
// *    of size, border, and fill.                                 *
// *                                                               *
// * Parameter Description: const int boxsize - size of the box,   *
// *   must be between 1 and 39, const char borderchar - must      *
// *   be a character between ! and ~, const char fillchar -       *
// *   must be a character between ! and ~.                        *
// * Date:  October 1st, 2011                                      *
// * Author: David A. Gaitros                                      *
// *****************************************************************
// *****************************************************************
Box::Box (const int boxsize, const char borderchar, const char fillchar)
{ 
  SetSize(boxsize); 
  SetBorder(borderchar);
  SetFill(fillchar);
  
}

// *****************************************************************
// *****************************************************************
// *                                                               *
// *  Member Function Name:  Draw                                  *
// *  Description: Draw the box to standard output.   If the box   *
// *    is of size 1 or 2, print them out seperately.  The other   *
// *    boxes shall be drawn in this manner,   Draw the top        *
// *    of the box, draw the center rows, and draw the bottom      *
// *    of the box.                                                *
// *                                                               *
// * Parameter Description:  None                                  *
// * Date:  October 1st, 2011                                      *
// * Author: David A. Gaitros                                      *
// *****************************************************************
// *****************************************************************  
  void Box::Draw()
{
  cout << endl; 
  if(size==SIZE1)
    { Center(size); 
      cout <<border << endl;
      return;
    }
  if(size==SIZE2)
    {
      Center(size);   cout<<border<<border<<endl;
      Center(size);   cout<<border<<border<<endl;
      return;
    }
  // ****************************************
  // * Draw the top of the Box
  // ****************************************
   Center(size); 
   for (int i=0; i<size; i++)
    cout<<border <<' ';
   cout << endl;
  // ****************************************
  // * Draw the middle
  // ****************************************
  for (int j=1;j<size-1; j++)
    {   Center(size); 
        cout << border;
      for (int i=1;i<size-1; i++)
	cout<<' '<<fill;
      cout << ' '<< border<<endl;
    }
  
  // ****************************************
  // * Draw the bottom of the Box
  // ****************************************
   Center(size);  
   for (int i=0; i<size; i++)
    cout<<border << ' ';
   cout << endl;

// *****************************************************************
// *****************************************************************
// *                                                               *
// *  Member Function Name: Shrink                                 *
// *  Description: Reduce the size of the box by 1 if it is not    *
// *  size 1 already.                                              *
// *                                                               *
// * Parameter Description:  None                                  *
// * Date:  October 1st, 2011                                      *
// * Author: David A. Gaitros                                      *

// *****************************************************************
// *****************************************************************  
}
  void Box::Shrink()
{
  if(size>MINIMUMSIZE)size--;
}

// *****************************************************************
// *****************************************************************
// *                                                               *
// *  Member Function Name: Grow                                   *
// *  Description: Increase the size of the box by 1 if it is not  *
// *  size MAXIMUMSIZE already.                                    *
// *                                                               *
// * Parameter Description:  None                                  *
// * Date:  October 1st, 2011                                      *
// * Author: David A. Gaitros                                      *
// *****************************************************************
// *****************************************************************  
  void Box::Grow()
{
  if(size<MAXIMUMSIZE) size++;
}
// *****************************************************************
// *****************************************************************
// *                                                               *
// *  Member Function Name: GetSize                                *
// *  Description: Return the size of the box.                     *
// *                                                               *
// * Parameter Description:  None                                  *
// * Date:  October 1st, 2011                                      *
// * Author: David A. Gaitros                                      *
// *****************************************************************
// *****************************************************************  
  int Box::GetSize()
{
  return size;
}
// *****************************************************************
// *****************************************************************
// *                                                               *
// *  Member Function Name: Perimeter                              *
// *  Description: Return the permiter of the box by multiplying   *
// *    the size by 4.                                             *
// *                                                               *
// * Parameter Description:  None                                  *
// * Date:  October 1st, 2011                                      *
// * Author: David A. Gaitros                                      *
// *****************************************************************
// *****************************************************************  
  int Box::Perimeter()
{
  return size*4;
}
// *****************************************************************
// *****************************************************************
// *                                                               *
// *  Member Function Name: GetArea                                *
// *  Description: Return the area of the box by multiplying the   *
// *    size by itself.                                            *
// *                                                               *
// * Parameter Description:  None                                  *
// * Date:  October 1st, 2011                                      *
// * Author: David A. Gaitros                                      *
// *****************************************************************
// *****************************************************************  
  int Box::Area()
{
  return size*size;
}

// *****************************************************************
// *****************************************************************
// *                                                               *
// *  Member Function Name: SetSize                                *
// *  Description: Set the size of the box. Check the number       *
// * to make sure it is between ranges.           .                * 
// *                                                               *
// * Parameter Description:  const int boxsize - proposed size     *
// *    of the box.                                                *
// * Date:  October 1st, 2011                                      *
// * Author: David A. Gaitros                                      *
// *****************************************************************
// *****************************************************************  
void Box::SetSize(const int boxsize)
{
   if(boxsize<MINIMUMSIZE) size=MINIMUMSIZE;
     else if (boxsize >MAXIMUMSIZE) size=MAXIMUMSIZE;
       else 
          size = boxsize;
 
} 

// *****************************************************************
// *****************************************************************
// *                                                               *
// *  Member Function Name: SetBorder                              *
// *  Description: Set the border character. Check to see if       *
// *    it is a valid character otherwise set to the default       *
// *    to # if not.                                               *
// *                                                               *
// * Parameter Description:  const char borderchar - border        *
// *     character.                                                *
// * Date:  October 1st, 2011                                      *
// * Author: David A. Gaitros                                      *
// *****************************************************************
// *****************************************************************  
  void Box::SetBorder(const char borderchar)
{
   if(ValidChar(borderchar))
       border = borderchar;
  else border=DEFAULTBORDER;
}
// *********************** *****************************************
// *****************************************************************
// *                                                               *
// *  Member Function Name: SetFill                                *
// *  Description: Set the Fill character. Check to see if         *
// *    it is a valid character otherwise set to the default       *
// *    to * if not.                                               *
// *                                                               *
// * Parameter Description:  const char fillchar - fill            *
// *     character.                                                *
// * Date:  October 1st, 2011                                      *
// * Author: David A. Gaitros                                      *
// *****************************************************************
// *****************************************************************  
  void Box::SetFill(const char fillchar)
{
  if(ValidChar(fillchar))   
       fill = fillchar;
  else fill=DEFAULTFILL; 
}

// *****************************************************************
// *****************************************************************
// *                                                               *
// *  Member Function Name: Summary                                *
// *  Description: Print the summary information of the box which  *
// *  is the size, the permimeter, the area and draw the box.      *
// *  This is done by calling the appropriate routines.            * 
// *                                                               *
// * Parameter Description: none                                   *
// * Date:  October 1st, 2011                                      *
// * Author: David A. Gaitros                                      *
// *****************************************************************
// *****************************************************************  
  void Box::Summary()
{
  cout << "The Box size is "<< GetSize() << endl;
  cout << "The perimeter is "<< Perimeter() << endl;
  cout << "The area is "<< Area() << endl;
  Draw();
  
 
}


  
