//pipe communication example

#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int i=0;

int main(){
	char write_msg[BUFFER_SIZE]="Greetings";
	char read_msg[BUFFER_SIZE];
	int fd[2];
	pid_t pid;
	
	if(pipe(fd)==-1){
		fprintf(stderr,"Pipe failed\n");
		return 1;
	}
	
	pid = fork();
	
	if(pid < 0){
		printf("%d\n\n",i++);
		fprintf(stderr,"fork failed\n");
		return 1;
	};
	
	if(pid > 0){	//parent
		printf("Parent i = %d\n\n",i);
		i++;
		close(fd[READ_END]);
		write(fd[WRITE_END],write_msg,strlen(write_msg)+1);
		printf("\n\n\nParent process executed. Message passed to child process.\n\n\n");
		close(fd[WRITE_END]);
	}
	
	else{		//child
		printf("Child i = %d\n\n",i);
		i++;
		close(fd[WRITE_END]);
		read(fd[READ_END],read_msg,BUFFER_SIZE);
		printf("Child process is reading the message.\n");
		printf("Read: %s\n\n\n",read_msg);
		close(fd[READ_END]);
		
	}
	return 0;
}
