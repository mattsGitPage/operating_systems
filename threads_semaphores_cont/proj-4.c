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



struct semaphore *mutex;
struct semaphore *wsem;
struct semaphore *rsem;

int wwc = 0;
int wc = 1;
int rc = 0;
int rwc = 0;
int buff[3];
int n = 3;
int r =0;
int w = 0;

int readers = 0;
int writers = 0;





void ReaderEntry(int reader) {
	
	

	P(mutex);	
	printf("Reader %d Waiting\n", reader);

	if (wwc > 0 || wc > 0){ // any w inside or waiting
		rwc++;// increment wait count
		V(mutex);//open critical section
		printf("reader %d in CS reading\n" , reader);
		P(rsem);//block on reader q
		//P(mutex);// get critical section	
		rwc--;//decrement wait count
	}

	rc++;
	
	sleep(1);
	if(rwc>0){
	//printf("Reader waiting is being woken up\n");
	 V(rsem);
	}
	else{ V(mutex);}

	
}

void ReaderExit(int rExit) {
	
	P(mutex);
	//printf("reader %d exiting ", rExit); not needed
	rc--;
	if (rc == 0 && wwc > 0){
		
		V(wsem);
	}
	
		else{V(mutex);}
	
}

void WriterEntry(int writer) {
	
	
	P(mutex);	
	printf("Writer %d Waiting\n", writer);
	if (rc > 0|| wc > 0 ){
		wwc++;
		V(mutex);
		printf("writer %d in CS writing\n", writer);
		P(wsem);
		//P(mutex);
		wwc--;
	}

	wc++;
	
	
	sleep(1);
	V(mutex);
	
	
}

void WriterExit(int wExit) {
	
	P(mutex);
	
	//printf("writer %d exiting", wExit); not needed in assignment
	wc--;
	if (rwc > 0)
	{
		//printf("waking up a reader\n");
			V(rsem);
		
	}
	else if( wwc> 0)
	{
		
		V(wsem);
	}
	else{V(mutex);}
		
	
}

void reader()
{
	
	P(mutex);
	readers++;
	V(mutex);

	while (go)
	{

		ReaderEntry(readers);
		sleep(go);
		ReaderExit(readers);

	}

}

void writer()
{
	

	P(mutex);
	writers++;
	V(mutex);
	while (go)
	{

		WriterEntry(writers);
		sleep(go);
		WriterExit(writers);
	}

}




int main()
{
	
	//allocate space for the que
	RunQ = (queue *) malloc(sizeof(queue*));
	
	//initialize the queue so the head is pointing to top of list
	RunQ = initQueue(RunQ);


	mutex = (struct semaphore*) malloc(sizeof(struct semaphore));
wsem = (struct semaphore*) malloc(sizeof(struct semaphore));
rsem = (struct semaphore*) malloc(sizeof(struct semaphore));





	InitSem(mutex, 1);
	InitSem(wsem, 0);
	InitSem(rsem, 1);
	
	


start_thread(writer);
start_thread(writer);
start_thread(reader);
start_thread(reader);
start_thread(reader);

	

	//run
	run();

	return 0;
}
