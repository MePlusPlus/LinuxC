/*
 * 时钟定时
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <signal.h>

//#define SHHHH
void main()
{
	void wakeup(int);
	printf("休眠4秒\n");
	signal(SIGALRM, wakeup);
	alarm(4);
	pause();
	printf("上班时间到了\n");
}

void wakeup(int signum)
{
	#ifndef SHHHH
		printf("从内核收到Alarm信号\n");
	#endif
	
}
