//Interpreter design in c

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<pthread.h>
#include<string.h>

#define p 	printf
#define s 	scanf
#define LEN	1000

void execute(char command[]){
	char 	del[] = " \n";
	char* 	token;
	char 	cmd[100] = "/bin/";	//commands 
	char 	paralist[10][20];
	int 	index=1;
	int 	i,j;
	
	token = strtok(command,del);
	
	strcat(cmd,token);
	
	strcpy(paralist[0],cmd);
	
	token = strtok(NULL,del);
	
	while(token!=NULL){
		strcpy(paralist[index++],token);
		token = strtok(NULL,del);
	}
	
	pid_t pid;
	if((pid = fork()) != 0){
		error("child not created.\n\n");
	}
	
	execvp(cmd,paralist,NULL);
	printf("Ooops !! there is something wrong here.....\n");
}

int main(int argc,char* argv[]){
	while(1){
		p("Linux@Linux:~$ ");
		char command[LEN+1]={'\0'};
		fgets(command,LEN,stdin);
		execute(command);
	}
	return 0;
}

