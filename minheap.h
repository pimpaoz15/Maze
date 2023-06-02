#include "Item.h"



struct Heap{
    Item *arr;
    int count;
    int capacity;
    int heap_type; // for min heap , 1 for max heap
};
typedef struct Heap Heap;

Heap *CreateHeap(int capacity,int heap_type);
void insert(Heap *h, Item element);
void print(Heap *h);
void heapify_bottom_top(Heap *h,int index);
void heapify_top_bottom(Heap *h, int parent_node);
Item PopMin(Heap *h);
void FreeHeap(Heap * h);
void CleanHeap(Heap * h);
int LookFor(Heap *h, int index, int prio, int x, int y);



void IncluiCell(Heap *h, int x, int y, int val, char D);
int LessNum(Item a, Item b);
void Heapify(Heap * h, int lim);
void Modify(Heap * h, int index, int newvalue);

typedef struct _cell {
  int pid_x;
  int pid_y;
  int prio;
  char direction;
} Cell;
