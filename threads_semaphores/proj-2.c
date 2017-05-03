/*
matthew kirt dunning
*/


#include "sem.h" // includes thread.h
#include <unistd.h>


// some global variables for random computations
int go = 1;
int x = 0;
int y = 0;
int num = 0;
int check = 1;
int global = 0;


struct semaphore* semaphore;

//create some random funtions to execute
void add()
{
	
	//shouldnt have a stopping condition
	while (go)
	{
		P(semaphore);
		x = x + go;
		y = y + go;

		//for sum of nat nums
		num++;
		
		printf("incremented x using a semaphore is : %d ", x);
		printf("\t incremented y using a semaphore is :  %d \n\n", y);

		sleep(go);
		V(semaphore);
		yield();

	}
}
//create some random funtions to execute
void strStuff()
{

	//shouldnt have a stopping condition
	while (go)
	{
		P(semaphore);
		//for even odd function
		check++;
		
		printf("just doing nothing \n\n");

		sleep(go);
		V(semaphore);
		yield();

	}
}
//more random functions with local and global variables
void localNGlobal()
{
	int local = 5;
	while(go)
	{
		P(semaphore);
		local = local + x;
		local = local % y;
		printf("local variable is : %d \n\n" , local);
		
		sleep(go);
		V(semaphore);
		yield();
	}



}

void sumNatNum()
{
	int sum = 0;

	while(go)
	{
	P(semaphore);
	for(int i = 1; i <= num; i++)
	{
		sum = sum + i;
	}
	
	printf("sum of first %d natural numbers is = %d \n\n", num, sum);
	
	sleep(go);
	V(semaphore);
	yield();
	}

}

void oddOrEven()
{

	while(go)
	{
	P(semaphore);
	if(check % 2 == 0)
		printf("number %d is even \n\n", check);
	else
		printf("number %d is odd \n\n", check);

	sleep(go);
	V(semaphore);
	yield();
	}
}

void gNl()
{

	while(go)
	{
		int local;
		P(semaphore);
		local++;
		global++;
		printf("threaded semaphore 1 has entered CS %d times and both have entered a total of %d times\n\n", local , global);
		sleep(go);
		V(semaphore);
		yield();
		
	}

}

void gNl2()
{

	while(go)
	{
		int local;
		P(semaphore);
		local++;
		global++;
		printf("threaded semaphore 2 has entered CS %d times and both have entered a total of %d times\n\n", local , global);
		sleep(go);
		V(semaphore);
		yield();
	}

}


int main()
{
	
	//allocate space for the que
	RunQ = (queue *) malloc(sizeof(queue*));
	
	//initialize the queue so the head is pointing to top of list
	RunQ = initQueue(RunQ);

	semaphore = (struct semaphore*) malloc(sizeof(struct semaphore));

	InitSem(semaphore, 1);
	

	//assign the functions to execute
	void *execute1 = add;
	void *execute2 = strStuff;
	void *execute3 = localNGlobal;
	void *execute4 = sumNatNum;
	void *execute5 = oddOrEven;

	//start the random functions
	start_thread(execute1);
	start_thread(execute2);
	start_thread(execute3);
	start_thread(execute4);
	start_thread(execute5);
	start_thread(gNl);
	start_thread(gNl2);
	

	//run
	run();

	return 0;
}
