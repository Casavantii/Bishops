#include "DLinkedList.h"

template <class TYPE>
DLinkedList<TYPE>::DLinkedList(){
    head = new Node<TYPE>(NULL);
    tail = new Node<TYPE>(NULL); // initializing head and tail as null
    elements = 0;
}

template <class TYPE>
DLinkedList<TYPE>::~DLinkedList(){
    while (!isEmpty())
        remove(head);
}
template <class TYPE>
Node<TYPE>* DLinkedList<TYPE>::insert(const TYPE & value , Node<TYPE>* nextPtr){

    Node<TYPE>* temp = new Node<TYPE>(value, nextPtr);

    if (isEmpty()){
        temp->prev = head; //bridging
        temp->next = tail;

        head->next = temp;
        tail->prev = temp;
    }

    else {
            Node<TYPE>* current = head->next;

            temp->prev = current->prev; // dealing with previous ptr
            current->prev = temp;

            head->next = temp;
            temp->next = current;
    }


    elements++; // keeping count of elements;
}//inserts a node

template <class TYPE>
Node<TYPE>* DLinkedList<TYPE>::isFirst(){
    return head->next;
} //returns a reference to header node

template <class TYPE>
Node<TYPE>* DLinkedList<TYPE>::isLast(){
    return tail->prev;
} //returns a reference to header node

template <class TYPE>
Node<TYPE>* DLinkedList<TYPE>::next(Node<TYPE>* ptr )const{
    if(ptr->value !=NULL)
        return ptr->next;
} //returns a reference to next node

template <class TYPE>
Node<TYPE>* DLinkedList<TYPE>::precedent(Node<TYPE>* ptr)const{
    if (ptr->value !=NULL)
        return ptr->prev;
} //reference to previous node

template <class TYPE>
Node<TYPE>* DLinkedList<TYPE>::remove(Node<TYPE>* N){
    Node<TYPE>* tempNext = N->next;
    Node<TYPE>* tempAfterNext = tempNext->next;
    N->next = tempNext->next;
    tempAfterNext->prev = N;
} //removes the node to the right of N

template <class TYPE>
bool DLinkedList<TYPE>::isEmpty ( ) const{
    return (  head -> next == head -> prev);
};//returns true if the list is empty

template <class TYPE>
void DLinkedList<TYPE>::display ( ){
    cout << "Elements : ";
    Node<TYPE>* temp = head->next;
    while (temp->value != NULL ){
        cout << temp->value << " ";
        temp = temp->next;
    }

} //displays the elements of linked list

template <class TYPE>
Node<TYPE>* DLinkedList<TYPE>::Min(Node<TYPE>* H){
    Node<TYPE>* tempLowest = H->next;
    Node<TYPE>* temp = H->next;
    while (temp->value != NULL ){
        temp = temp->next;
        if (temp->value < tempLowest->value)
            tempLowest = temp;
    }
    return tempLowest;

} //find the min value in a list headed by H


template <class TYPE>
void DLinkedList<TYPE>::baseSort(Node<TYPE>* start){ // trying recursive selection sort from a base sort
	if (start== tail)
		return;
	Node<TYPE>* minIndex = start;
	Node<TYPE>* index = start->next;
		while (index->value > minIndex->value)
			index = index->next;
		minIndex = index;
	Node<TYPE>* temp = start;
	start = minIndex;
	minIndex = temp;
	 baseSort(start->next);
}

template <class TYPE>                       // trying recursive selection sort
void DLinkedList<TYPE>:: sort(){
	baseSort(head->next);}
/**
template <class TYPE>          // non recursive selection sort using Min
void DLinkedList<TYPE>::sort(){
	Node<TYPE>* start = head->next;
	while (start->value != NULL){
		Node<TYPE>* minIndex = start;
		Node<TYPE>* index = start->next;
		Node<TYPE>* lowest = Min(head);
		int temp = start->value;
		start->value = lowest->value;
		lowest->value = temp;
		start = start->next;
	}


template <class TYPE>
void DLinkedList<TYPE>::sort(){ // non-recurive selection sort not using min
	Node<TYPE>* start = head->next;
	while (start->value != NULL){
		Node<TYPE>* minIndex = start;
		Node<TYPE>* index = start->next;
			while (index->value > minIndex->value && index->value != NULL)
				index = index->next;
			minIndex = index;
		int temp = start->value;
		start->value = minIndex->value;
		minIndex->value = temp;
		start = start->next;
	}
}


void DLinkedList::sort(){                   // trying recursive selection sort
	Node<TYPE>* start = head->next;
	while (start->value != NULL){
		Node<TYPE>* minIndex = start;
		Node<TYPE>* index = start->next;
			while (index->value > minIndex->value && index->value != NULL)
				index = index->next;
			minIndex = index;
		Node<TYPE>* temp = start;
		start = minIndex;
		minIndex = temp;
		start = start->next;
	}
}




void DLinkedList::sort(){
    Node<TYPE>* startIndex = head->next;
	if (startIndex->value == NULL)
		return;
	Node<TYPE>* minIndex = startIndex;
	for ( Node<TYPE>* index = startIndex->next; index->value != NULL; index = index->next){
		if (index->value < minIndex->value)
			minIndex = index;
	}
	Node<TYPE>* temp = startIndex;
	startIndex = minIndex;
	minIndex = temp;
	sort();
}
 //sort the list (selection sort) RECURSIVE

void DLinkedList::sort(){                                    // trying recursive selection sort
	Node<TYPE>* startIndex = head->next;
	Node<TYPE>* index = startIndex->next;
	int lowest = startIndex->value;
	lowest = startIndex->value;

	while (pointer->value != NULL){
		if (pointer->value < lowest)
			int temp = startIndex->value;
			startIndex->value = pointer->value;
			pointer->value = temp;
*/

