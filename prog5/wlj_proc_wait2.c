/*
 * 进程并发控制监控
 * 父进程发现子进程终止，则重启子进程
 * 利用kill -9测试
 * 父进程发现任意一个子进程结束，就结束所有子进程
 * 然后重启
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void main()
{
	pid_t pid1, pid2, pid3;
	int status;
	while(1)
	{
		if ((pid1 = fork()) < 0)
			exit(1);
		else if (0 == pid1) //子进程
		{
			sleep(30);
			exit(0);
		}
		if ((pid2 = fork()) < 0) exit(1);
		else if (0 == pid2)
		{
			sleep(40);
			exit(0);
		}
		
		/*------父进程----------*/
		fprintf(stderr, "Fork child pid=[%d][%d]\n",pid1,pid2);
		pid3 = wait(&status);  //监控子进程状态
		kill(pid1, SIGTERM);   //杀死子进程1
		kill(pid2, SIGTERM);  //杀死子进程2
		fprintf(stderr, "Kill child pid=[%d][%d], exit pid[%d] status[%d]\n", pid1, pid2, pid3, status);
		pid3 = wait(&status); 	//两个子进程结束，必须wait两次
		sleep(1);
	}		
}
