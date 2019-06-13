#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H
#include "Node.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <conio.h>
using namespace std;
template <class TYPE> class Node;
template <class TYPE>


class DLinkedList{
    public:
        friend class Node<TYPE>;
        DLinkedList();
        virtual ~DLinkedList();

        Node<TYPE>* insert(const TYPE & value, Node<TYPE>* nextPtr);//inserts a node

        Node<TYPE>* isFirst(); //returns a reference to header node

        Node<TYPE>* isLast(); // returns a reference to header node

        Node<TYPE>* next(Node<TYPE>* ptr)const; //returns a reference to next node

        Node<TYPE>* precedent(Node<TYPE>* ptr)const; //reference to previous node

        Node<TYPE>* remove(Node<TYPE>* N); //removes the node to the right of N

        bool isEmpty ( ) const;//returns true if the list is empty

        void display ( ); //displays the elements of linked list

        Node<TYPE>* Min(Node<TYPE>* H); //find the min value in a list headed by H

        void baseSort(Node<TYPE>* start);

        void sort(); //sort the list (selection sort) RECURSIVE


    protected:

    private:
        Node<TYPE>* head;
        Node<TYPE>* tail;
        int elements;
};

#endif // DLINKEDLIST_H
