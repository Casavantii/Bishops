/****************************************************************
* File      :   Node.h
* Date      :   Winter, 2016
* Author    :   Steven Poulin (spoulin15@ubishops.ca)
 *****************************************************************/

#ifndef _Node_h
#define _Node_h
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <conio.h>

template <class TYPE> class DLinkedList;
template <class TYPE>
class Node{
      friend class DLinkedList<TYPE>;
      TYPE value;
      Node<TYPE> * next;
      Node<TYPE> * prev;
     // Node (const  TYPE& t);
      //Node (const  TYPE& t,  Node * n);
      Node<TYPE> (const  TYPE& t,  Node * n=NULL , Node * p=NULL);
};

#endif
