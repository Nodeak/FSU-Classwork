#include <iostream>
#include "bitflags.h"

BitFlags::BitFlags() : numflags(sizeof(int)*8)
{
   flags = 0;		// defaults all flags to "off"
}

void BitFlags::Set(int num)
// set flag # num to 1 (on).  Note:  this scheme numbers the flags from 
//  the low order bit to the high order, starting at 0.
//  Flag0 is the 1's place, Flag1 is the 2's place, Flag2 is the 4's 
//   place, etc.
{
/*   Old Version
     int mask = 1 << num;		// create mask, shifting 1 bit to flag
				//   position given by "num"
*/

   flags = flags | Mask(num);	// set by using bitwise 'or' with the mask
}


///////////////////////////////////////////////////////////////////////////
// These other functions are left as an exercise.  How would you do these? 
///////////////////////////////////////////////////////////////////////////

void BitFlags::Unset(int num)
// Set flag #num to 0
{
   flags = flags & ~Mask(num);
}
   
void BitFlags::Flip(int num)
// flip flag #num to its opposite
{
   flags = flags ^ Mask(num);
}

bool BitFlags::Query(int num) const
// return true if flag #num is currently 1, return false otherwise
{
   if (flags & Mask(num))
	return true;
   else
        return false;
}

int BitFlags::Mask(int num) const
{
   return (1 << num);
}