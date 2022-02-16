#include <iostream>
#include <vector>
#include "list.h"
#include "listnode.h"
#include "stack.h"

using namespace std;

int main(){

    char cont = 'y';

    while(cont == 'y'){
    Stack<int> s;
    int x, temp;
    cout << "Please enter an integer: ";
    cin >> x;
    cout << "The number " << x << " translated into binary is: " << endl;

    while(x != 0){
        temp = x % 2;
        s.push(temp);
        x = x/2;
    }

    while(!s.isStackEmpty()){
        s.pop(x);
        cout << x;
    }


    cout << endl;

    cout << "Would you like to continue? (y or n): ";
    cin >> cont;
    cout << endl;
    }
    return 0;
}