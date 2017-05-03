/*
matthew kirt dunning 
project 1
*/

#ifndef q_h
#define q_h
#include <stdlib.h>
#include <stdio.h>

#include "tcb.h"


//tcb given to us containing struct of element contents
typedef struct q
{
	TCB_t *current;
} queue;

void rotateQ(queue *head);
TCB_t* newItem();
queue *initQueue( queue *head);
void addQueue(queue *head, TCB_t *item);
TCB_t* delQueue(queue *head);
void freeItem(TCB_t *item); //optional
void empty_add(queue *head, TCB_t *item); //help figuring this out empty queue
void multiple_add(queue *head, TCB_t *item);// multiple items in the queue
void single_add(queue *head, TCB_t *item); // oneitem in the queue
void dequeue_helper(queue *head, TCB_t *item); // helper for dequeue makes debugging a little easier

// returns a pointer to a new q-element
//only function allowed to allocate memory
TCB_t *newItem()
{
	TCB_t *item = (TCB_t*)malloc(sizeof(TCB_t));
	item->next = 0;
	item->prev = 0;
	return item;
}

//create empty queue pointed to by head
//important as per instructions there is no allocation
queue *initQueue(queue *head)
{
	head->current = 0;
	return head;
}

//no elements in queue addition
void empty_add(queue *head, TCB_t *item)
{
	//set the only item in the queue now to tcb item
	head->current = item;
	item->prev = 0;
	item->next = 0;
}

//multiple elements in queue addition
void multiple_add(queue *head, TCB_t *item)
{
	item->prev = head->current->prev;
	item->next = head->current;
	head->current->prev->next = item;
	head->current->prev = item;
}

//only one element in the queue
void single_add(queue *head, TCB_t *item)
{
	head->current->next = item;
	head->current->prev = item;
	item->next = head->current;
	item->prev = head->current;
}

// adds a queue item, pointed to by “item”, to the queue pointed to by head.
void addQueue(queue *head, TCB_t *item)
{
	// queue is empty 
	if (head->current == 0)
	{
		empty_add(head , item);
	}
	
	// queue contains elements
	else if (head->current->next != 0) 
	{
		multiple_add(head, item);
	}

	//next element is free
	else
	{
		single_add(head, item);	
	}
}

//moves one element up and takes the first one off
//finally working!!!!
void dequeue_helper(queue *head, TCB_t *item)
{

	head->current->prev->next = head->current->next;
	head->current->next->prev = head->current->prev;
	head->current = head->current->next;
}

// deletes an item from head and returns a pointer to the deleted item
struct TCB_t *delQueue(queue *head) 
{
	//first item in the queue
	struct TCB_t *item = head->current;

	if (head->current != 0) 
	{
		//See if items are in the queue if so remove the top and move it all forward
		if (head->current->next != 0) 
		{
			dequeue_helper(head, item);
		}
		else 
		{
			//only one element in queue so delete it 
			head->current = 0;
		}
	}

	return item;
}

// Moves the header pointer to the next element in the queue.
//This is equivalent to AddQ(&head, DeleteQ(&head)), but is simpler to use and more efficient to implement.
void rotateQ(queue *head) 
{
	//given to us in the assignment equal to this statement
	addQueue(head, delQueue(head));
	
	
}

//optional free function
void freeItem(TCB_t *item)
{
	free(item);
}


#endif

