/**
 * @file PQAPI.h
 * @author Xiangyuan Lian
 * @date July 2018
 * @brief File containing function definitions of queue
 */
#ifndef _PQ_API_
#define _PQ_API_

#include "heapAPI.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN_PQ 0
#define MAX_PQ 1
#define PQ_TYPE unsigned char

/**
 *Priority queue struct of a priority queue
 **/

typedef struct PQueueStruct{
    Heap *heap;
}PQueue;

/**Function to point the queue to the appropriate functions. Allocates memory to the list.
*@return pointer to the priority queue
*@param the initialized the size of the priority queue
*@param to get the type of the heap MIN or MAX
*@param printFunction function pointer to print a single node of the list
*@param deleteFunction function pointer to delete a single piece of data from the list
*@param compareFunction function pointer to compare two nodes of the list in order to test for equality or order
**/

PQueue *creatPQueue(size_t initialSize, PQ_TYPE pqtype, void (*printFunction)(void *toBePrinted),
                  void (*deleteFunction)(void *toBeDeleted),
                  int (*compareFunction)(const void *first,const void *second));

/** Deletes the entire heap inside queue starting with the heap nodes.
*@pre 'PQueue' type must exists.
*@param priority queue pointer to the Queue-type dummy node
**/
void destroy(PQueue *pqueue);

/**Inserts a Node to the priority queue. The heap then updates according to the priority of node.
*@pre 'Queue' type must exist.
*@param priority queue pointer to the queue
*@param toBeAdded a pointer to data that is to be added to the heap insode queue
**/
void enQueue(PQueue *pqueue, void *toBeAdded);

/**Function to return the data at the front of the heap.
 *@pre The heap inside the queue exists and has memory allocated to it
 *@param queue pointer to the dummy head of the queue
 *@return pointer to the data located at the top of the heap
 **/
void *deQueue(PQueue *pqueue);

/**Function to check the queue is empty or not.
 *@pre 'Queue' type must exist.
 *@param queue poniter to the dummy head of the list containing the head pf the list
 *@return integer 1 on empty; interger 0 on not empty
**/
int isEmpty(PQueue *pqueue);

/**Function to return the data at the front of the queue.
 *@pre The queue exists and has memory allocated to it
 *@param queue pointer to the dummy of the queue.
 *@return void pointer to the data at very top.
 **/
void *peek(PQueue *pqueue);

#endif
