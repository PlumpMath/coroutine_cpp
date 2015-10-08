/*************************************************************************
	> File Name: coroutine.c
	> Author: MarkWoo
	> Mail:wcgwuxinwei@gmail.com 
	> Created Time: 2015年09月30日 星期三 04时20分29秒
 ************************************************************************/

#include<stdio.h>
#include <ucontext.h>
#include <unistd.h>

void func1(void *arg) {
	puts("func1");
	sleep(1);
}

void func2(void *arg) {
	puts("func2");
	sleep(1);
}

void func3(void *arg) {
	puts("func3");
	sleep(1);
}

void context_test() {
	char stack_func1[1024 * 256];
	char stack_func2[1024 * 256];
	char stack_func3[1024 * 256];
	ucontext_t child_func1, child_func2, child_func3, context_test_func;

	getcontext(&child_func1);
	getcontext(&child_func2);
	getcontext(&child_func3);
	child_func1.uc_stack.ss_sp = stack_func1; // set stack base pointer
	child_func1.uc_stack.ss_size = sizeof(stack_func1); // set stack size
	child_func1.uc_flags = 0; 
	child_func2.uc_stack.ss_sp = stack_func2; // set stack base pointer
	child_func2.uc_stack.ss_size = sizeof(stack_func2); // set stack size
	child_func2.uc_flags = 0; 
	child_func3.uc_stack.ss_sp = stack_func3; // set stack base pointer
	child_func3.uc_stack.ss_size = sizeof(stack_func3); // set stack size
	child_func3.uc_flags = 0; 
	child_func1.uc_link = &context_test_func; // set succeed run-time context
	child_func2.uc_link = &context_test_func; // set succeed run-time context
	child_func3.uc_link = &context_test_func; // set succeed run-time context

	makecontext(&child_func1, (void (*)(void))func1, 0); // modify context funcional pointer to func1
	makecontext(&child_func2, (void (*)(void))func2, 0); // modify context funcional pointer to func2
	makecontext(&child_func3, (void (*)(void))func3, 0); // modify context funcional pointer to func3

	swapcontext(&context_test_func, &child_func3); // switch to child_func1 context, and save current context into main
	swapcontext(&context_test_func, &child_func2); // switch to child_func1 context, and save current context into main
	swapcontext(&context_test_func, &child_func1); // switch to child_func1 context, and save current context into main
	puts("main"); // if succeed context seted, after func1 finished, go back here
}

int main(void) {
	//ucontext_t context;
	
	context_test();

	//getcontext(&context);
	//puts("Hello World!");
	//sleep(1);
	//setcontext(&context);
	return 0;
}
