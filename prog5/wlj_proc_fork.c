/*
 * 进程控制 创建子进程 fork
 * meplusplus@qq.com
 */
#include <unistd.h>
#include <stdio.h>
int main()
{
	pid_t pid;
	int i=0;
	
	fprintf(stderr, "Process Begin. pid=[%d], i=[%d]\n", getpid(),
			i);
	//创建子进程
	if ((pid = fork()) > 0)
	{	//父进程会执行
		fprintf(stderr, "Parent pid=[%d], child pid=[%d]\n",
				getpid(), pid);
	}else if (0 == pid)
	{
		//子进程会执行
		fprintf(stderr, "Child pid=[%d]\n", getpid());
		i++;
	}
	else
		fprintf(stderr, "Fork failed.\n");
	//父子进程都会执行
	fprintf(stderr, "Process end. pid=[%d], i=[%d]\n", getpid(), i);
}
