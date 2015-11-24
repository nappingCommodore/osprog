#include<stdio.h>
#include<pthread.h>
#include<sys/sem.h>
#include<unistd.h>
#include<string.h>
#include<stdint.h>

#define NN 10

void sem_acq(int semid){
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=-1;
	sb.sem_flg=0;
	
	if((semop(semid,&sb,1))==-1){
		perror("\nFailed to acquire semaphore\n");
		//exit(0);
	}
}

void sem_rel(int semid){

	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=-1;
	sb.sem_flg=0;
	
	if((semop(semid,&sb,1))==-1){
		perror("\nFailed to release semaphore\n");
		//exit(0);
	}
}


int read_count = 0;
int wr_sem,mutex;

void *Reader(void* arg){
	int x = (intptr_t) arg;
	sem_acq(mutex);
	read_count+=1;
	
	if(read_count == 1)
		sem_acq(wr_sem);
	sem_rel(mutex);
	
	printf("Reader %d is reading...\n",x);
	fflush(stdout);
	
	sem_acq(mutex);
	read_count-=1;
	printf("Reader %d finished reading...\n",x);
	fflush(stdout);
	
	if(read_count == 0)
		sem_rel(wr_sem);
	sem_rel(mutex);
	
	return NULL;
	
}

void *Writer(void* arg){
	int x = (intptr_t) arg;
	sem_acq(wr_sem);
	printf("Writer %d is writing...\n",x);
	printf("Writer %d finished writng...\n",x);
	fflush(stdout);
	sem_rel(wr_sem);
	return NULL;
}

int main(){
	pthread_t rd_thread,wr_thread;
	int i;
	
	mutex=semget(IPC_PRIVATE,1,0666|IPC_CREAT);
	semctl(mutex,0,SETVAL,1);
	
	wr_sem=semget(IPC_PRIVATE,1,0666|IPC_CREAT);
	semctl(wr_sem,0,SETVAL,1);
	
	for(i=1;i<=NN;i++){
		pthread_create(&rd_thread,NULL,Reader,(void*)(intptr_t)i);
		pthread_create(&wr_thread,NULL,Writer,(void*)(intptr_t)i);
	}
	
	for(i=1;i<=NN;i++){
		pthread_join(rd_thread,NULL);
		pthread_join(wr_thread,NULL);
	}
	
	return 0;
}
	
