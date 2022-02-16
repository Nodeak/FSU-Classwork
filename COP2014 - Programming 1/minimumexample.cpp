#include <iostream>
using namespace std;



double smallest(double arr[], int s);


int main()
{


  return 0;
}



double smallest(double arr[], int s)
{
  int min = arr[0]

  for(int i = 0; i < s; i++)
  {
    if(arr[i] < min)
      min = arr[i];
  }
  return min;
}
