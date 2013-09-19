/*
 * 精确定时器，每1.5秒发送SIGPROF
 * meplusplus@qq.com
 */
#include <sys/select.h>
#include <sys/time.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int n = 0;
void time_handler(int sig)
{
	fprintf(stderr, "ITIMER_PROF[%d]\n", n++);
	signal(SIGPROF, time_handler);
}

void main()
{
	struct itimerval value;
	value.it_value.tv_sec = 1;   //it_value本次定时
	value.it_value.tv_usec = 500000;
	value.it_interval.tv_sec = 1;//it_interval下次定时
	value.it_interval.tv_usec = 500000;
	signal(SIGPROF, time_handler);	 //精确定时器信号
	setitimer(ITIMER_PROF, &value, NULL);	//定时开始
	while(1);
}
