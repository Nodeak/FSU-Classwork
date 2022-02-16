

/***************************


        PUBLIC FUNCTIONS


***************************/

template <typename T>
HashTable<T>::HashTable(size_t size){
  tables.resize(prime_below(size));
  currentSize = tables.size();  
}

template <typename T>
HashTable<T>::~HashTable(){
  makeEmpty();
  clear();
}



template <typename T>
bool HashTable<T>::contains(const T &x){
  auto & chosenList = tables[myhash(x)];
  return find(begin(chosenList), end(chosenList), x) != end(chosenList);
}


template <typename T>
bool HashTable<T>::insert(const T & x){
  auto & chosenList = tables[myhash(x)];
    if (contains(x))
    return false;

  chosenList.push_back(x);

  // rehash
  if(++currentSize > tables.size())
    rehash();

    return true;
}



template <typename T>
bool HashTable<T>::insert (T &&x){
  auto & chosenList = tables[myhash(x)];
  if (contains(x))
    return false;

  chosenList.push_back(x);

  // rehash
  if(++currentSize > tables.size()){
    rehash();
  }

    return true;
}


template <typename T>
bool HashTable<T>::remove(const T &x){
  auto & chosenList = tables[myhash(x)];
  auto itr = find(begin(chosenList), end(chosenList), x);

  if(itr == end(chosenList))
    return false;
  chosenList.erase(itr);
  --currentSize;
  return true;
}


template <typename T>
void HashTable<T>::clear(){
  makeEmpty();
}


template <typename T>
bool HashTable<T>::load(const char *filename){
  std::ifstream infile;
  std::string temp;

  infile.open(filename);

  if(!infile){
    std::cout << "Error: file could not be opened" << std::endl;
    return false;
  }

  while(!infile.eof()){
    getline(infile, temp);
    insert(temp);
  }

  infile.close();
  return true;
}

template <typename T>
int HashTable<T>::hashSize(){
  return currentSize;
}


// iterator x goes through the tables vector, while iterator y prints out the values stored in the lists
template <typename T>
void HashTable<T>::dump(){
  for (std::list<T> &x : tables){
    for(T &y : x)
      std::cout << y << std::endl;
  }
}


template <typename T>
bool HashTable<T>::write_to_file(const char *filename){
  std::ofstream outfile;
  
  outfile.open(filename);

  for (std::list<T> &x : tables){
    for(T &y : x)
      outfile << y << std::endl;
  }
  outfile.close();
}






/**************************


        PRIVATE FUNCTIONS


***************************/

template <typename T>
void HashTable<T>::makeEmpty(){
  for(auto & itr : tables)
    tables.clear();
    currentSize = 0;
}

template <typename T>
void HashTable<T>::rehash(){
  std::vector<std::list<T>> oldLists = tables;

	// create new double-sized, empty table
	tables.resize(prime_below(2 * tables.size()));
	for (auto & thisList: tables)
		thisList.clear();

	// copy table over
	currentSize = 0;
	for (auto & thisList : oldLists)
		for (auto & x : thisList)
			insert(std::move(x));
}

template <typename T>
size_t HashTable<T>::myhash(const T &x){
  std::hash<T> hf;
  return hf(x) % tables.size();
}


// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
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