
#include<stdio.h>
#include<pthread.h>

int sum=0;

void *add(void* n){

	printf("Thread is running.\n\n");
	int i=0;
	
	int m= *(int*) n;
	
	for(;i<=m;i++){
		sum+=i;
	}
	
	
	pthread_exit(0);
}



int main(){
	pthread_t tid;
	pthread_attr_t attr;
	
	pthread_attr_init(&attr);
	
	int n;
	scanf("%d",&n);
	
	int t1 = time(NULL);
	
	pthread_create(&tid,&attr,add,&n);
	
	printf("Is helper thread running or not?\n\n");
	
	pthread_join(tid,NULL);
	
	printf("Print this after thread completion.\n\n");
	
	int t2 = time(NULL);
	
	printf("%d\n",sum);
	
	printf("t1: %d   t2: %d\n",t1,t2);
	
	printf("Time elapsed between creation and destruction of thread is : %d\n",t2-t1);
	return 0;
}

//	
