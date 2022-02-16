/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 5
 *		
 *		File brings in either an integer or string and creates a dynamically allocated array
 *		representing the number. Given this info, you can compare, add, multiply, increase by 1,
 *		and decrease by 1 with different overloaded operators.
 *
 * 		Credit for the C2I and I2C functions are given to Robert Myers. These function switch characters
 * 		to integers or integers to characters depending on which one you call.
*/

#include <iostream>
#include <cstring>
#include "myint.h"

using namespace std;

int C2I(char c);
char I2C(int x);


MyInt::MyInt(int n){
	
	int temp = n;
	
	SIZE = 0;
	if(n <= 0)
		SIZE = 1;
	else{
		while(temp > 0){
			SIZE++;
			temp /= 10;
		}
	}
	
	intlist = new int[SIZE];
	for(int i = SIZE - 1; i >= 0; i--){
		if(n <= 0)
			intlist[i] = 0;
		else{
			intlist[i] = n % 10;
			n = n / 10;
		}
	}
	maxSIZE = SIZE + 5;
	lastloc = SIZE - 1;
}

MyInt::MyInt(const char s[]){
	
	
	SIZE = strlen(s);
	intlist = new int[SIZE];
	
	for(int i = 0; i < SIZE; i++){
		if(C2I(s[i]) == -1)
			intlist[i] = 0;
		else
			intlist[i] = C2I(s[i]);
	}
	maxSIZE = SIZE + 5;
	lastloc = SIZE - 1;
}

MyInt::MyInt(const MyInt& x){
	maxSIZE = x.maxSIZE;
	SIZE = x.SIZE;
	lastloc = x.lastloc;

	intlist = new int[x.SIZE];

	for(int i = 0; i < SIZE; i++)
		intlist[i] = x.intlist[i];

}

MyInt::~MyInt(){
	delete [] intlist;
}

int C2I(char c){
	// converts character into integer (returns -1 for error)
	if (c < '0' || c > '9')
		return -1;	// error
	return (c - '0');				// success
}

char I2C(int x){
	// converts single digit integer into character (returns '\0' for error)
	if (x < 0 || x > 9)
		return '\0';	// error
	return (static_cast<char>(x) + '0'); 	// success
}

MyInt& MyInt::operator=(const MyInt & x){
	if (this == &x)
		return *this;

	delete [] intlist;

	maxSIZE = x.maxSIZE;
	SIZE = x.SIZE;
	lastloc = x.lastloc;

	intlist = new int[x.SIZE];

	for(int i = 0; i < SIZE; i++)
		intlist[i] = x.intlist[i];

	return *this;
}

// Add in operator overload and member function definitions 
MyInt operator+(const MyInt& x, const MyInt& y){
	MyInt rl;
	MyInt a;
	MyInt b;
	int carry = 0;
	int temp;
	int i;

	// first number larger than second number
	if(x.SIZE > y.SIZE || x.SIZE == y.SIZE){
		rl = a = x;
		b = y;
		a.Reverse();
		b.Reverse();
		
		// reverse both numbers for easier addition
		// start from  [0] and work towards end, carrying the one if need be

		for(i = 0; i < a.SIZE; i++){
			if(rl.SIZE == rl.maxSIZE)
				rl.Resize();
			if(carry == 0 && i <= b.SIZE){
				temp = a.intlist[i] + b.intlist[i];
				if (temp >= 10){
					temp -= 10;
					carry = 1;
				}
				else 
					carry = 0;
				rl.intlist[i] = temp;
			}
			else if(carry == 1 && i <= b.SIZE){
				temp = a.intlist[i] + b.intlist[i] + 1;
				if (temp >= 10){
					temp -= 10;
					carry = 1;
				}
				else
					carry = 0;
				rl.intlist[i] = temp;
			}
			else if(carry == 0 && i > b.SIZE){
				temp = a.intlist[i];
				if (temp >= 10){
					temp -= 10;
					carry = 1;
				}
				else 
					carry = 0;
				rl.intlist[i] = temp;
			}
			else if(carry == 1 && i > b.SIZE){
				temp = a.intlist[i] + 1;
				if (temp >= 10){
					temp -= 10;
					carry = 1;
				}
				else
					carry = 0;
				rl.intlist[i] = temp;
			}
		}
		if(rl.SIZE == rl.maxSIZE)
			rl.Resize();
		if(carry == 1){
				rl.Grow();
				rl.intlist[rl.lastloc] = 1;
				
				
		}
	}
	else{
		rl = a = y;
		b = x;
		a.Reverse();
		b.Reverse();
		// reverse both numbers for easier addition
		// start from  [0] and work towards end, carrying the one if need be

		for(i = 0; i < a.SIZE; i++){
			if(rl.SIZE == rl.maxSIZE)
				rl.Resize();
			if(carry == 0 && i <= b.SIZE){
				temp = a.intlist[i] + b.intlist[i];
				if (temp >= 10){
					temp -= 10;
					carry = 1;
				}
				else 
					carry = 0;
				rl.intlist[i] = temp;
			}
			else if(carry == 1 && i <= b.SIZE){
				temp = a.intlist[i] + b.intlist[i] + 1;
				if (temp >= 10){
					temp -= 10;
					carry = 1;
				}
				else
					carry = 0;
				rl.intlist[i] = temp;
			}
			else if(carry == 0 && i > b.SIZE){
				temp = a.intlist[i];
				if (temp >= 10){
					temp -= 10;
					carry = 1;
				}
				else 
					carry = 0;
				rl.intlist[i] = temp;
			}
			else if(carry == 1 && i > b.SIZE){
				temp = a.intlist[i] + 1;
				if (temp >= 10){
					temp -= 10;
					carry = 1;
				}
				else
					carry = 0;
				rl.intlist[i] = temp;
			}
		}
		
		if(carry == 1){
				rl.Grow();
				rl.intlist[rl.lastloc] = 1;
				
				
		}
	}
	rl.Reverse();
	return rl;
}

