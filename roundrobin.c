//round robin scheduling

#include <stdio.h>
#include <ucontext.>
#include <stdlib.h>
#include <time.h>
#include <error.h>

#define NC 10	//max number of context
#define STACK_SIZE 1024	//stack size allocated to each context

//structure of context queue
struct context_queue{
	ucontext_t *queue;
	int top;
	int bottom;
}cq;


//checking whether all the contexts are already taken
bool is_max_context_allocated(){
	if((top+1)%NC == bottom){
		return true
	}
	
	return flase;
}


//this method is called by user if he/she wants to create a context
ucontext_t create_context(){
	if(is_max_context_allocated()){
		perror("Maximum size limit reached\n");
		exit(0);
	}
	
	top = (top+1)%NC;
	getcontext(&cq[top]);
	cq[top].uc_link = 0;	//link to next context
	cq[top].uc_stack.ss_sp = malloc(STACK_SIZE);
	cq[top].uc_stack.ss_size = STACK_SIZE;
}

int main(){
	

}
