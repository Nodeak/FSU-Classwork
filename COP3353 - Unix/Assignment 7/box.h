// ************************************************************
// ************************************************************
// *  Box Class:                                              *
// *                                                          *
// *  Description:  A class that provides the capability to   *
// *    draw a box of varying size to standard output.  The   *
// *    box will have a border and fill character and be      *
// *    restricted to certain sizes as specified by the       *
// *    constants MINIMUMSIZE and MAXIMUMSIZE.   Boxes        *
// *    of sizes 1 and 2 have no fill characters.             *
// *                                                          *
// * Date: Aug 1, 2011                                        *
// * Author: Dr. David A. Gaitros                             *
// ************************************************************
// ************************************************************

#include "const.h" 
class Box
{

  // **********************************************************
  // * Public member functions.                               *
  // **********************************************************
public:

    
  Box (const int boxsize=1, const char borderchar=DEFAULTBORDER,
       const char fillchar=DEFAULTFILL); 
  void Draw();
  void Shrink();
// put in a comment 
  void Grow();
  int GetSize();
  int Perimeter();
  int Area();
  void SetBorder(const char borderchar);
  void SetFill(const char fillchar);
  void SetSize(const int boxsize);
  void Summary();

// ************************************************************
// * Private Data items.                                      *
// ************************************************************
  
private:
 
  char fill;
  char border;
  int size;
}; 
  
