/******************************************************************************
 *
 * File Name: heap.c
 *	      (c) Miguel Cardoso e Manuel Guilherme
 *
 * NAME
 *     Heap operations
 *
 * DESCRIPTION
 *		implements abstract type of heap, both min and max;
 *
 *****************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "minheap.h"



/******************************************************************************
 * CreateHeap()
 *
 * Arguments: capacity - heap size
 *            heap_type - 0 for minHeap, 1 for maxHeap
 * Returns: Heap
 * Side-Effects: none
 *
 * Description: allocates space for a new heap of specified size
 *
 *****************************************************************************/
Heap *CreateHeap(int capacity,int heap_type){
    Heap *h = (Heap *) malloc(sizeof(Heap)); //one is number of heap

    if(h == NULL) exit(0);
    h->heap_type = heap_type;
    h->count=0;
    h->capacity = capacity;
    h->arr = (Item *) malloc(capacity*sizeof(Item)); //size in bytes

    //check if allocation succeed
    if ( h->arr == NULL) exit(0);
    return h;
}

/******************************************************************************
 * insert()
 *
 * Arguments: h - pointer to heap
 *            element - pointer to new element
 * Returns: void
 * Side-Effects: none
 *
 * Description: add element at the end of heap and do fixup
 *
 *****************************************************************************/

void insert(Heap *h, Item element){
    if( h->count < h->capacity){
        h->arr[h->count] = element;
        heapify_bottom_top(h, h->count);
        h->count++;
    } else{
        h = (Heap*) realloc(h, sizeof(h->arr) + 2 * sizeof(Item));
        if(h == NULL) exit(0);
        h->capacity += 2;
        h->arr[h->count] = element;
        heapify_bottom_top(h, h->count);
        h->count++;
    }
    return;
}

/******************************************************************************
 * swap()
 *
 * Arguments: a - Item
 *            b - Item
 * Returns:
 * Side-Effects: none
 *
 * Description: exchanges a and b (abstract types)
 *
 *****************************************************************************/
void swap(Item a, Item b)
{
    Item aux;
    aux = (Item *) malloc(sizeof(Item));
    aux = a;
    a = b;
    b = aux;
    free(aux);
    return;
}

/******************************************************************************
 * heapify_bottom_top()
 *
 * Arguments: h - pointer to heap structure
 *            index - index of element to fixup
 * Returns:
 * Side-Effects: none
 *
 * Description: Performs fixup from index
 *
 *****************************************************************************/
void heapify_bottom_top(Heap *h,int index){
    Item *t;
    if (index==0) return;
    int parent_node = (index-1)/2;

    if(!LessNum(h->arr[parent_node],h->arr[index])){
        t = h->arr[index];
        h->arr[index] = h->arr[parent_node];
        h->arr[parent_node] = t;
        heapify_bottom_top(h,parent_node);
    }
}

/******************************************************************************
 * heapify_top_bottom()
 *
 * Arguments: h - pointer to heap structure
 *            parent_node - index of element to fixdown
 * Returns:
 * Side-Effects: none
 *
 * Description: performs fixdown from index
 *
 *****************************************************************************/
void heapify_top_bottom(Heap *h, int parent_node){
    Item *t;
    int left = parent_node*2+1;
    int right = parent_node*2+2;
    int min;

    if(left >= h->count || left <0)
        left = -1;
    if(right >= h->count || right <0)
        right = -1;

    if(left != -1 && LessNum(h->arr[left], h->arr[parent_node]))
        min=left;
    else
        min =parent_node;
    if(right != -1 && LessNum(h->arr[right], h->arr[min]))
        min = right;

    if(min != parent_node){
        t = h->arr[min];
        h->arr[min] = h->arr[parent_node];
        h->arr[parent_node] = t;
        heapify_top_bottom(h, min);
    }
}

/******************************************************************************
 * PopMin()
 *
 * Arguments: h - pointer to heap
 * Returns: Item
 * Side-Effects: none
 *
 * Description: exchange first and last element of heap, remove last element
 *              (min element) from heap and maintain heap order by performing
 *              a fixdown of the first element
 *
 *****************************************************************************/
Item PopMin(Heap *h){
    Item pop;
    if(h->count==0) return ((Item*) NULL);

    // replace first node by last and delete last
    pop = h->arr[0];
    h->arr[0] = h->arr[h->count-1];
    h->count--;
    heapify_top_bottom(h, 0);
    return pop;
}

/******************************************************************************
 * Modify()
 *
 * Arguments: h - pointer to heap
 *            index - index of element to modify
 *            newvalue - new element value
 * Returns: void
 * Side-Effects: none
 *
 * Description: compares new element with antecedent, if larger do a fixup
 *              otherwise do fixdown
 *
 *****************************************************************************/
void Modify(Heap * h, int index, int newvalue)
{
    Cell *aux;
    if (index > h->count - 1 || index < 0) return;

    aux = (Cell*) h->arr[index];

    if (newvalue < aux->prio)
    {
        aux->prio = newvalue;
        heapify_top_bottom(h, index);
    }
    else
    {
        aux->prio = newvalue;
        heapify_bottom_top(h, index);
    }

    return;
}

/******************************************************************************
 * print()
 *
 * Arguments: h - pointer to heap
 * 
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints Heap on the command line
 *
 *****************************************************************************/
void print(Heap *h){
    Cell *aux;
    int i;
    printf("____________Print Heap_____________\n");
    for(i=0;i< h->count;i++){
        aux = (Cell*) h->arr[i];
        printf("-> X: %d Y: %d P: %d", aux->pid_x, aux->pid_y, aux->prio);
    }
    printf("->__/\\__\n");
}

void FreeHeap(Heap *h)
{
  CleanHeap(h);
  free(h->arr);
  free(h);
 return;
}

/******************************************************************************
 * CleanHeap()
 *
 * Arguments: Heap
 * Returns: none
 * Side-Effects: None
 *
 * Description: cleans an heap
 *
 *****************************************************************************/
void CleanHeap(Heap * h)
{
  int i=0;

  for(i=0;i<h->count;i++){
    free(h->arr[i]);
  }

  h->count= 0;

    return;
}

/******************************************************************************
 * HeapSort()
 *
 * Arguments: Heap
 * Returns: void
 * Side-Effects:
 *
 * Description: sorts an heap using the heapsort algorithm
 *
 *****************************************************************************/
void HeapSort(Heap * h)
{
Item t;
  int l, n;
  n= h->count;
  Heapify(h, n);

  for(l=h->count-1; l>0; l--){
    t = (h->arr) [0];
    (h->arr)[0] = (h->arr)[l];
    (h->arr)[l] = t;
    h->count--;
    heapify_top_bottom(h,0);
  }
  h->count = n;

}

/******************************************************************************
 * Heapify()
 *
 * Arguments: Heap
 * Returns: void
 * Side-Effects:
 *
 * Description: forces the argument to be an heap
 *
 *****************************************************************************/
void Heapify(Heap * h, int lim)
{
  while(lim>=0){
    heapify_top_bottom(h, lim);
    lim--;
  }
    return;
}