MyInt operator*(const MyInt& x, const MyInt& y){
	MyInt result;
	MyInt a, b, r1, r2, r3;
	int carry = 0;
	int i, j;	// i goes through a, j goes through b 
	int temp;
	
	if(x.SIZE > y.SIZE){
		a = x; a.Reverse();
		b = y; b.Reverse();
		r1 = a;
		r2 = 0;


		for(j = 0; j < b.SIZE; j++){
			cout << "Gone through: " << j << endl;
			if(j == 0){
				for(i = 0; i < a.SIZE; i++){	//goes through each value of a
					if(carry == 0){				// if there is not carry over number
						temp = a.intlist[i] * b.intlist[j];
						if(temp >= 10){
							while(temp >= 10){
								temp -= 10;
								carry++;
							}
						}
						else
							carry = 0;
						r1.intlist[i] = temp;
					}
					else if(carry > 0){			// if there is a carry over number, add it and then set it back to 0 to see if there are more carries
						temp = a.intlist[i] * b.intlist[j] + carry;
						if(temp >= 10){
							carry = 0;
							while(temp >= 10){
								temp -= 10;
								carry++;
							}
						}
						else
							carry = 0;
						r1.intlist[i] = temp;
					}
				}
				if(carry > 0){
					r1.Grow();
					r1.intlist[r1.lastloc] = carry;
				}
			}	
			else if(j > 0){
				carry = temp = 0;
				for(i = 0; i < a.SIZE; i++){	//goes through each value of a
					if(i == r2.lastloc){
						r2.Resize();
						r2.Grow();
					}

					if(carry == 0){				// if there is not carry over number
						temp = a.intlist[i] * b.intlist[j];
						if(temp >= 10){
							while(temp >= 10){
								temp -= 10;
								carry++;
							}
						}
						else
							carry = 0;
						r2.intlist[i + j] = temp;
					}
					else if(carry > 0){			// if there is a carry over number, add it and then set it back to 0 to see if there are more carries
						temp = a.intlist[i] * b.intlist[j] + carry;
						if(temp >= 10){
							carry = 0;
							while(temp >= 10){
								temp -= 10;
								carry++;
							}
						}
						else
							carry = 0;
						r2.intlist[i + j] = temp;
					}
				}
				cout << r2.SIZE << " " << r2.maxSIZE << " " << r2.lastloc << endl;
				if(carry > 0){
					r1.Grow();
					r1.intlist[r1.lastloc] = carry;
				}
			}
			

			r1.Reverse();r2.Reverse();
			cout << "r1 = " << r1 << endl;
			cout << "r2 = " << r2 << endl;
			cout << "added: " << r1 + r2 << endl;
			r1 = r1 + r2;
			r1.Reverse();

		}
	}
	r1.Reverse();
	return r1;
}

