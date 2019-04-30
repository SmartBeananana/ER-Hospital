/**
 * @file testQueue.c
 * @author Xiangyuan Lian
 * @date July 2018
 * @brief File containing implementation of priority queue unit test
 */
#include "PQAPI.h"
#include "test.h"

void printNode(void *toBePrinted);
void destroyData(void *toBeDeleted);
int compare(const void *first,const void *second);

int main(int argc, char **argv)
{
    int testNumber = 0, testsPassed = 0;
    int *num, *num1, *num2, *num3, *num4;
    int empty = 0;

    printf("*******************Start Testing Section*******************\n\n");

    PQueue *pq;

    pq = creatPQueue(100,MIN_PQ,destroyData,printNode,compare);
    testNumber++;
    printTestInfo(testNumber, "Testing the initialized priority queue is not null");
    printf("Expect: Not NULL\n");
    printf("Received: %p\n", (void *)pq);
    testsPassed += printPassFail(pq != NULL);

    num1 = malloc(sizeof(int));
    *num1 = 1;
    testNumber++;
    printTestInfo(testNumber, "Testing insert a node into priority queue");
    enQueue(pq, num1);
    printf("Expect: 1\n");
    printf("Received: %d\n",*((int *)(pq->heap->array[0]->data)));
    testsPassed += printPassFail(*((int *)(pq->heap->array[0]->data)) == *num1);

    testNumber++;
    printTestInfo(testNumber, "Testing remove a node from priority queue");
    num = deQueue(pq);
    printf("Expect: 1\n");
    printf("Received: %d\n",*((int *)num));
    testsPassed += printPassFail(*num == *num1);

    testNumber++;
    printTestInfo(testNumber, "Testing the queue is not empty.");
    empty = isEmpty(pq);
    printf("Except: 1\n");
    printf("Received: %d\n",empty);
    testsPassed += printPassFail(empty == 1);

    num2 = malloc(sizeof(int));
    *num2 = 2;
    enQueue(pq, num2);
    num3 = malloc(sizeof(int));
    *num3 = 3;
    enQueue(pq, num3);
    num4 = malloc(sizeof(int));
    *num4 = 4;
    enQueue(pq, num4);
    testNumber++;
    printTestInfo(testNumber, "Testing to get the data at the front of the queue");
    num = peek(pq);
    printf("Except: 2\n");
    printf("Received: %d\n",*num);
    testsPassed += printPassFail(*num == 2);

    printf("Testing destory funtion with valgrind and cppCheck\n");
    printf("The function works well when there is no memory leak reported\n\n");

    printf("The total number of testing: %d\n", testNumber);
    printf("-----The total number of test passed: %d-----\n\n", testsPassed);


    destroy(pq);

    return 0;
}

void destroyData(void *toBeDeleted)
{
    free(toBeDeleted);

}

int compare(const void *first,const void *second)
{
    int a,b;

    a = *((int*)first);
    b = *((int*)second);

    return a-b;
}

void printNode(void *toBePrinted)
{
    printf("%d ", *((int*)toBePrinted));
}
