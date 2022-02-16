/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 7
 *		
 *		File that finds all prime numbers smaller than given number, and sets the bits
 *		whether or not it is prime. (1 means prime, 0 means not prime)
*/
#include <cmath>
#include <iostream>
#include "bitarray.h"

void Sieve(BitArray& x){                                

    int root = sqrt(x.getNum());                        // find the square root of the given number for use in first for loop

    cout << "Primes less than " << x.getNum() << endl;
    for(int i = 0; i < x.getSize(); i++){               // changes all the bits to 1
		x.changeChar(255);
	}

    x.Unset(0);                                         //unsetting 0 and 1
    x.Unset(1);

    for(int i = 2; i < root; i++){                      // parses through each bit that is equal to 1
        if(x.Query(i)){
            for(int j = i; j < x.getNum(); j++){        // parses though rest of bits to find the multiples of the number
                int temp = j * i;
                x.Unset(temp);
            }
        }
    }
}