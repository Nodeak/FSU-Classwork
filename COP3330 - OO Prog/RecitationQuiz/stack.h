// Fig. 21.13: stack.h
// Template Stack class definition derived from class List.
#ifndef STACK_H
#define STACK_H

#include "list.h"  // List class definition

template< class STACKTYPE >
class Stack : private List< STACKTYPE > 
{

public:
   // push calls List function insertAtFront
   void push( const STACKTYPE &data ) 
   { 
      this->insertAtFront( data ); 
   }

   // pop calls List function removeFromFront
   bool pop( STACKTYPE &data ) 
   { 
      return this->removeFromFront( data ); 
   } 

   // isStackEmpty calls List function isEmpty
   bool isStackEmpty() const 
   { 
      return this->isEmpty(); 
   }
 
   // printStack calls List function print
   void printStack() const 
   { 
      this->print(); 
   }

}; 

#endif

/**************************************************************************
 * (C) Copyright 1992-2003 by Deitel & Associates, Inc. and Prentice      *
 * Hall. All Rights Reserved.                                             *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
