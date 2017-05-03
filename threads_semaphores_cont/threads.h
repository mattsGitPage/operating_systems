
#include "q.h"
#include <stdio.h>
#define SIZE 8192


queue * RunQ;

//psuedo code given in assignment
void start_thread(void(*routine)(void))
{
	//allocate a stack of given size
	void * stack = malloc(SIZE);

	//allocate a TCB with function created in q
	TCB_t * tcb = newItem();
	
	//call init_TCB with appropriate arguments
	init_TCB(tcb, routine, stack, SIZE);

	//call addQ to add this TCB into the RUNQ which is global header pointer
	addQueue(RunQ, tcb);

}


//code given in the assignment
void run() 
{ //real code

	ucontext_t parent;   // get a place to store the main context, for faking
	getcontext(&parent);  //magic sauce
	swapcontext(&parent, &(RunQ->current->context));

}


//code given in assignment
//similar to run just add the rotation
void yield() 
{
	ucontext_t parent;
	getcontext(&parent);
	
	//rotate according to psuedo code
	rotateQ(RunQ);

	//rotated so next next item should be up
	swapcontext(&parent, &(RunQ->current->context));
}
