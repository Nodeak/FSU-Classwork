/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 5
 *		
 *		Header file for MyInt holding functions and overloaded operators for
 *		MyInt
 *
 * 		Credit for the C2I and I2C functions are given to Robert Myers. These function switch characters
 * 		to integers or integers to characters depending on which one you call.
*/

#include <iostream>

using namespace std;

class MyInt
{
	

// these overload starters are declared as friend functions
// add in multiplication, as well

friend MyInt operator+(const MyInt&, const MyInt&);
friend MyInt operator*(const MyInt&, const MyInt&);
friend ostream& operator<<(ostream&, const MyInt&);
friend istream& operator>>(istream&, MyInt&);
friend bool operator<(const MyInt&, const MyInt&);
friend bool operator<=(const MyInt&, const MyInt&);
friend bool operator>(const MyInt&, const MyInt&);
friend bool operator>=(const MyInt&, const MyInt&);
friend bool operator==(const MyInt&, const MyInt&);
friend bool operator!=(const MyInt&, const MyInt&);

// add in the other comparison overloads, as well
// declare overloads for input and output (MUST be non-member functions)
//  you may make them friends of the class

public:
// be sure to add in the second constructor, and the user-defined 
//  versions of destructor, copy constructor, and assignment operator

	MyInt(int n = 0);		// first constructor
	MyInt(const char s[]);
	MyInt(const MyInt&);
	~MyInt();	

	MyInt& operator=(const MyInt &);
	MyInt& operator++();
	MyInt operator++(int);
	MyInt& operator--();
	MyInt operator--(int);
	
private:
	//int num;
	int SIZE;
	int maxSIZE;
	int lastloc;
	int* intlist;
	void Grow();
	void Resize();
	void Reverse();
	void Shift(int);
	
// member data (suggested:  use a dynamic array to store the digits)

};