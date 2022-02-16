#include <iostream>
#include "bst.h"

using namespace std;
using namespace cop4530;

int main(){

    BST<int> x;
    x.insert(2);
    x.insert(3);
    x.printInOrder();

    return 0;
}