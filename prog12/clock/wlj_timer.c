/*
 * 间隔计时器 精确
 * 每隔500毫秒打印数字，当数字到达0后，退出程序
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>
//毫妙定时器
int set_ticker(int n_msecs)
{
	struct itimerval new_timerset;
	long n_sec, n_usecs;
	n_sec = n_msecs/1000; 		//秒
	n_usecs = (n_msecs%1000)*1000L;	//微妙
	
	new_timerset.it_interval.tv_sec = n_sec;
	new_timerset.it_interval.tv_usec = n_usecs;
	
	new_timerset.it_value.tv_sec = n_sec;
	new_timerset.it_value.tv_usec = n_usecs;
	
	return setitimer(ITIMER_REAL, &new_timerset, NULL);
	
}
void main()
{
	void countdown(int);
	
	signal(SIGALRM, countdown);
	if (set_ticker(500) == -1)
		perror("set_ticker");
	else
		while(1)
		{
			pause();
		}
}

void countdown(int signum)
{
	static int num = 10;
	printf("%d...", num--);
	fflush(stdout);
	if(num < 0)
	{
		printf("DONE!\n");
		exit(0);
	}
}


