/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 6
 *		
 *		Header file containing Base class Student and Derived classes English, History, and Math
*/
// BASE CLASS
#include <string>
#include <iostream>
#include <fstream>
#ifndef _student_h
#define _student_h
//#include "studentlist.h"

// Student class provides basic info [first, last, course] since all courses need that information
class Student
{

    public:
        Student();
        Student(std::string f, std::string l, std::string c);
        virtual void print(std::ostream&) const;
        void show() const;
        char getLetter();
        std::string getCourse();
        std::string getFirst();
        std::string getLast();
        void checkLetter(double);

    protected:
        std::string first, last, course;
        char letter;

    private:

};



// DERIVED CLASSES

// specific grades for each course
class English:public virtual Student
{
    public:
        
        English();
        English(int a, int p, int mt, int ft, std::string fir, std::string las, std::string cour);
        double classGrade(int a, int p, int mt, int ft);
        void print(std::ostream&) const;

        int getAttend();
        int getProject();
        int getMidterm();
        int getFinal();
        double getGrade();
        
    private:
        int attend, project, midterm, finaltest;
        double finalGrade;


};






class History:public virtual Student
{
    public:
        History();
        History(int p, int mt, int ft, std::string fir, std::string las, std::string cour);
        double classGrade(int p, int mt, int ft);
        void print(std::ostream&) const;

        int getPaper();
        int getMidterm();
        int getFinal();
        double getGrade();

    private:
        int paper, midterm, finaltest;
        double finalGrade;

};






class Math:public virtual Student
{

    public:
        Math();
        Math(int q1, int q2, int q3, int q4, int q5, int t1, int t2, int ft, std::string fir, std::string las, std::string cour);
        double classGrade(double qa, int t1, int t2, int ft);
        double average(int q1, int q2, int q3, int q4, int q5);
        void print(std::ostream&) const;

        double getQuiz();
        int getTest1();
        int getTest2();
        int getFinal();
        double getGrade();

    private:
        int test1, test2, finaltest;
        double quizAve, finalGrade;
};

#endif