#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"

/**Function to point the list head to the appropriate functions. Allocates memory to the struct.
*@return pointer to the list head
*@param printFunction function pointer to print a single node of the list
*@param deleteFunction function pointer to delete a single piece of data from the list
*@param compareFunction function pointer to compare two nodes of the list in order to test for equality or order
**/
List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second)){
  //creating new list and allocating space for list
  List *newList = malloc(sizeof(List)*1);

  //initializing list elements
  newList->head = NULL;
  newList->tail = NULL;
  newList->printData = printFunction;
  newList->compare = compareFunction;
  newList->deleteData = deleteFunction;

  //returning new list
  return newList;
}


/**Function for creating a node for a linked list. This node contains generic data and may be connected to
other notes in a list.
*@pre data should be of same size of void pointer on the users machine to avoid size conflicts. data must be valid.
*data must be cast to void pointer before being added.
*@post data is valid to be added to a linked list
*@return On success returns a node that can be added to a linked list. On failure, returns NULL.
*@param data - is a generic pointer to any data type.
**/
Node *initializeNode(void *data){
  //creating new node and allocating space for node
  Node * newNode = malloc(sizeof(Node)*1);

  //initializing node elements
  newNode->data = data;
  newNode->next = NULL;
  newNode->previous = NULL;

  //returning new node
  return newNode;
}


/**Inserts a Node to the front of a linked list. The list then updates accordingly to adhere to the ADT.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertFront(List *list, void *toBeAdded){
  //check if list list does not point to anything
  if(list == NULL){
    return;
  }

  //creating node to be added
  Node *nodeToBeAdded = initializeNode(toBeAdded);

  //checking if any nodes are in the list yet
  if(list->head == NULL){
    list->head = nodeToBeAdded;
    list->tail = nodeToBeAdded;
    return;
  }

  //adding node if head is not NULL
  nodeToBeAdded->next = list->head;
  list->head->previous= nodeToBeAdded;
  list->head = nodeToBeAdded;
  return;
}


/**Inserts a Node to the back of a linked list. The list then updates accordingly to adhere to the ADT.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertBack(List *list, void *toBeAdded){
   //check if list list does not point to anything
  if(list == NULL){
    return;
  }

  //creating node to be added
  Node *nodeToBeAdded = initializeNode(toBeAdded);

  //checking if head is NULL(head can be checked because then if head exists, we know there is at least 1 node)
  if(list->head == NULL){
    list->head = nodeToBeAdded;
    list->tail = nodeToBeAdded;
    return;
  }

  //adding node to end if head is not NULL
  list->tail->next = nodeToBeAdded;
  nodeToBeAdded->previous = list->tail;
  list->tail = nodeToBeAdded;
  return;
}

/** Deletes the entire linked list head to tail, starting with the nodes, followed by the list itself.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the List-type dummy node
**/
void deleteList(List *list){
  //check if list exists
  if(list == NULL){
    return;
  }

  //create placeholder for node.
  Node *nodeHolder;

  //free each node including data in note(data in node is cleared through deleteData)
  while(list->head!=NULL){
    nodeHolder = list->head;
    list->head = list->head->next;
    list->deleteData(nodeHolder->data);
    free(nodeHolder);
  }
  //free the list itself
  free(list);
  return;

}

/** Uses the comparison function in the List struct to place the element in the appropriate position in the list.
*this is intended to be used from the beginning in order to keep the list completely sorted.
*@pre List exists and has memory allocated to it. Node to be added is valid.
*@post The node to be added will be placed immediately before or after the first occurrence of a related node
*@param list a pointer to the dummy head of the list containing function pointers for delete and compare, as well
as a pointer to the first and last element of the list.
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertSorted(List *list, void *toBeAdded){
  //check if list exists
  if(list == NULL){
    return;
  }

  //creating nodes
  Node *nodeToBeAdded = initializeNode(toBeAdded);
  Node *nodeToBeCompared = list->head;

  //check if head == null
  if (list->head == NULL) {
    list->head = nodeToBeAdded;
    list->tail = nodeToBeAdded;
    return;
  }

  //comparing nodes
  if (nodeToBeCompared != NULL){
    while((nodeToBeCompared->next != NULL) && (list->compare(nodeToBeCompared->data,toBeAdded)>= 0)){
      nodeToBeCompared = nodeToBeCompared->next;
    }

   //placing nodes
   nodeToBeCompared = nodeToBeCompared->next;
   nodeToBeAdded->next = nodeToBeCompared->next;
   nodeToBeAdded->previous = nodeToBeCompared;
   nodeToBeCompared->next->previous = nodeToBeAdded;
   nodeToBeCompared->next = nodeToBeAdded;
  }
  return;
}

/**Function to remove a node from the list and alter the pointers accordingly to not disrupt the order of the
 *data structure.
 *@pre List must exist and have memory allocated to it
 *@post toBeDeleted will have its memory freed if it exists in the list.
 *@param list pointer to the dummy head of the list containing deleteFunction function pointer
 *@param toBeDeleted pointer to data that is to be removed from the list
 *@return returns EXIT_SUCCESS on success, and EXIT_FAILURE when empty. Returns -1 when the node cannot be found.
 **/
