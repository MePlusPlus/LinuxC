/*
 * 普通定时器
 * 每隔1秒向进程发送SIGALARM
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int n = 0;
void time_handler(int sig)  //定时事件处理器
{
	fprintf(stderr, "Alarm %d\n", n++);
	//定时器只会定时一次，所以必须重新设置
	signal(SIGALRM, time_handler);
	alarm(1);
}

void main()
{
	int status;
	signal(SIGALRM, time_handler);
	alarm(1);
	while(1);
}
