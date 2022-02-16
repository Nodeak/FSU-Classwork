/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 7
 *		
 *		File that sets up a character array to practice changing and querrying bits
*/
#include <iostream>
#include "bitarray.h"

BitArray::BitArray(unsigned int n) : numflags(sizeof(char)*8){		// numflags get the size of char
        while(n % numflags != 0)									// setting the size of the number to the needed amount of bits based upon size of the bit (eg. asks for 35 needs 40 bits)
			n++;
		num = n;
		arraySize = n / numflags;									// set number of chars that is going to be in the array
		flags = 0;													// sets default flag to 0;
        barray = new unsigned char[arraySize];						// creates array of minimum needed bits

		for(int i = 0; i < arraySize; i++){							// fills bits with 0's
			barray[i] = 0;
		}
}

BitArray::BitArray(const BitArray& x) : numflags(sizeof(char)*8){	// copy constructor

	arraySize = x.arraySize;
	flags = x.flags;

	barray = new unsigned char[x.arraySize];

	for(int i = 0; i < arraySize; i++)
		barray[i] = x.barray[i];

}

BitArray::~BitArray(){												// destructor
    delete [] barray;
}

BitArray& BitArray::operator=(const BitArray& x){					// assignment operator

    if (this == &x)
		return *this;

	delete [] barray;

	arraySize = x.arraySize;
	flags = x.flags;

	barray = new unsigned char[x.arraySize];

	for(int i = 0; i < arraySize; i++)
		barray[i] = x.barray[i];

	return *this;
    
}

unsigned int BitArray::Length() const{
    return arraySize * numflags;
}

void BitArray::Set(unsigned int index){						// sets bit to 1 if not using the inclusive OR |
	index = whichChar(index);
	barray[index] |= Mask(index);
}

void BitArray::Unset(unsigned int index){					// flips ALL the bits over and replaces the given bit with a 0 if it wasn't already
	index = whichChar(index);
	barray[index] &= ~(Mask(index));
}

void BitArray::Flip(unsigned int index){					// flips a specific bit using the exclusive OR operant ^
	index = whichChar(index);
	barray[index] ^= Mask(index);
}

bool BitArray::Query(unsigned int index){					// checks to see if the bit in question is a 1

	index = whichChar(index);

	if ((barray[index]>>charloc) & 1)
		return true;
	else
        return false;
}

int BitArray::Mask(int index) const{						// function that actually goes into the location and reads out the bit requested
	return (1 << charloc);
}

int BitArray::whichChar(int n){								// since it isn't a straight array of bits, this adjusts the given number to a specifc
		charloc = n % numflags;								// array location and bit location on that array;
		return n / numflags;
}

void BitArray::changeChar(int n){							// changes to characters of the array to requested char (used in Sieve)
	for(int i = 0; i < arraySize; i++){
			barray[i] = n;
	}
}

ostream& operator<<(ostream& os, const BitArray& a){		// overloaded << operator that parses through the bits and prints them out
	os << "(";
	for(int i = 0; i < a.arraySize; i++){
		for(int j = 0; j < a.numflags; j++){
  			os << ((a.barray[i] >> j) & 1);
		}
	}
	os << ")";
	return os;
}

bool operator==(const BitArray& x, const BitArray& y){		// overloaded == operator that checks to see if all the bits are equal, and returns false if any of them aren't
	for(int i = 0; i < x.arraySize; i++){
		for(int j = 0; j < x.numflags; j++){
  			if (((x.barray[i] >> j) & 1) != (y.barray[i] >> j))
				return false;
		}
	}
	return true;
}

bool operator!=(const BitArray& x, const BitArray& y){		// overloaded != operator that parses through the bits and returns true if any aren't equal
	for(int i = 0; i < x.arraySize; i++){
		for(int j = 0; j < x.numflags; j++){
  			if (((x.barray[i] >> j) & 1) != (y.barray[i] >> j))
				return true;
		}
	}
	return false;
}

int BitArray::getNum(){							// return inputed number
	return num;
}

int BitArray::getSize(){						// returns array size
	return arraySize;
}