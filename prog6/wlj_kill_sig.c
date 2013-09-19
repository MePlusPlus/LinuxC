/*
 * 父进程创建子进程，并发送SIGTERM信号
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

//子进程捕获信号函数
void child_handler(int sig)
{
	fprintf(stderr, "Get Sig\n");
	exit(6);
}

void main()
{
	pid_t pid;
	int status;
	if ((pid = fork()) < 0) exit(1);
	else if (pid == 0) //子进程
	{
		signal(SIGTERM, child_handler);
		sleep(30);
		exit(0);
	}
	fprintf(stderr, "Parent [%d] Fork Child pid=[%d]\n",
				getpid(), pid);
	sleep(1);
	kill(pid, SIGTERM);	//向子进程发送SIGTERM 唤醒
	wait(&status);
	fprintf(stderr, "Kill Child pid=[%d], exit status[%d]\n",
			pid, status>>8);  //使用exit退出，返回status<<8,所以要还原
}

