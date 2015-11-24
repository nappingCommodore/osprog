//server program

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(int argc,char* argv[]){

	int socketfd;
	struct sockaddr_in serv_addr;
	
	if(argc < 2){
		perror("Format is <port>\n");
		exit(1);
	}
	
	//get the socket file descriptor
	if(( socketfd = socket(AF_INET,SOCK_STREAM,0) ) < 0)
		error("Error in opening socket\n");
		
		
	//setting the serv_addr field as 0	
	bzero((char *) &serv_addr,sizeof(serv_addr));
	
	//this is the port number provided by user
	int portno = atoi(argv[1]);
	
	//setting all the fields of sockaddr_in structure
	
	//for IPV4 family
	serv_addr.sin_family = AF_INET;
	
	//address setting (structure within structure.. struception)
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	
	//setting port
	serv_addr.sin_port = htons(portno);
	
	//binding socket withh structure
	if(bind(socketfd, (struct socksddr *) &serv_addr,sizeof(serv_addr)) < 0)
		error("Error in socket binding\n");
		
	listen(socketfd,5);
