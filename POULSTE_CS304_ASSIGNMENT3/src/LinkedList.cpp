/****************************************************************
* File      :   LinkedList.cpp (Linked list without header node)
* Version   :   1.0
* Date      :   Winter, 2016
* Author    :   Madjid Allili (mallili@ubishops.ca)
* Subject   :   Methods of class LinkedList
 *****************************************************************/

#include <iostream>
#include <assert.h>
#include "LinkedList.h"

using namespace std;


//Constructor
template <class TYPE>
LinkedList<TYPE>::LinkedList(){
     head = NULL;

}

//Destructor
template <class TYPE>
LinkedList<TYPE>::~LinkedList(){
  makeEmpty();

}

//Assignment operator
template <class TYPE>
const LinkedList<TYPE>& LinkedList<TYPE>::operator=(const LinkedList<TYPE>& Rhs){
    if (this == &Rhs)return Rhs;
    makeEmpty();
    if(Rhs.isEmpty()) return *this;
    Node<TYPE> *temp;
    temp=Rhs.head;
    do{
           insertFirst(temp->value);
           temp=temp->next;


    }while(temp!=NULL);
    return *this;

}


//Put item on top of LinkedList
template <class TYPE>
void LinkedList<TYPE>::insertFirst(const TYPE& e){

    head= new Node<TYPE>(e, head);
}

//General Insertion
template <class TYPE>
Node<TYPE>* LinkedList<TYPE>::insert(const TYPE & e, Node<TYPE>* current){
    Node<TYPE>*  temp;
    if (current==NULL){
       insertFirst(e);
       temp=head;
    }
    else {
         temp= new Node<TYPE>(e, current -> next);
	     current -> next  = temp;
    }
	return temp;

}

//Take item from top of LinkedList
template <class TYPE>
TYPE LinkedList<TYPE>::removeFirst(){
     assert(!isEmpty());
     Node<TYPE> *temp=head; // Temporary pointer
     TYPE data=head->value;
     head=head->next;
     delete temp;
     return data;
}

//General Removal
template <class TYPE>
Node<TYPE>* LinkedList<TYPE>::remove(Node<TYPE>* current){
    if (current != NULL){
       Node<TYPE>*  temp= current -> next;
	   current -> next  = current -> next -> next;
	   delete temp;
    }
	return current;
}

//Delete node holding item
template <class TYPE>
void LinkedList<TYPE>::deleteEL(TYPE& el){
   Node<TYPE>* temp = head;
   Node<TYPE>* prev = NULL;
   bool found = false;
   while (!found && temp!=NULL)
      if (temp->value== el)
         found = true;
      else {
         prev = temp;
         temp = temp->next;
      }
   if (found){
      if (temp==head)
         head = head->next;
      else prev->next = temp->next;
      delete temp;
   }
}

//Find an item
template <class TYPE>
Node<TYPE>* LinkedList<TYPE>::find(TYPE & el){
   Node<TYPE>* temp = head;
   bool found = false;
   while (!found && temp!=NULL)
      if (temp->value == el)
         found = true;
      else temp = temp->next;
   return temp;
}

//True if LinkedList is empty
template <class TYPE>
bool LinkedList<TYPE>::isEmpty()const{
      return (head==NULL);
}

//Make empty
template <class TYPE>
void LinkedList<TYPE>::makeEmpty(){
      while (!isEmpty())removeFirst();
}

//Display
template <class TYPE>
void LinkedList<TYPE>::display(){
   cout << "\nDisplaying: ";
   Node<TYPE>* curr = head;
   while (curr!=NULL){
     cout << curr->value << " ";
     curr=curr->next;
   }
   cout << endl << endl;;
}
