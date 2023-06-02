/******************************************************************************
* queue.c
* (c) Miguel Cardoso & Manuel Guilherme
* AED 2021 - 1S
*
* DESCRIPTION
*	Auxiliary functions for Tree  - QUEUE
*
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "queue.h"

struct _element {
  Item this;
  int level;
  struct _element *next;
};

struct _queue {
  Element *first;
  Element *last;
};

/******************************************************************************
 * qEmpty()
 *
 * Arguments: q - pointer to Queue
 *
 * Returns: 1 if empty, 0 otherwise
 * Side-Effects: none
 *
 * Description: checks if Queue is empty
 *
 *****************************************************************************/
int qEmpty(Queue *q){
  if(q->first == NULL) return 1;
  return 0;
}


/******************************************************************************
 * QueueNew()
 *
 * Arguments:
 *
 * Returns: a pointer to Queue
 * Side-Effects: none
 *
 * Description: creates an empty queue
 *
 *****************************************************************************/

Queue *QueueNew()
{
  Queue * q = malloc(sizeof(Queue));
  q->first = NULL;
  q->last = NULL;
  return q;
}


/******************************************************************************
 * InsertLast()
 *
 * Arguments: queue - a queue
 *            this - a "node" to insert last in the queue
 *
 * Returns: void
 * Side-Effects: none
 *
 * Description: inserts an element at the end of a queue
 *
 *****************************************************************************/

void InsertLast(Queue* queue, Item this)
{
  Element *elem;

  if (queue == NULL || this == NULL)
     return;

  elem = malloc(sizeof(Element));
  elem->this = this;
  elem->next = NULL;
  if (queue == NULL)
     return;
  if (queue->last != NULL)
     queue->last->next = elem;
  queue->last = elem;
  if (queue->first == NULL)
     queue->first = elem;

  return;
}


/******************************************************************************
 * GetFirst()
 *
 * Arguments: queue - a queue
 *
 * Returns: pointer to first node in queue
 * Side-Effects: none
 *
 * Description: prints the tree in the Breathfirst format
 *
 *****************************************************************************/

Item GetFirst(Queue* queue)
{
  Element *q = queue->first;
  Item this = (Item) NULL;

  if (queue->first != NULL) {
     queue->first = queue->first->next;

     this = q->this;
     free(q);
  }

  return this;
}

