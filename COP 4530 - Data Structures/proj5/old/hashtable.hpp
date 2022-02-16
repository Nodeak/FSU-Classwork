// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n


// ********Public Functions**********


// Constructor
template <typename T>
bool HashTable<T>::HashTable(size_t size = 101){

}

// Destructor
template <typename T>
bool HashTable<T>::~HashTable(){

}

// Contains function
template <typename T>
bool HashTable<T>::contains(const T &x){
  auto & whichList = theLists[myhash(x)];

	return find(begin(whichList), end(whichList), x) != end(whichList);
}

// Insert Functions
template <typename T>
bool HashTable<T>::insert(const T &x){
  auto & whichList = theLists[myhash(x)];
	if (find(begin(whichList), end(whichList), x) != end(whichList))
		return false;

	whichList.push_back(x);

	//  rehash, see Section 5.5
	if (++currentSize > theLists.size())
		rehash();

	return true;
}

template <typename T>
bool HashTable<T>::insert(T &&x){
  auto & whichList = theLists[myhash(x)];
	if (find(begin(whichList), end(whichList), x) != end(whichList))
		return false;

	whichList.push_back(x);

	//  rehash, see Section 5.5
	if (++currentSize > theLists.size())
		rehash();

	return true;
}

template <typename T>
bool HashTable<T>::remove(const T &x){
  auto & whichList = theLists[myhash(x)];
  auto itr = find(begin(whichList), end(whichList), x);

  if (itr == end(whichList))
    return false;

  whichList.erase(itr);
  --currentSize;
  return true;
}

template <typename T>
void HashTable<T>::clear(){

}

template <typename T>
bool HashTable<T>::load(const char *filename){

}

template <typename T>
void HashTable<T>::dump(){

}

template <typename T>
bool HashTable<T>::write_to_file(const char *filename){

}







// ********* Private Functions **********
template <typename T>
void HashTable<T>::makeEmpty(){
  for (auto & thisList : the Lists){
    thisList.clear();
  }
}

template <typename T>
void HastTable<T>::rehash(){

}

template <typename T>
size_t HashTable<T>::myhash(const T &x){
  static hash<HashedObj> hf;
	return hf(x) % theLists.size();
}

template <typename T>
unsigned long HashTable<T>::prime_below(unsigned long p){

}

template <typename T>
void HashTable<T>::setPrimes(vector<unsigned long>&){

}








template <typename T>
unsigned long HashTable<T>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename T>
void HashTable<T>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

