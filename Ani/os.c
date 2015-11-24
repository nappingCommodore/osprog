#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argn,char * argc[])
{
	int i;
	if(argn==1)
		printf("No commands to run\n");
	else{
		int pid=fork();
		if(pid<0)
			printf("Error");
		else if(pid==0){
			i=execvp(argc[1],argc+1);
			printf("ERROR WHILE EXECUTING\n");
		}
		else
		{
			wait(NULL);
		}
	}
}
