/*
 * 进程同步 使用wait和waitid
 * 父进程等待子进程运行结束
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void main()
{
	pid_t i,j;
	int status;
	if ((i = fork()) == 0)
	{
		fprintf(stderr, "Child begin. pid=[%d]\n", getpid());
		sleep(15);
		fprintf(stderr, "Child end. pid=[%d]\n", getpid());
		exit(20);
	}
	fprintf(stderr, "waiting for child.\n");
	j = wait(&status);
	fprintf(stderr, "Child pid=[%d], exit pid[%d], status[%d]\n",
			i, j, status);
}
