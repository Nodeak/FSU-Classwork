/*		Kaedon Hamm
 *		COP3330 Section 7
 *		Assignment 6
 *		
 *		Main or Driver file that contains a menu to import information through text files, print that information to the screen, or export it to a filename of their choice
*/
#include <iostream>
#include <cstring>
#include "studentlist.h"
#include "student.h"

using namespace std;

// ease of printing the menu
void menuloop();

int main(){

    StudentList t4;

    char ifile[30];
    char ofile[30];

    int quit = 0;
    char choice;

    menuloop();

    // continues through menu until quit, asking user for filenames to import and export to
    do{
        cout << "\nPlease enter a selection: ";
        cin >> choice;
        if( toupper(choice)== 'I'){
            cout << "Please input the name of the file that will be imported: ";
            cin >> ifile;
            t4.ImportFile(ifile);
        }
        else if(toupper(choice) == 'S'){
            t4.ShowList();
            cout << endl;
        }
        else if(toupper(choice) == 'E'){
            cout << "Please input the name of the file that data will be exported to: ";
            cin >> ofile;
            t4.CreateReportFile(ofile);
        }
        else if(toupper(choice) == 'M'){
            menuloop();
        }
        else{
            quit++;
        }

    }while(quit != 1);


    return 0;
}

// menu
void menuloop(){

    cout << "            *** Student List menu ***\n\n";
    cout << " I          Import students from a file\n";
    cout << " S          Show student list (bried)\n";
    cout << " E          Export a grade report (to file)\n";
    cout << " M          Show this Menu\n";
    cout << " Q          Quit Program\n" ;
}