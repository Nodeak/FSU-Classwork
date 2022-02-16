/* Name: Kaedon Hamm
Date: 12/2/2017
Section: 0006
Assignment: 7
Due Date: 12/6/2017
About this project: Takes information from a file, creates a dynamic structure array to store the info, and gives user different options to view different info.
Assumptions: (write any assumptions made here (ex: assumes correct user input))

All work below was performed by Kaedon Hamm */
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

// Creates an stucture array for the incoming team information
struct teaminfo
{
	//cstring team name
	char name[40];
	int wins;
	int losses;
	int playoffs;	//0 or 1
	int diff;
};

// Function declerations for inputing information, the menu, and options
void teamInput(ifstream &in, teaminfo arr[], int size);
int menu(ifstream &in, teaminfo arr[], int size);
void op1(ifstream &in, teaminfo arr[], int size);
void op2(ifstream &in, teaminfo arr[], int size);
void op3(ifstream &in, teaminfo arr[], int size);
void op4(ifstream &in, teaminfo arr[], int size);
void op5(ifstream &in, teaminfo arr[], int size);

int main()
{
	// Variables
	int size;
	char filename[20];
	ifstream in;

	// Checks to see if user input is a valid file
	do
	{
		in.clear();
		cout << "Please enter a filename: ";
		cin >> filename;

		in.open(filename);
		if (!in)
			cout << "That is not a valid file. Try again!\n";

	} while (!in);


	//Creates dynamic area of length 'size'
	in >> size;
	teaminfo* arr = new teaminfo[size];

	// Take info on teams from text file
	teamInput(in, arr, size);

	//LOOP FOR MENU
	for (int i = 0; i < 1;) {
		int option = menu(in, arr, size);
		if (option == 1)
			op1(in, arr, size);
		else if (option == 2)
			op2(in, arr, size);
		else if (option == 3)
			op3(in, arr, size);
		else if (option == 4)
			op4(in, arr, size);
		else if (option == 5)
			op5(in, arr, size);
		else if (option == 0)
			i++;
		else
			cout << "Please choose a valid menu option." << endl;
	}

	// Deletes dynamic array & closes ifstream
	delete[] arr;
	in.close();
	return 0;
}

// Function to put info from file into structure array
void teamInput(ifstream &in, teaminfo arr[], int size)
{
	while (!in.eof()) {
		for (int i = 0; i < size; i++) {
			in.getline(arr[i].name, 40, ',');
			in >> arr[i].wins;
			in.ignore();
			in >> arr[i].losses;
			in.ignore();
			in >> arr[i].playoffs;

			arr[i].diff = arr[i].wins - arr[i].losses;
		}
	}
}

// Function to print out menu
int menu(ifstream &in, teaminfo arr[], int size)
{
	int option;

	cout << "\n1 - View team Win/Loss records" << endl;
	cout << "2 - Show teams with at least x wins" << endl;
	cout << "3 - List teams that made the playoffs" << endl;
	cout << "4 - List teams and their win / loss differential" << endl;
	cout << "5 - Sort teams by Win / Loss differential(extra credit)" << endl;
	cout << "0 - Exit program" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Choice: " << endl;
	cin >> option;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	return option;
}

// Menu option 1 - View team Win/Loss Records:
void op1(ifstream &in, teaminfo arr[], int size)
{
	cout << "Team Win-Loss Records:" << endl;
	for (int i = 0; i < size; i++)
		cout << arr[i].name << " " << arr[i].wins << "-" << arr[i].losses;
	cout << endl;
}

// Menu option 2 - Show teams with at least x wins:
void op2(ifstream &in, teaminfo arr[], int size)
{
	int minwin; //cool name
	cout << "Show teams with at least ___ wins: ";
	cin >> minwin;

	for (int i = 0; i < size; i++) {
		if (arr[i].wins >= minwin)
			cout << arr[i].name;
	}
	cout << endl;
}

// Menu option 3 - List teams that made the playoffs:
void op3(ifstream &in, teaminfo arr[], int size)
{
	int j = 0;
	int k = 1;

	cout << "Teams that made the Playoffs: " << endl;
	for (int i = 0; i < size; i++) {
		if (arr[i].playoffs == 1)
			j++;
	}

	for (int i = 0; i < size; i++) {
		if (k < j && arr[i].playoffs == 1) {
			cout << arr[i].name << ", ";
			k++;
		}
		else if (k == j && arr[i].playoffs == 1) {
			cout << arr[i].name;
			k++;
		}

	}
	cout << endl;
}

// Menu option 4 - Print teams and their Win/Loss
void op4(ifstream &in, teaminfo arr[], int size)
{
	cout << "Win/Loss Differential: " << endl;
	for (int i = 0; i < size; i++) {
		if (arr[i].diff >= 0)
			cout << arr[i].name << " +" << arr[i].diff;
		else
			cout << arr[i].name << " " << arr[i].diff;
	}
	cout << endl;
}

// Menu option 5 - Sort teams by Win/Loss differential (EXTRA CREDIT OPPORTUNITY, 10 points)
void op5(ifstream &in, teaminfo arr[], int size)
{
	teaminfo temp;

	for (int i = 1; i < size; ++i){
		for (int j = 0; j < (size - i); ++j) {
			if (arr[j].diff > arr[j + 1].diff){
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	cout << "Teams sorted from lowest to highest differential." << endl;
}
