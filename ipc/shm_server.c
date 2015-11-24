//server client using ipc shared memory

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
	
	if(( shmid = shmget(key,SIZE,IPC_CREAT|0666)) < 0){
		perror("shmget");
		exit(0);
	}
	
	if(( shm = shmat(shmid,NULL,0)) == (char*) -1){
		perror("shmat");
		exit(1);
	}
	
	s = shm;
	
	char c;
	for(c = 'a';c <= 'z'; c++)
		*s++ = c;
	*s = NULL;
	
	
	while(*shm != '*')
		sleep(1);
		
	return 0;
} 
