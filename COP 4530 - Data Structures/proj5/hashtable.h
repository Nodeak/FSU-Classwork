#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>



// used when improper size is given (for example
// size is 0 or negatiave)
static const unsigned int default_capacity = 11;
static const unsigned int max_prime = 1301081;

//unsigned long prime_below(unsigned long);
//void setPrimes(std::vector<unsigned long> &);

namespace cop4530{



template <typename T>
class HashTable{

    public:
        HashTable(size_t size = 101);               // constructor. Create a hash table, where the size of the vector is set to prime_below(size) (where size is default  to 101), where prime_below() is a private member function of the HashTable and provided to you.
        ~HashTable();                               // destructor. Delete all elements in hash table.
        bool contains(const T &x);                  // check if x is in the hash table.
        bool insert(const T & x);                   // add x into the hash table. Don't add if x is already in the hash table. Return true if x is inserted; return false otherwise.
        bool insert (T &&x);                        // move version of insert.
        bool remove(const T &x);                    // delete x if it is in the hash table. Return true if x is deleted, return false otherwise.
        void clear();                               // delete all elements in the hash table
        bool load(const char *filename);            // load the content of the file with name filename into the hash table. In the file, each line contains a single value to be inserted to the hash table.
        void dump();                                // display all entries in the hash table. Elements in one entry of the hash table (linked list) are separated by the tab character ("\t") (see the provided executable for more detailed on the output format).
        bool write_to_file(const char *filename);   // write all elements in the hash table into a file with name filename.
        int hashSize();                             // size helper function
    private:
        void makeEmpty();                           // delete all elements in the hash table. The public interface clear() will call this function.
        void rehash();                              // Rehash function. Called when the number of elements in the hash table is greater than the size of the vector.
        size_t myhash(const T &x);                  // return the index of the vector entry where x should be stored.
        unsigned long prime_below (unsigned long);  // two helpful functions to determine the proper prime numbers used in setting up the vector size. Whenever you need to set hash table to a new size "sz", call prime_below(sz) to determine the new proper underlying vector size. These two functions have been provided in hashtable.h and hashtable.hpp.
        void setPrimes(std::vector<unsigned long>&);     // two helpful functions to determine the proper prime numbers used in setting up the vector size. Whenever you need to set hash table to a new size "sz", call prime_below(sz) to determine the new proper underlying vector size. These two functions have been provided in hashtable.h and hashtable.hpp.

        std::vector<std::list<T>> tables;
        int currentSize;

};

#include "hashtable.hpp"

}