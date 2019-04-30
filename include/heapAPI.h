/**
 * @file heapAPI.c
 * @author Xiangyuan Lian
 * @date July 2018
 * @brief File containing implementation of heap ADT
 */

#ifndef _HEAP_
#define _HEAP_

/**
 *Heap typedef for struct in heap.h
**/
typedef struct HeapStruct Heap;

/**
 *Node typedef for struct in heap.h
 **/
typedef struct NodeStruct Node;

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/**
 *Node struct of Heap ADT.
 **/
struct NodeStruct{
    void *data;
};

/**
 *Heap struct of a Heap ADT as an array
 **/
struct HeapStruct{
    Node **array;
    size_t size;
    HEAP_TYPE type;
    void (*destroyData)(void *data);
    void (*printNode)(void *toBePrinted);
    int (*compare)(const void *first, const void *second);
};

/**
 *Function to swap elements until the heap property is satisfied form the top
 *to the very bottom of the branch
 *@pre Heap must exists
 *@param Heap pointer to a heap
 *@param index of the array position want to start heapify
 **/
void heapifydown(Heap *heap, int index);

/**
 *Function to swap elements until the heap property is satisfied form the selected
 *node to the very top of the branch
 *@pre Heap must exists
 *@param Heap pointer to a heap
 *@param index of the array position want to start heapify
 **/
void heapifyup(Heap *heap, int index);

#endif
