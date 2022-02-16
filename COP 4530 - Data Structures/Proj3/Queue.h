#ifndef COP4530_VECTOR_H
#define COP4530_VECTOR_H
/********************************
 * COP 4530
 * FSU Department of Computer Sience
 ********************************/

#include <iostream>
#include <deque>

namespace cop4530 {

template <typename T>
class Queue {
 public:
	Queue(); 								// zero parameter constructor. Create an empty queue.
	~Queue(); 								// De-allocate memory if necessary.
	Queue(const Queue &rhs);			 	// copy constructor. Create the new queue with the elements of an existing queue rhs.
	Queue(Queue &&rhs); 					// Create the new queue with the elements of an existing queue rhs.
	Queue& operator=(const Queue &rhs);		// copy assignment operator.
	Queue& operator=(Queue &&rhs);			// move assignment operator.
	T& back();								// return a reference to the last element in the queue.
	const T& back() const;					// constant version of the above member function.
	bool empty() const;						// return true if there is no element in the queue; return false otherwise.
	T& front();								// return a reference to the first element in the queue.
	const T& front() const;					// constant version of the above member function.
	void pop();								// remove the first element in the queue and discard it.
	void push(const T& val);				// add a new element val into the end of the current queue.
	void push(T&& val);						// add a new element val into the end of the current queue. val should be moved instead of copied (if possible)
	int size();								// return the number of elements in the current queue.
	int capacity();
    
    
private:
	std::deque<T> Q;
    
};

#include "Queue.hpp"

} // end of namespace COP4530
#endif