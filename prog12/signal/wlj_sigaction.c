/*
 * 使用sigaction信号机制
 * 测试：连续很快ctr+c和ctr+\
 *       或者连续按ctrl+c
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <signal.h>
#define INPUTLEN 100
void main()
{
	struct sigaction newhandler;
	sigset_t blocked;
	void inthandler(int s);
	char x[INPUTLEN];
	
	newhandler.sa_handler = inthandler;
	newhandler.sa_flags = SA_RESETHAND;
	
	sigemptyset(&blocked);
	sigaddset(&blocked, SIGQUIT);
	newhandler.sa_mask = blocked;
	
	if(sigaction(SIGINT, &newhandler, NULL) == -1)
		perror("sigaction");
	else
		while(1)
		{
			fgets(x, INPUTLEN, stdin);
			printf("input:%s", x);
		}	
}

void inthandler(int s)
{
	printf("Called with signal %d\n", s);
	sleep(2);
	printf("done handling signal %d\n", s);
}