int deleteDataFromList(List *list, void *toBeDeleted){
  //check if list exists
  if(list->head==NULL && list->tail==NULL){
    return EXIT_FAILURE;
  }
  //creating node
  Node *nodeToBeCompared = list->head;

  //comparing nodes to see if one is the same as toBeDeleted
  if (nodeToBeCompared != NULL){
    while(nodeToBeCompared->next != NULL){
      if (list->compare(nodeToBeCompared->data,toBeDeleted) == 0){

        //check if head
        if (nodeToBeCompared ==list->head){
           list->head = nodeToBeCompared->next;
           list->deleteData(nodeToBeCompared->data);
           free(nodeToBeCompared);
           return EXIT_SUCCESS;
        }

        //check if tail
        else if(nodeToBeCompared==list->tail){
          list->tail=nodeToBeCompared->previous;
          list->deleteData(nodeToBeCompared->data);
          free(nodeToBeCompared);
          return EXIT_SUCCESS;
        }

        //if not head or tail
        else{
          nodeToBeCompared->previous->next = nodeToBeCompared->next;
          nodeToBeCompared->next->previous = nodeToBeCompared->previous;
          list->deleteData(nodeToBeCompared->data);
          free(nodeToBeCompared);
          return EXIT_SUCCESS;
        }
      }

      //moving to next node to be checked
      nodeToBeCompared = nodeToBeCompared->next;
    }
    return -1;
  }

return -1;
}


/**Function to return the data at the front of the list.
 *@pre The list exists and has memory allocated to it
 *@param list pointer to the dummy head of the list containing the head of the list
 *@return pointer to the data located at the head of the list
 **/
void *getFromFront(List *list){
  //check if list exists
  if(list->head == NULL && list->tail == NULL){
    return NULL;
  }

  //returns pointer to data located at head of the list.
  return list->head->data;
}

/**Function to return the data at the back of the list.
 *@pre The list exists and has memory allocated to it
 *@param list pointer to the dummy head of the list containing the tail of the list
 *@return pointer to the data located at the tail of the list
 **/
void *getFromBack(List *list){
  //check if list exists
  if(list->head == NULL && list->tail == NULL){
    return NULL;
  }

  //returns pointer to data located at the tail of the list
  return list->tail->data;
}

/**Function to print list from head to tail. This will utilize the list's printData function pointer to print.
 *@pre List must exist, but does not have to have elements.
 *@param list Pointer to linked list dummy head.
 **/
void printForward(List *list){
  //check if list exists
  if(list->head == NULL && list->tail == NULL){
    return;
  }

  //creates node
  Node *nodeToBePrinted = list->head;

  //prints forward using printData
  while (nodeToBePrinted != list->tail){
    list->printData(nodeToBePrinted->data);
    nodeToBePrinted = nodeToBePrinted->next;
  }
  list->printData(list->tail->data);

  //returns void
  return;
}

/**Function to print list from tail to head. This will utilize the list's printData function pointer to print.
 *@pre List must exist, but does not have to have elements.
 *@param list Pointer to linked list dummy head.
 **/
void printBackwards(List *list){
//check if list exists
  if(list->head == NULL && list->tail == NULL){
    return;
  }

  //creates node
  Node *nodeToBePrinted = list->tail;

  //prints backwards using printData
  while (nodeToBePrinted != list->head){
    list->printData(nodeToBePrinted->data);
    nodeToBePrinted = nodeToBePrinted->previous;
  }
  list->printData(list->head->data);

  //returns void
  return;
}

