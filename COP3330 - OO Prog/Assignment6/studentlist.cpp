/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 6
 *		
 *		File creates a list of Basde Student objects, but with it being pointers, allows it to be specified to types of Students
 *      Contains functions that import files with information, shows a list of the information, grows the dynamic array, and creates an export file of information
*/
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include "studentlist.h"

using namespace std;


// sets new studentlist and creates a dynamic array of pointers
StudentList::StudentList(){
    size = 0;
    studlist = new Student*[size];
}

// deletes allocated memory
StudentList::~StudentList(){
    for(int i = 0; i < size; i++)
        delete studlist[i];
}

// takes in a file
bool StudentList::ImportFile(const char* filename){

    ifstream in;                                                    // open in filestream for given filename
    string first, last, course, newline;

    do{
        in.clear();
        in.open(filename);
        if(!in){
            cout << "Invalid file name" << endl;                    // checks for a valid filename
            return false;
        }
    }while(!in);

    in >> adds;
    Grow(adds);                                                     // grows the array to fit more students based upon given number at the beginning of the file
    in.ignore(1000, '\n');


        for(int i = cur; i < size; i++){                             // loop that reads in last name, first name, goes to next line, course, and grades based upon the subject
            getline(in, last, ',');
            in >> first;
            in.ignore(1000, '\n');
            getline(in, course, ' ');

            if(course == "History"){
                int p, mt, ft;
                in >> p;
                in >> mt;
                in >> ft;
                studlist[i] = new History(p, mt, ft, first, last, course);
            }
            else if(course == "English"){
                int a, p, mt, ft;
                in >> a;
                in >> p;
                in >> mt;
                in >> ft;
                studlist[i] = new English(a, p, mt, ft, first, last, course);
            }
            else if(course == "Math"){
                int q1, q2, q3, q4, q5, t1, t2, ft;
                in >> q1;
                in >> q2;
                in >> q3;
                in >> q4;
                in >> q5;
                in >> t1;
                in >> t2;
                in >> ft;
                studlist[i] = new Math(q1, q2, q3, q4, q5, t1, t2, ft, first, last, course);
            }
            in.ignore(1000, '\n');
        }
    return true;
}

// create a report file
bool StudentList::CreateReportFile(const char* filename){
    ofstream out;                                                                                       // open an out filestream for given filename
    
    do{
        out.clear();
       	out.open(filename);
        
       	if (!out)                                                                                       // checks to see if valid filename
            return false;
    }while (!out);

    out << "Student Grade Summary\n";                                                                   // beginning of file report, "out" is filestream that prints to file instead of screen
    out << "---------------------\n\n";

    out << "\n\nEnglish Class" << endl;                                                                 // for English
    out << setw(40) << left << "Student" << setw(10) << "Final" << setw(10) << "Final" << "Letter\n";
    out << setw(40) << left << "Name" << setw(10) << "Exam" << setw(10) << "Avg" << "Grade\n";
    out << "-------------------------------------------------------------\n";

    for(int i = 0; i < size; i++){                                                                       // goes through entire studlist and prints all english student info under english
        if(studlist[i]->getCourse() == "English"){                                                       // ^ does same for History and Math
            studlist[i]->print(out);
        }
    }

    out << "\n\nHistory Class" << endl;
    out << setw(40) << left << "Student" << setw(10) << "Final" << setw(10) << "Final" << "Letter\n";
    out << setw(40) << left << "Name" << setw(10) << "Exam" << setw(10) << "Avg" << "Grade\n";
    out << "-------------------------------------------------------------\n";

    for(int i = 0; i < size; i++){
        if(studlist[i]->getCourse() == "History"){
            studlist[i]->print(out);
        }
    }

    out << "\n\nMath Class" << endl;
    out << setw(40) << left << "Student" << setw(10) << "Final" << setw(10) << "Final" << "Letter\n";
    out << setw(40) << left << "Name" << setw(10) << "Exam" << setw(10) << "Avg" << "Grade\n";
    out << "-------------------------------------------------------------\n";

    for(int i = 0; i < size; i++){
        if(studlist[i]->getCourse() == "Math"){
            studlist[i]->print(out);
        }
    }
    return true;
}

void StudentList::ShowList() const{                                                             // prints out first, last, and course using the Base class function
    cout << setw(25) << left << "Last" << setw(25) << "First" << "Course\n";
    for(int i = 0; i < size; i++){
        studlist[i]->show();
    }
}

void StudentList::Grow(int n){                                                                  // grows the dynamic array by creating a temp list, copying it over, and recreating the original array

    int newSize = size + n;
    Student** newlist = new Student*[newSize];

    for(int i = 0; i < size; i++)
        newlist[i] = studlist[i];
    delete [] studlist;
    studlist = newlist;
    cur = size;
    size = newSize;
}


