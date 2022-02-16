#include <iostream>
#include <ios>
#include "Vector.h"

// default constructor
template <typename T>
Vector<T>::Vector() : theSize{0}, theCapacity{0}, array{nullptr}{}


template <typename T>
Vector<T>::Vector(const Vector &rhs) : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, array{nullptr}{
	array = new T[theCapacity];
	for (int k = 0; k < theSize; ++k)
		array[k] = rhs.array[k];
}


template <typename T>
Vector<T>::Vector(Vector &&rhs) : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, array{rhs.array}{
	rhs.array = nullptr;
	rhs.theSize = 0;
	rhs.theCapacity = 0;
}

// num elements with value of val
template <typename T>
Vector<T>::Vector(int num, const T& val){
	//Construct a Vector with num elements, all initialized with value val. Note that the capacity should also be num.
	//theSize = theCapacity = num;
	for(int i = 0; i < num; i++){
		this->push_back(val);
	}
}

// constructs with elements [start, end]
template <typename T>
Vector<T>::Vector(const_iterator start, const_iterator end){
	//construct a Vector with elements from another Vector between start and end. Including the element referred to by the start iterator, but not by the end iterator, that is, the new vector should contain the elements in the range [start, end)
	for(auto i = start; i != end; i++){
		this->push_back(*i);
	}	
}


template <typename T>
Vector<T>::~Vector(){
	delete [] array;
}


template <typename T>
T& Vector<T>::operator[](int index){
	return array[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const{
	return array[index];
}


template <typename T>
const Vector<T>& Vector<T>::operator=(const Vector &rhs){
	Vector copy = rhs;
	std::swap(*this, copy);
	return *this;
}


template <typename T>
Vector<T>& Vector<T>::operator=(Vector &&rhs){
	std::swap(theSize, rhs.theSize);
	std::swap(theCapacity, rhs.theCapacity);
	std::swap(array, rhs.array);
	
	return *this;
}

// at function
template <typename T>
T& Vector<T>::at(int loc){
	// Return reference to the element at the specified location. Throw "out_of_range" exception if index is not in the valid range [0, theSize).  There are two versions of this member function.
	if(loc < 0 && loc > theSize)
		throw std::out_of_range();
	else
		return array[loc];
}
template <typename T>
const T& Vector<T>::at(int loc) const{
	// Return reference to the element at the specified location. Throw "out_of_range" exception if index is not in the valid range [0, theSize).  There are two versions of this member function.
	if(loc < 0 && loc > theSize)
		throw std::out_of_range();
	else
		return array[loc];
}


// front()
template <typename T>
T& Vector<T>::front(){
	return array[0];
}
template <typename T>
const T& Vector<T>::front() const{
	return array[0];
}

template <typename T>
T& Vector<T>::back(){
	return array[theSize - 1];
}
template <typename T>
const T& Vector<T>::back() const{
	return array[theSize - 1];
}

template <typename T>
int Vector<T>::size() const{
	return theSize;
}

template <typename T>
int Vector<T>::capacity() const{
	return theCapacity;
}

template <typename T>
bool Vector<T>::empty() const{
	return size() == 0;
}


// clear()
template <typename T>
void Vector<T>::clear(){
	theSize = 0;
}


// resize vector
template <typename T>
void Vector<T>::push_back(const T & val){
	if(theCapacity == 0){
		resize(0);
	}
	if(theSize == theCapacity)
		reserve((2*theCapacity) + 1);
	array[theSize++] = val;
}

template <typename T>
void Vector<T>::pop_back(){
	--theSize;
}

template <typename T>
void Vector<T>::resize(int num, T val){
	if( num > theCapacity )
		reserve( num * 2 );	
	theSize = num;
}


template <typename T>
void Vector<T>::reserve(int size){
	if( size < theSize )
		return;

	T *newArray = new T[ size ];
	for( int k = 0; k < theSize; ++k )
		newArray[ k ] = std::move( array[ k ] );

	theCapacity = size;
	std::swap( array, newArray );
	delete [ ] newArray;
}


// print out all elements (ofc is a deliter)
template <typename T>
void Vector<T>::print(std::ostream& os, char ofc) const{
	for(int i = 0; i < theSize -1; i++){
		os << array[i] << ofc;
	}
	os << array[theSize-1];
}


template <typename T>
typename Vector<T>::iterator Vector<T>::begin(){
	return &array[0];
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end(){
	return &array[size()];
}

// insert iterator
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator itr, const T& val){
	this->push_back(val);
	//iterator temp = --end();
	for(auto i = --end(); i != itr-1; i--){
		std::swap(i,i-1);
	}
}

// erase iterator 1 val
template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator itr){
	while(itr != end()){
		*itr = *(itr+1);
		itr++;
	}
	theSize--;
}

// erase iterator 2 vals
template <typename T>
typename Vector<T>::iterator Vector <T>::erase (iterator start, iterator endd){
	int i = 0;
	while(start != endd && endd+1 != end()){
		*start = *(endd + i);
		start++;
		--theSize;
		i++;
	}
}





// out of class functions

template <typename T>
bool operator==(const Vector<T> & llhs, const Vector<T> &rhs){
	if(llhs.size() != rhs.size())
		return false;
	for(int i = 0; i < rhs.size(); i++){
		if(rhs[i] != llhs[i])
			return false;
	}
	return true;
}

template <typename T>
bool operator!=(const Vector<T> & llhs, const Vector<T> &rhs){
	return !(llhs == rhs);
}

template <typename T>
std::ostream & operator<<(std::ostream &os, const Vector<T> &v){
	v.print(os, ' ');
}








