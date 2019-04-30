/**
 * @file heapImpl.c
 * @author Xiangyuan Lian
 * @date July 2018
 * @brief File containing implementation of heap
 */

#include "heapAPI.h"

Heap *createHeap(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{
    Heap *newHeap;

    newHeap = malloc(sizeof(Heap));
    newHeap->array = malloc(sizeof(Node)*initialSize);
    newHeap->size = 0;
    newHeap->type = htype;
    newHeap->destroyData = destroyDataFP;
    newHeap->printNode = printNodeFP;
    newHeap->compare = compareFP;

    return newHeap;
}

Node *createHeapNode(void *data)
{
    if(data == NULL)
        return NULL;

    Node *newNode;

    newNode = malloc(sizeof(Node));
    newNode->data = data;

    return newNode;
}

void insertHeapNode(Heap *heap, void *data)
{
    Node *newNode;

    newNode = createHeapNode(data);

    if(newNode == NULL)
        return;

    heap->array[heap->size] = newNode;
    heap->size++;

    heapifyup(heap,heap->size-1);
}

void deleteMinOrMax(Heap *heap)
{
    if(heap == NULL)
        return;

    Node *tempNode;

    tempNode = heap->array[0];
    heap->array[0] = heap->array[heap->size-1];
    heap->array[heap->size-1] = tempNode;
    heap->destroyData(heap->array[heap->size-1]->data);
    free(heap->array[heap->size-1]);
    heap->size--;

    heapifydown(heap, 0);
}

void *getMinOrMax(Heap *heap)
{
    if(heap == NULL)
        return NULL;

    return heap->array[0]->data;
}

void changeHeapType(Heap *heap)
{
    if(heap == NULL)
        return;

    int i;

    if(heap->type == MIN_HEAP)
    {
        heap->type = MAX_HEAP;
    }
    else if(heap->type == MAX_HEAP)
    {
        heap->type = MIN_HEAP;
    }
    for(i = heap->size/2-1; i>=0; i--)
    {
        heapifydown(heap, i);
    }
}

void deleteHeap(Heap *heap)
{
    if(heap == NULL)
        return;

    if(heap->array == NULL)
    {
        free(heap);
        return;
    }

    int i = 0, heapSize = 0;
    heapSize = heap->size;

    for(i=0; i<heapSize; i++)
    {
        deleteMinOrMax(heap);
    }
    free(heap->array);
    free(heap);
}

void heapifydown(Heap *heap, int index)
{
    if(heap == NULL)
        return;

    int left = 2 * index + 1;
    int right = left + 1;
    int significant = index;
    int multiplier = 1;

    if(heap->type == MIN_HEAP)
    {
        multiplier = -1;
    }

    if(left < heap->size && (heap->compare(heap->array[left]->data, heap->array[significant]->data)*multiplier)>0)
    {
        significant = left;
    }
    if(right < heap->size && (heap->compare(heap->array[right]->data, heap->array[significant]->data)*multiplier)>0)
    {
        significant = right;
    }
    if(significant != index)
    {
        Node *tempNode;
        tempNode = heap->array[index];
        heap->array[index] = heap->array[significant];
        heap->array[significant] = tempNode;
        heapifydown(heap, significant);
    }
}

void heapifyup(Heap *heap, int index)
{
    if(heap == NULL)
        return;

    int parent = (index-1)/2;
    int multiplier = 1;

    if(heap->type == MIN_HEAP)
    {
        multiplier = -1;
    }
    if (parent>=0 && (heap->compare(heap->array[parent]->data,heap->array[index]->data)*multiplier)<0)
    {
        Node *tempNode;
        tempNode = heap->array[index];
        heap->array[index] = heap->array[parent];
        heap->array[parent] = tempNode;
        heapifyup(heap, parent);
    }
}
