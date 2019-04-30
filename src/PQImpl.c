/**
 * @file PQImpl.c
 * @author Xiangyuan Lian
 * @date July 2018
 * @brief File containing the implementation function of priority queue
 */
#include "PQAPI.h"

PQueue *creatPQueue(size_t initialSize, PQ_TYPE pqtype,
                void (*destroyDataFP)(void *data),
                void (*printNodeFP)(void *toBePrinted),
                int (*compareFP)(const void *first, const void *second))
{
    PQueue *pqueue;
    pqueue = malloc(sizeof(PQueue));

    if(!pqueue)
    {
        return NULL;
    }

    pqueue->heap = createHeap(initialSize, pqtype, destroyDataFP, printNodeFP, compareFP);

    return pqueue;
}

void destroy(PQueue *pqueue)
{
    if (pqueue == NULL)
    {
        return;
    }

    deleteHeap(pqueue->heap);

    free(pqueue);
}

void enQueue(PQueue *pqueue, void *toBeAdded)
{
    if(pqueue == NULL)
    {
        return;
    }
    insertHeapNode(pqueue->heap, toBeAdded);
}

void *deQueue(PQueue *pqueue)
{
    if(pqueue == NULL || pqueue->heap == NULL)
    {
        return NULL;
    }

    void *toBePopped;

    toBePopped = getMinOrMax(pqueue->heap);

    if(toBePopped == NULL)
    {
        return NULL;
    }

    Node *tempNode;

    tempNode = pqueue->heap->array[0];
    pqueue->heap->array[0] = pqueue->heap->array[pqueue->heap->size-1];
    pqueue->heap->array[pqueue->heap->size-1] = tempNode;
    free(pqueue->heap->array[pqueue->heap->size-1]);
    pqueue->heap->size--;

    heapifydown(pqueue->heap, 0);

    return toBePopped;
}
int isEmpty(PQueue *pqueue)
{
    if(pqueue == NULL)
    {
        return 1;
    }
    else if(pqueue->heap->array == NULL || pqueue->heap->size == 0)
    {
        return 1;
    }
    return 0;
}

void *peek(PQueue *pqueue)
{
    if (pqueue == NULL)
    {
        return NULL;
    }

    return getMinOrMax(pqueue->heap);
}
