/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 8
 *		
 *		Adding the functions of 'insertMiddle' and 'removeMiddle' to the class
*/
// Fig. 21.4: list.h
// Template List class definition.
#ifndef LIST_H
#define LIST_H

#include <iostream>

using std::cout;

#include <new>
#include "listnode.h"  // ListNode class definition

template< class NODETYPE >
class List {

public:
   List();      // constructor
   ~List();     // destructor
   void insertAtFront( const NODETYPE & );
   void insertAtBack( const NODETYPE & );
   void insertMiddle( NODETYPE &, int);               // New Function
   bool removeFromFront( NODETYPE & );
   bool removeFromBack( NODETYPE & );
   bool removeMiddle( NODETYPE &, int);               // New Function
   bool isEmpty() const;
   void print() const;

private:
   ListNode< NODETYPE > *firstPtr;  // pointer to first node
   ListNode< NODETYPE > *lastPtr;   // pointer to last node

   // utility function to allocate new node
   ListNode< NODETYPE > *getNewNode( const NODETYPE & );

}; // end class List

// default constructor
template< class NODETYPE >
List< NODETYPE >::List() 
   : firstPtr( 0 ), 
     lastPtr( 0 ) 
{ 
   // empty body

} // end List constructor

// destructor
template< class NODETYPE >
List< NODETYPE >::~List(){
   if ( !isEmpty() ) {    // List is not empty
//      cout << "Destroying nodes ...\n";

      ListNode< NODETYPE > *currentPtr = firstPtr;
      ListNode< NODETYPE > *tempPtr;

      while ( currentPtr != 0 )         // delete remaining nodes
      {  
         tempPtr = currentPtr;

// commented out the output -- no need to print what we are deallocating
//         cout << tempPtr->data << '\n';  

         currentPtr = currentPtr->nextPtr;
         delete tempPtr;

      }

   }

//   cout << "All nodes destroyed\n\n";

} // end List destructor

// insert node at front of list
template< class NODETYPE >
void List< NODETYPE >::insertAtFront( const NODETYPE &value )
{
   ListNode< NODETYPE > *newPtr = getNewNode( value );

   if ( isEmpty() )  // List is empty
      firstPtr = lastPtr = newPtr;

   else {  // List is not empty
      newPtr->nextPtr = firstPtr;
      firstPtr = newPtr;

   } // end else

} // end function insertAtFront

// insert node at back of list
template< class NODETYPE >
void List< NODETYPE >::insertAtBack( const NODETYPE &value )
{
   ListNode< NODETYPE > *newPtr = getNewNode( value );

   if ( isEmpty() )  // List is empty
      firstPtr = lastPtr = newPtr;

   else {  // List is not empty
      lastPtr->nextPtr = newPtr;
      lastPtr = newPtr;

   } // end else

} // end function insertAtBack

// delete node from front of list
template< class NODETYPE >
bool List< NODETYPE >::removeFromFront( NODETYPE &value )
{
   if ( isEmpty() )  // List is empty
      return false;  // delete unsuccessful

   else {  
      ListNode< NODETYPE > *tempPtr = firstPtr;

      if ( firstPtr == lastPtr )
         firstPtr = lastPtr = 0;
      else
         firstPtr = firstPtr->nextPtr;

      value = tempPtr->data;  // data being removed
      delete tempPtr;

      return true;  // delete successful

   } // end else

} // end function removeFromFront

// delete node from back of list
template< class NODETYPE >
bool List< NODETYPE >::removeFromBack( NODETYPE &value )
{
   if ( isEmpty() )
      return false;  // delete unsuccessful

   else {
      ListNode< NODETYPE > *tempPtr = lastPtr;

      if ( firstPtr == lastPtr )
         firstPtr = lastPtr = 0;
      else {
         ListNode< NODETYPE > *currentPtr = firstPtr;

         // locate second-to-last element
         while ( currentPtr->nextPtr != lastPtr )
            currentPtr = currentPtr->nextPtr;

         lastPtr = currentPtr;
         currentPtr->nextPtr = 0;

      } // end else

      value = tempPtr->data;
      delete tempPtr;

      return true;  // delete successful

   } // end else

} // end function removeFromBack