ostream& operator<<(ostream& os, const MyInt& x){
	for(int i = 0; i < x.SIZE; i++){
		os << x.intlist[i];
	}
	return os;
}

istream& operator>>(istream& is, MyInt& x){
	int temp;
	is >> temp;	
	x = temp;
	return is;
}

bool operator<(const MyInt& x, const MyInt& y){
	if(x.SIZE < y.SIZE)
		return true;
	else if(x.SIZE == y.SIZE){
		for(int i = 0; i < x.SIZE; i++){
			if(x.intlist[i] < y.intlist[i])
				return true;
		}
		
	}
	return false;
}
bool operator<=(const MyInt& x, const MyInt& y){
	if(x.SIZE > y.SIZE)
		return false;
	else if(x.SIZE == y.SIZE){
		for(int i = 0; i < x.SIZE; i++){
			if(x.intlist[i] > y.intlist[i])
				return false;
		}
		
	}
	return true;
}

bool operator>(const MyInt& x, const MyInt& y){
	if(x.SIZE > y.SIZE)
		return true;
	else if(x.SIZE == y.SIZE){
		for(int i = 0; i < x.SIZE; i++){
			if(x.intlist[i] > y.intlist[i])
				return true;
		}
		
	}
	return false;
}

bool operator>=(const MyInt& x, const MyInt& y){
	if(x.SIZE < y.SIZE)
		return false;
	else if(x.SIZE == y.SIZE){
		for(int i = 0; i < x.SIZE; i++){
			if(x.intlist[i] < y.intlist[i])
				return false;
		}
		
	}
	return true;
}

bool operator==(const MyInt& x, const MyInt& y){
	if(x.SIZE == y.SIZE){
		for(int i = 0; i < x.SIZE; i++){
			if(x.intlist[i] != y.intlist[i]){
				return false;
			}
		}
		return true;
		
	}
	return false;
}

bool operator!=(const MyInt& x, const MyInt& y){
	if(x.SIZE == y.SIZE){
		for(int i = 0; i < x.SIZE; i++){
			if(x.intlist[i] != y.intlist[i])
				return true;
		}
		return false;
		
	}
	return true;
}

MyInt& MyInt::operator++(){
	*this = *this + 1;
	return *this;
}

MyInt MyInt::operator++(int){
	MyInt temp = * this;
	*this = *this + 1;
	return temp;
}

MyInt& MyInt::operator--(){
	Reverse();
	intlist[0] -= 1;
	for(int i = 0; i < SIZE; i++){
		if(intlist[i] < 0){
			if(intlist[i + 1] != lastloc){
				intlist[i + 1] -= 1;
				intlist[i] = 9;
			}
		}
	}
	Reverse();
	return *this;
}

MyInt MyInt::operator--(int){
	MyInt temp = *this;
	Reverse();
	intlist[0] -= 1;
	for(int i = 0; i < SIZE; i++){
		if(intlist[i] < 0){
			if(intlist[i + 1] != lastloc){
				intlist[i + 1] -= 1;
				intlist[i] = 9;
			}
		}
	}
	Reverse();
	return temp;

}

void MyInt::Grow(){
	SIZE++;
	maxSIZE++;
	lastloc++;
}

void MyInt::Resize(){

		maxSIZE = SIZE + 5;

		int* newArray = new int[maxSIZE];
		for (int i = 0; i < SIZE; i++){
			newArray[i] = intlist[i];
		}
		delete [] intlist;
		intlist = newArray;
	
	/*if(maxSIZE < SIZE){
		int diff = maxSIZE - SIZE;
		maxSIZE =  5 + (maxSIZE - diff);
		int* newArray = new int[maxSIZE];
		for (int i = 0; i < SIZE; i++){
				newArray[i] = intlist[i];
		}
		delete [] intlist;
		intlist = newArray;
	}*/
}

void MyInt::Reverse(){
	int hold;
	int last = lastloc;
	for(int i = 0; i < SIZE / 2; i++){
		hold = intlist[i];
		intlist[i] = intlist[last];
		intlist[last] = hold;
		last--;
	}
}

void MyInt::Shift(int x){

	int hold;

	for(int i = 0; i <= x; i++){
		if(intlist[i] == maxSIZE - 1){
			Grow();
		}
		hold = intlist[i];
		intlist[i] = 0;
		intlist[i + 1] = hold;
	}
}
