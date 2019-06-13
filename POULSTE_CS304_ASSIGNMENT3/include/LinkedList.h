/****************************************************************
* File      :   LinkedList.h (Linked list without header node)
* Version   :   1.0
* Date      :   Winter, 2016
* Author    :   Madjid Allili (mallili@ubishops.ca)
* Subject   :   Declarations of class LinkedList
 *****************************************************************/

#ifndef _LinkedList_h
#define _LinkedList_h
#include "Node.h"

template <class TYPE>
class LinkedList {
   private:
      LinkedList(const LinkedList &);
      Node<TYPE> *head;

//--------------------------------------------------------------
   public:
       LinkedList();
       ~LinkedList();
       const LinkedList& operator=(const LinkedList&);
       void insertFirst(const TYPE&);
       Node<TYPE>* insert(const TYPE &, Node<TYPE>* );
       TYPE removeFirst ( );
       Node<TYPE>* remove(Node<TYPE>* );
       void deleteEL(TYPE & );
       Node<TYPE>* find( TYPE & );
       bool isEmpty()const;
       void makeEmpty();
       void display();
};

#endif
