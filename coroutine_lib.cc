/*************************************************************************
	> File Name: coroutine_lib.cc
	> Author: MarkWoo
	> Mail:wcgwuxinwei@gmail.com 
	> Created Time: 2015年10月08日 星期四 04时00分00秒
 ************************************************************************/

#include<iostream>
#include<string>
#include "coroutine_lib.h"

void Func1(void *args) {
	printf("*******Func1");
}

void Func2(void *args) {
	printf("*******Func2");
}

int UthreadCreate(Schedule &schedule, Fun func, void *args) {
}

int UthreadYield(Schedule &schedule) {
}

void UtheadResume(Schedule &schedule, int id) {
}

int ScheduleFinished(const Schedule &schedule) {
	return 0;
}

int main(void) {
	return 0;
}
