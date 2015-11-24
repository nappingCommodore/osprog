#include <stdio.h>
#include <ucontext.h>
#include <stdlib.h>

ucontext_t *_main;

int main(){
	_main = malloc (sizeof(ucontext_t));
	getcontext(_main);
	return 0;
}
