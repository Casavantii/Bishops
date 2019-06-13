#include "Node.h"
//template <class TYPE>
//Node<TYPE>::Node (const  TYPE& t){
//           value = t;
//           next = NULL;
//           prev = NULL;
//
//      }
//template <class TYPE>
//Node<TYPE>::Node (const  TYPE& t,  Node * n ){
//           value = t;
//           next = n;
//           prev = NULL;
//      }
template <class TYPE>
Node<TYPE>::Node (const  TYPE& t,  Node * n,  Node * p ){
           value = t;
           next = n;
           prev = p;
      }

