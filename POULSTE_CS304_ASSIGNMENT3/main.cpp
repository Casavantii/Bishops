#include <iostream>
#include "DLinkedList.h"
#include "src\DLinkedList.cpp"
#include "Node.h"
#include "src\Node.cpp"
#include <ctime>
#include <cstdlib>
using namespace std;

int main(){
    DLinkedList<int> theList; //initialize an empty list
    int size; // the size of the list to be sorted
    int n;
    cout << "enter size " << endl;
    cin >> size;
    srand(time(0));
    Node<int> *temp =theList.isFirst();
    for (int i=1; i<=size; i++){
        n = rand() % 100; // generate the elements randomly
        temp = theList.insert(n, temp);
    }
    theList.display(); // display the generated list
    theList.sort(); // Sort using recursive selection sort
    theList.display(); // display the sorted list
    return 0; // display the sorted list
}
