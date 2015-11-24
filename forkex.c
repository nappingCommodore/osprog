#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define MAX_COUNT 107
void childProcess(void){
	int i;
	
	for(i = 0 ; i < MAX_COUNT ; i++){
		printf("This is \x1b[33mchild\x1b[0m process, value is %d\n",i);	//"child" in yellow color
	}
	
	printf("	******Child Process is done******	\n");
}

void parentProcess(void){
	int i;
	
	for(i = 0; i < MAX_COUNT; i++)
		printf("This is \x1b[32mParent\x1b[0m process, value is %d\n",i);		//Parent in green color
	
	printf("	******Parent Process is done******	\n");
}

int main(){
	int i=0;
	pid_t pid;
	
	/*if( (pid = fork() ) != 0){
		printf("%d\n\n",pid);
		printf("Error : child process creation unsuccessful\n");
		///_exit(0);
	}*/
	
	pid=fork();
	
	printf("Outside pid : %d\n\n",pid);
	if(pid == 0){
		printf("\n\n\n");
		childProcess();
		//sleep(10000000);
		printf("Exiting from child\n");
		_exit(0);
	}
	
	else{
		printf("\n\n\n");
		parentProcess();
		//sleep(10000000);
		printf("Exiting from parent\n");
		_exit(0);
	}
	
	return 0;
}


//Conclusion:  	As we created child process using fork(), parent process got pid of child (some non negative non zero integer, I got
//				5926,6002 etc. So pid is not zero initially, (in parent process) , parent process run initially, but remember child 
//				has been created and is waiting in background for context switching. After spending one time quantum on parent process
//				CPU switches the context and child process starts running (child process is exact copy of parent process). It return 
//				pid as 0 because in child process pid value is 0. After running for one time quantum, again context switching occurs
//				and control returns to parent process. This back and forth operation happens till one of the process does not end 
//				execution. After ending of one process no context switching occurs and remained process runs till its end.
//
//Remember:		We have to _exit(0) from both the processes. I was not exiting the parent process hence I had to end program using ctrl+c 
//				because program was in stand still mode.
