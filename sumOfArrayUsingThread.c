#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>

#define NN 1024

int args[64] ;
int N,P,A[NN],sum=0;
pthreads_mutex_t mut;
pthreads_barrier_t barr;

int init_args(){
	for(int i=0;i<64;i++)
		args[i]=i;
}


int main(){
	
}
