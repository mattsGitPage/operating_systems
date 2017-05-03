#include <stdio.h>
#include <stdlib.h>
#include "threads.h"




//semaphore data structure contains a value field and tcb queue

typedef struct semaphore
{
	struct queue *semaphores;
	int valueField;
}*mightUse;


void InitSem(struct semaphore *s, int value);//initilizes the value field with the sprcified value
void P(struct semaphore *s); // routine decrements the semaphore and if the value is less than 0 then blocls the process in the queue
void V(struct semaphore *s);// increments the semaphore if value is 0 or negative then takes a pcb and runs it





//initialize the value field witht he specified value

void InitSem(struct semaphore *s, int value)
{
	//allocate space for the semaphore queue
	//not necessary since space must be allocated in main
	s->semaphores = (struct queue*)malloc(sizeof(queue));
	//assign the value of the semaphore
	s->valueField = value;
	
}

//decrement semaphore and blocks prcoess if value is 0
void P(struct semaphore *s)
{
	//decrement semaphore
	s->valueField = s->valueField - 1;

	//check the semaphore value if less than 0
	if(s->valueField < 0)
	{
		// block the process in the queue associated with the semaphore
		TCB_t *tcb = delQueue(RunQ); 
		addQueue(s->semaphores, tcb); 
		swapcontext(&tcb->context, &RunQ->current->context); 
	}
	


}

//increments the semaphore 
void V(struct semaphore *s)
{
	s->valueField = s->valueField + 1;
	
	if (s->valueField <= 0)
	{
		TCB_t *tcb = delQueue(s->semaphores); 
		addQueue(RunQ, tcb);
	}

}
