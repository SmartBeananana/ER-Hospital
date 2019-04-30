/**
 * @file HeapAPI.h
 * @author Michael Ellis
 * @date March 2017
 * @brief File containing the function definitions of a heap
 */


/* notes for students
You must have a second .h file that you write that contains
any extra functions you write for your heap.  You will need additional functions.

In that .h file you MUST have a typedef that  defines the
type "Heap"  and the type "Node".  Heap must be the 
struct that is your main heap,  Node must be the type that is stored in the heap.

typedef somestructhere Heap;
typedef someotherstructhere Node;

*/
#ifndef _HEAP_API_
#define _HEAP_API_

#define MIN_HEAP 0
#define MAX_HEAP 1
#define HEAP_TYPE unsigned char




/**Function to allocate memory to the heap and point the heap to the appropriate functions. Allocates memory to the heap based on the size given.
 *@return pointer to the heap
 *@param initialSize initial size of the heap
 *@param htype flag to choose whether to start the heap as a min heap or max heap. Takes in values MIN_HEAP and MAX_HEAP
 *@param compareFP function pointer to a function that compares two pieces of data.
 *@param destroyDataFP function pointer to a function to delete a single piece of data from the heap
 *@param printNodeFP function pointer to a function that prints out a data element of the heap
 *@return pointer to the heap
 **/
Heap *createHeap(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second));

/**Function for creating a node for a heap.
 *@pre Node must be cast to void pointer before being added.
 *@post Node is valid and able to be added to a heap
 *@param data is a generic pointer to any data type that is to be stored in the heap.
 *@return returns a node for a heap
 **/
Node *createHeapNode(void *data);

/**Inserts a Node into the heap. Uses createHeapNode to place the data in a Node structure, and then puts the newly
 *created Node in the heap by adding at the bottom and comparing it to each parent node until it fits the Heap structure.
 *If the heap is a min heap, if the Node is lesser than the parent, it is swapped. The opposite is true for a max heap.
 *@pre Heap must exist and have data allocated to it
 *@param heap Pointer to a heap
 *@param data Pointer to generic data that is to be inserted into the heap
**/
void insertHeapNode(Heap *heap, void *data);

/**Function to remove the maximum or minimum Node of the heap (depending on min heap or max heap).
 *Once the Node has been deleted, the Node at the deepest point in the Heap is placed in the min/max position.
 *Finally, the heap is heapified to maintain heap property.
 *@pre Heap must exist and have memory allocated to it
 *@param heap Pointer to a heap.
 **/
void deleteMinOrMax(Heap *heap);

/**Function to rearrange a heap to maintain heap property. Starting at the min/max, each Node is compared with its
 *two children to determine the smallest/largest of the three. If the parent is smaller/larger than the child,
 *it is swapped. Heapify is then recursively called on the child in order to continue heapifying until it reaches the bottom of the heap.
 *@param heap Pointer to a heap to be heapified
 **/
void *getMinOrMax(Heap *heap);


/**Function to switch the type of heap from min-to-max or max-to-min. This changes the htype flag from MIN_HEAP
 *to MAX_HEAP and vice versa. Once the flag has been changed, heapify is called on the heap to rearrange it to 
 *fit the new heap property.
 *@param heap Pointer to a heap to switch from min-to-max or max-to-min.
 **/
void changeHeapType(Heap *heap);



/**Function delete a heap. This function calls deleteMinOrMax the same amount of times as the size of the
 *heap, which heapifies after each deletion. Finally, it frees the Heap structure.
 *@param heap Pointer of a heap to be deleted.
 **/
void deleteHeap(Heap *heap);



#endif