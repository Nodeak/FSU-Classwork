/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 6
 *		
 *		Contains a Base class of Student, containing first name, last name, course, and letter grade.
 *      Contains Derived classes of English, History, and Math that hold the final grades, and other specific grades based upon the subject,,
 *              also includes functions that work with StudentList to print out information that could otherwise not be reached
*/
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "student.h"

using namespace std;


// BASE STUDENT CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Student::Student(){
    first = last = course = " ";
}

Student::Student(string f, string l, string c){
    first = f;
    last = l;
    course = c;
}

//bunch of return statements in case they are needed
string Student::getCourse(){
    return course;
}
string Student::getFirst(){
    return first;
}
string Student::getLast(){
    return last;
}

char Student::getLetter(){
    return letter;
}

//sets the letter grade based upon the given final grade score
void Student::checkLetter(double x){
    if(x >= 90)
        letter = 'A';
    else if(x < 90 && x >= 80)
        letter = 'B';
    else if(x < 80 && x >= 70)
        letter = 'C';
    else if(x < 70 && x >= 60)
        letter = 'D';
    else
        letter = 'F';
}

// virtual function decleration 
void Student::print(ostream& out) const{
}

// Base classs show, used in StudentList's ShowList() function
void Student::show() const{
    cout << "" << endl;
    cout << setw(25) << left << last << setw(25) << first << course;
}

// DERIVED ENGLISH COURSE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
English::English():Student(){
    attend = project = midterm = finaltest = 0;
}

English::English(int a, int p, int mt, int ft, std::string fir, std::string las, std::string cour):Student(fir, las, cour){
    attend = a;
    project = p;
    midterm = mt;
    finaltest = ft;
    finalGrade = classGrade(a, p, mt, ft);
}

// calculates final grade and sets letter grade
double English::classGrade(int a, int p, int mt, int ft){
    double temp = ((a*0.1) + (p*0.3) + (mt*0.3) + (ft*0.3));
    checkLetter(temp);
    return temp;
}

// print statement that is called from StudentList's CreateReportFile() function
void English::print(ostream& out) const{
    out << setw(40) << left << first + " " + last << setw(10) << finaltest << setw(10) << finalGrade << letter << endl;
}

// bunch of return statements in case they are needed
int English::getAttend(){
    return attend;
}
int English::getProject(){
    return project;
}
int English::getMidterm(){
    return midterm;
}
int English::getFinal(){
    return finaltest;
}
double English::getGrade(){
    return finalGrade;
}


// HISTORY COURSE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
History::History():Student(){
    paper = midterm = finaltest = 0;
}

History::History(int p, int mt, int ft, std::string fir, std::string las, std::string cour):Student(fir, las, cour){
    paper = p;
    midterm = mt;
    finaltest = ft;
    finalGrade = classGrade(p, mt, ft);

}

// calculates final grade and sets letter grade
double History::classGrade(int p, int mt, int ft){
    double temp = ((p*0.25)+(mt*0.35)+(ft*0.4));
    checkLetter(temp);
    return temp;
}

// print statement that is called from StudentList's CreateReportFile() function
void History::print(ostream& out) const{
    out << setw(40) << left << first + " " + last << setw(10) << finaltest << setw(10) << finalGrade << letter << endl;
}

// bunch of return statements in case they are needed
int History::getPaper(){
    return paper;
}
int History::getMidterm(){
    return midterm;
}
int History::getFinal(){
    return finaltest;
}
double History::getGrade(){
    return finalGrade;
}


// MATH COURSE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Math::Math():Student(){
    quizAve = test1 = test2 = finaltest = 0;
}

Math::Math(int q1, int q2, int q3, int q4, int q5, int t1, int t2, int ft, std::string fir, std::string las, std::string cour):Student(fir,las,cour){
    quizAve = average(q1, q2, q3, q4, q5);
    test1 = t1;
    test2 = t2;
    finaltest = ft;
    finalGrade = classGrade(quizAve, t1, t2, ft);

}

// calculates final grade and sets letter grade
double Math::classGrade(double qa, int t1, int t2, int ft){
    double temp = ((qa*0.15)+(t1*0.25)+(t2*0.25)+(ft*0.35));
    checkLetter(temp);
    return temp;
}

// returns average quiz grade as a double
double Math::average(int q1, int q2, int q3, int q4, int q5){
    return (q1 + q2 + q3 + q4 + q5) / 5.0;
}

// print statement that is called from StudentList's CreateReportFile() function
void Math::print(ostream& out) const{
    out << setw(40) << left << first + " " + last << setw(10) << finaltest << setw(10) << finalGrade << letter << endl;
}

// bunch of return statements in case they are needed
double Math::getQuiz(){
    return quizAve;
}
int Math::getTest1(){
    return test1;
}
int Math::getTest2(){
    return test2;
}
int Math::getFinal(){
    return finaltest;
}
double Math::getGrade(){
    return finalGrade;
}

