/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 6
 *		
 *		Header file for StudentList class, holding a dynamic array of pointers
*/
#ifndef _studentlist_h
#define _studentlist_h
#include "student.h"
#include <fstream>

class Student;

class StudentList
{
public:
    StudentList();		// starts out empty
    ~StudentList();		// cleanup (destructor)

    bool ImportFile(const char* filename);
    bool CreateReportFile(const char* filename);
    virtual void ShowList() const;	// print basic list data

private:
    Student** studlist;
    int size, adds, cur;
    void Grow(int n);
    
};

#endif