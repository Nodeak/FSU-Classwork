/* Starter file for assignment 5
* Two functions are provided.  You will write the 5 specified functions,
* as well as a menu program to test the functions.
*
* Header goes here.
*/



#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/*Given Function prototypes*/
void PrintArray(const int arr[], const int size);

/* Add your own function prototypes here */
void menu();
void FillArray(int arr[], int size, int min, int max);
void Insert(int arr[], int size, int num, int index);

int main()
{
	srand((unsigned)time(0));		//random number generator
									/* We'll set the test size to 15.  Use this constant in your calls
									*  instead of the literal 15.  Then, by changing this line, you can
									*  easily test arrays of different sizes. */
	const int SIZE = 15;

	/* Declare your array of size SIZE*/
	int arr[SIZE];

	//other variables
	int i = 0;
	int min, max, num, index;
	char selection;


	/*Loop that presents user with menu options and calls appropriate Array functions*/
	/*Note: you can assume the user will call Fill Array function first so that the array has data in it to begin*/
	do
	{
		menu();
		cout << " Enter your menu selection: ";
		cin >> selection;
		if (selection == 'P' || selection == 'p')
			PrintArray(arr, SIZE);
		else if (selection == 'F' || selection == 'f') {
			cout << "What is the minimum random value?";
			cin >> min;
			cout << "What is the maximum random value?";
			cin >> max;
			FillArray(arr, SIZE, min, max);
			PrintArray(arr, SIZE);
		}
		else if (selection == 'I' || selection == 'i') {
			cout << "Enter a value to insert: ";
			cin >> num;
			cout << "Enter index at which to insert: ";
			cin >> index;
			Insert(arr, SIZE, num, index);
			PrintArray(arr, SIZE);
		}
		else if (selection == 'D' || selection == 'd') {

		}
		else if (selection == 'R' || selection == 'r') {

		}
		else if (selection == 'X' || selection == 'x') {

		}
		else if (selection == 'M' || selection == 'm') {

		}
		else if (selection == 'Q' || selection == 'q') {
			PrintArray(arr, SIZE);
			i++;
		}
	} while (i < 1);







	return 0;
}					// end main()


					/* Add in the definitions of your own 5 functions HERE */








					/* Definition of PrintArray below DO NOT CHANGE!*/

					//PrintArray Function
					//This function prints the contents of any interger array of any size seperated by commas
void PrintArray(const int arr[], const int size)
{
	cout << "\nThe array:\n { ";
	for (int i = 0; i < size - 1; i++)	// for loop, prints each item (not last due to comma handling)
		cout << arr[i] << ", ";

	cout << arr[size - 1] << " }\n";	// prints last item , sans comma
}


//********* Menu **********
void menu()
{
	cout << " 					* * Given Features * *\n";
	cout << " P					Print the array with random values\n\n";
	cout << "						* * Function Tests * *\n";
	cout << " F					Fill the array with random values\n";
	cout << " I					Insert\n";
	cout << " D					Delete\n";
	cout << " R					Reverse\n";
	cout << " X					Max Odd Value\n\n";
	cout << " M					Print this menu\n";
	cout << " Q					Quit this program\n\n";
}


//********* Fill Array **********
void FillArray(int arr[], int size, int min, int max)
{
	for (int i = 0; i < 0; i++)
		arr[i] = rand() % (max + 1) + min;
}

//********* Insert *********
void Insert(int arr[], int size, int num, int index)
{


}
