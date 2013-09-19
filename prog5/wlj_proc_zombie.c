/*
 * 僵死进程产生模型
 * 当子进程先于父进程结束，父进程没有调用wait，处理，将产生僵死进程
 * ps -ef 查看 defunct
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void main()
{
	pid_t pid;
	if ((pid = fork()) == 0)
	{
		printf("Child[%d]\n", getpid());
		exit(0);
	}
	//wait();
	printf("Parent[%d]\n", getpid());
	sleep(60);
}