// is List empty?
template< class NODETYPE > 
bool List< NODETYPE >::isEmpty() const 
{ 
   return firstPtr == 0; 
   
} // end function isEmpty

// return pointer to newly allocated node
template< class NODETYPE >
ListNode< NODETYPE > *List< NODETYPE >::getNewNode( 
   const NODETYPE &value )
{
   return new ListNode< NODETYPE >( value );

} // end function getNewNode

// display contents of List
template< class NODETYPE >
void List< NODETYPE >::print() const
{
   if ( isEmpty() ) {
      cout << "The list is empty\n\n";
      return;

   } // end if

   ListNode< NODETYPE > *currentPtr = firstPtr;

   cout << "The list is: ";

   while ( currentPtr != 0 ) {
      cout << currentPtr->data << ' ';
      currentPtr = currentPtr->nextPtr;

   } // end while

   cout << "\n\n";

} // end function print

template< class NODETYPE >
void List< NODETYPE >::insertMiddle( NODETYPE & value, int n){
  n -= 1;                                                       // indexing reasons
  ListNode<NODETYPE> *newPtr = getNewNode(value);               // the node that will be inserted into the list
  ListNode<NODETYPE> *tempPtr = firstPtr;                       // the temporary node that will be placed right in front of the requested slot
  int SIZE = 0;                                                     

  while(tempPtr != NULL){                                       // while the next node is NOT NULL, keep counting how many links there are
    SIZE++;
    tempPtr = tempPtr->nextPtr;
  }
  tempPtr = firstPtr;                                           // resets tempPtr to the first node, for when/if it goes through the list

  if(n <= 0 || isEmpty())
    insertAtFront(value);
  else if(n > SIZE)
    insertAtBack(value);
  else{
    for(int i = 0; i < n; i++)                                   // getting tempPtr to where new node wants to be
      tempPtr = tempPtr->nextPtr;
    newPtr->nextPtr = tempPtr;                                   // linking new node with the slot in front of where it wants to be inserted
    tempPtr = firstPtr;                                           
    for(int i = 0; i < n - 1; i++)
      tempPtr = tempPtr->nextPtr;
    tempPtr->nextPtr = newPtr;                                  // linking the new node with the slot behind where it wants to be inserted, thus making it inserted
  }
  
}

template< class NODETYPE >
bool List< NODETYPE >::removeMiddle( NODETYPE & x, int n){
  n -= 1;                                                       // indexing reasons
  ListNode<NODETYPE> *tempPtr = firstPtr;
  int SIZE = 0;

   while(tempPtr->nextPtr != NULL){                             // same sizing technique as one above
    SIZE++;
    tempPtr = tempPtr->nextPtr;
  }

  tempPtr = firstPtr;

  if(isEmpty() || n < 0 || n > SIZE + 1)                        // returning false for anything out of bounds
    return false;
  else if(n == 0)                                               // if first slot wants to be removed
    removeFromFront(x);
  else if(n == SIZE)                                            // if last slot wants to be removed
    removeFromBack(x);
  else{

    for(int i = 0; i < n - 1; i++){                             // goes through array and sets temp as node right in front of location requested to remove
      tempPtr = tempPtr->nextPtr;
    }

    if(tempPtr == NULL || tempPtr->nextPtr == NULL)             // if location is null
      return false;

    ListNode<NODETYPE> *temp2 = getNewNode(0);            // another temp node
    temp2 = tempPtr->nextPtr;                             // temp2 hold location of slot wanting to be removed
    x = temp2->data;                                      // stores data of deleted node into x
    tempPtr->nextPtr = temp2->nextPtr;                    // tempPtr's next location is set to temp2's nextPtr location, breaking the link b/w the old one
    delete temp2;
  }
  return true;
}

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
