#include <iostream>
#include <deque>
#include "Queue.h"

template <typename T>
Queue<T>::Queue(){}

template <typename T>
Queue<T>::~Queue(){
	Q.clear();
}

template <typename T>
Queue<T>::Queue(const Queue &rhs){
	Q = rhs.Q;
}

template <typename T>
Queue<T>::Queue(Queue &&rhs){
	Q = rhs.Q;
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue &rhs){
	Q = rhs.Q;
	return *this;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue &&rhs){
	Q = rhs.Q;
	return *this;
}

template <typename T>
T& Queue<T>::back(){
	return Q.back();
}

template <typename T>
const T& Queue<T>::back() const{
	return Q.back();
}

template <typename T>
bool Queue<T>::empty() const{
	return Q.empty();
}	

template <typename T>
T& Queue<T>::front(){
	return Q.front();
}

template <typename T>
const T& Queue<T>::front() const{
	return Q.front();
}

template <typename T>
void Queue<T>::pop(){
	Q.pop_front();
}

template <typename T>
void Queue<T>::push(const T& val){
	Q.push_back(val);
}

template <typename T>
void Queue<T>::push(T&& val){
	Q.push_back(val);
}

template <typename T>
int Queue<T>::size(){
	return Q.size();
}

template <typename T>
int Queue<T>::capacity(){
	return Q.capacity();
}


























