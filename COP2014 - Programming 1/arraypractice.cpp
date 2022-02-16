#include <iostream>
using namespace std;

int reee(int arr[], int size);

int main()
{
	const int size = 5;
	int arr[size] = { 1,2,3,4,5 };



	cout << "The sum is: " << reee(arr, size) << endl;

	return 0;
}

int reee(int arr[], int size)
{
	int sum = 0;

	for (int i = 0; i < size; i++)
		sum = sum + arr[i];

		return sum;
}
