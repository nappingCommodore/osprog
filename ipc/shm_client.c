//Client program for ipc shared memory

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define SIZE 27

int main(){
	int shmid;
	key_t key;
	char *shm,*s;
	
	key = 1234;
	
	if(( shmid = shmget(key,SIZE,0666)) < 0){
		perror("shmget");
		exit(1);
	}
	
	if(( shm = shmat(shmid,NULL,0))==(char*)-1){
		perror("shmat");
		exit(1);
	}
	
	for(s = shm;*s != NULL;s++){
		putchar(*s);
	}
	
	putchar('\n');
	
	*shm = '*';
	
	return 0;
}
