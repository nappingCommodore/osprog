
//thread library creation using jmp


#include <stdio.h>
#include <malloc.h>
#include <setjmp.h>
#include <signal.h>
#include <stdlib.h>


#define FIBER_STACK 1024*64

jmp_buf child,parent;

void threadFunction(){
        printf("Child fiber switching to parent...\n\n");

        if(setjmp(child)){      //context of child saved
                printf("Child thread exiting...\n\n");
                longjmp(parent,1);      //switched to parent
        }
        longjmp(parent,1);
        printf("AFTER THE LONGJMP\n");
}

void signalHandler(){
        printf("Child fiber is switching to parent in handler...\n\n");
        if(setjmp(child)){
                threadFunction();
        }
        printf("Exiting from handler\n\n");
return;
}


int main(){
        stack_t stack;
        struct sigaction sa;

        stack.ss_flags = 0;
        stack.ss_size = FIBER_STACK;
        stack.ss_sp = malloc(FIBER_STACK);

        if(stack.ss_sp == 0){
                perror("malloc: could not allocated stack\n\n");
                exit(1);
        }

        sigaltstack(&stack,0);

        sa.sa_handler = &signalHandler;
        sa.sa_flags = SA_ONSTACK;

        sigemptyset(&sa.sa_mask);
        sigaction(SIGUSR1,&sa,0);

        printf("Creating child fiber\n\n");
        raise(SIGUSR1);


        printf("Switching to child fiber\n\n");
        if(setjmp(parent)){
                printf("Switching to child fiber\n\n");
                if(setjmp(parent) == 0)
                        longjmp(child,1);

        }

        else{
                longjmp(child,1);
        }

        free(stack.ss_sp);

        printf("Child fiber returned and stack freed\n\n");
        return 0;
}
