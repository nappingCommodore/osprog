#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <stdint.h>
#include <unistd.h>

#define BUFF_SIZE   5		/* total number of slots */
#define NP          3		/* total number of producers */
#define NC          3		/* total number of consumers */
#define NITERS      4		/* number of items produced/consumed */

typedef struct {
    int buf[BUFF_SIZE];   /* shared var */
    int in;         	  /* buf[in%BUFF_SIZE] is the first empty slot */
    int out;        	  /* buf[out%BUFF_SIZE] is the first full slot */
    int full;     	  /* keep track of the number of full spots */
    int empty;    	  /* keep track of the number of empty spots */
    int mutex;    	  /* enforce mutual exclusion to shared data */
} sbuf_t;

sbuf_t shared;

void sem_acq(int semid){

	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=-1;
	sb.sem_flg=0;

	if((semop(semid,&sb,1))==-1)    {
		perror("\nFailed to acquire semaphore.");
			exit(0);
	}
}


void sem_rel(int semid){
	struct sembuf sb;

	sb.sem_num=0;
	sb.sem_op=1;
	sb.sem_flg=0;
	
	if((semop(semid,&sb,1))==-1)    {
		perror("\nFailed to release semaphore.");
		exit(0);
	}
}

void *Producer(void *arg)
{
    int i, item, index;

    index = (intptr_t) arg;

    for (i=0; i < NITERS; i++) {

        /* Produce item */
        item = i;	

        /* Prepare to write item to buf */

        /* If there are no empty slots, wait */
        sem_acq(shared.empty);
        /* If another thread uses the buffer, wait */
        sem_acq(shared.mutex);
        shared.buf[shared.in] = item;
        shared.in = (shared.in+1)%BUFF_SIZE;
        printf("[P%d] Producing %d ...\n", index, item); fflush(stdout);
        /* Release the buffer */
        sem_rel(shared.mutex);
        /* Increment the number of full slots */
        sem_rel(shared.full);

        /* Interleave  producer and consumer execution */
        if (i % 2 == 1) sleep(1);
    }
    return NULL;
}

void *Consumer(void *arg){
    int item, i, index;
    
    index = (intptr_t)arg;
    
    for(i=0; i < NITERS; i++){
    	
    	sem_acq(shared.full);
    	sem_acq(shared.mutex);
    	
    	item = shared.buf[shared.out];
    	shared.out = (shared.out+1)%BUFF_SIZE;
    	printf("[P%d] Consuming %d ...\n", index, item); fflush(stdout);
    	
    	sem_rel(shared.mutex);
    	
    	sem_rel(shared.empty);
    	
    	if(i % 2 ==1 ) sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t idP, idC;
    int index;

	key_t k1  = ftok(".",1);
	key_t k2  = ftok(".",2);
	key_t k3  = ftok(".",3);
    shared.full = semget(k1,1,0666|IPC_CREAT);
    semctl(shared.full,0,SETVAL,0);
    shared.empty = semget(k2,1,0666|IPC_CREAT);
	semctl(shared.empty,0,SETVAL,BUFF_SIZE);
    shared.mutex = semget(k3,1,0666|IPC_CREAT);
	semctl(shared.mutex,0,SETVAL,1);

    for (index = 0; index < NP; index++)
    {  
       /* Create a new producer */
       pthread_create(&idP, NULL, Producer, (void*)(intptr_t)index);
    }

    for(index = 0; index < NC; index++){
    	pthread_create(&idC, NULL, Consumer, (void*)(intptr_t)index);
    }

    pthread_exit(NULL);
   return 0;
 
}


