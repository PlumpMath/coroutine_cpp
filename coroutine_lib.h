/*************************************************************************
	> File Name: coroutine_lib.h
	> Author: MarkWoo
	> Mail:wcgwuxinwei@gmail.com 
	> Created Time: 2015年10月08日 星期四 04时00分39秒
 ************************************************************************/

#ifndef _COROUTINE_LIB_
#define _COROUTINE_LIB_

#include <ucontext.h>
#include <unistd.h>
#include <vector>
#include <cstdio>

#define DEFAULT_STACK_SIZE (1024*512)

enum ThreadState {
	FREE,
	RUNNABLE,
	RUNNING,
	SUSPEND
};

/*
 * coroutine definition(user thread)
 */
typedef void (* Fun)(void *args);
struct Uthread {
	ucontext_t running_context; // using for save coroutine context
	Fun func; // function pointer point to coroutine running function
	void *args;
	enum ThreadState state; // coroutine running state
	char stack[DEFAULT_STACK_SIZE]; // coroutine stack
};

/*
 * coroutine scheduler
 */
typedef std::vector<Uthread> ThreadVector;
struct Schedule {
	ucontext_t main; // save current thread running context
	int running_thread; // current serial num of current running thread 
	ThreadVector threads; // current scheduler own all threads

	Schedule(): running_thread(-1) {}
};

int UthreadCreate(Schedule &schedule, Fun func, void *args);
int UthreadYield(Schedule &schedule);
void UtheadResume(Schedule &schedule, int id);
int ScheduleFinished(const Schedule &schedule);
void UthreadFuncCalled(Schedule &schedule);
void TestSchedule(Schedule &schedule); 

#endif
