#include <iostream>

using namespace std;

#include "bitarray.h"
#include "sieve.h"

int main()
{
 
    /*cout << "\nAre they equal?" << endl;
    if( test == test1)
        cout << "Equal!" << endl;
    else
        cout << "Not Equal!" << endl;

    cout << endl;
    cout << test;
    cout << endl;
    test.Set(25);
    test.Set(4);
    cout << test;
    cout << endl;
    test.Unset(4);
    cout << test;
    cout << endl;
    test.Flip(6);
    cout << test;
    cout << endl;
    if (test.Query(6))
        cout << "The bit at the given index is: " << test.Query(6) << endl;
    else
        cout << "The bit at the given index is: " << test.Query(6) << endl;

    cout << "\nAre they NOT equal?" << endl;
    if( test != test1)
        cout << "Not Equal!" << endl;
    else
        cout << "Equal!" << endl;*/

    //cout << "Length is: " << test.Length() << endl;

   unsigned int i, max, counter = 0;

   cout << "\nEnter a positive integer for the maximum value: ";
   cin >> max;

   BitArray ba(max);

   Sieve(ba);                    // find the primes (marking the bits)

   cout << "The bit array looks like this: \n"
        << ba
        << '\n';  

   cout << "\nPrimes less than " << max << ':' << '\n';
   for (i = 0; i < max; i++)
   {    
       if (ba.Query(i))
       {
	    counter++;
            cout << i;
            if (counter % 8 == 0)
            {
                cout << '\n';
                counter = 0;
            }
            else
                cout << '\t';
       }
   }


   cout << "\nGoodbye!\n";
   return 0;
}
