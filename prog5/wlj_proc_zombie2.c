/*
 * 预防僵死进程 wait方法，托管法，忽略SIGC(H)LD, 捕捉SIGCHLD信号
 * 以下是托管法：父进程先于子进程死亡，则所有子进程由init进程接管
 * 当子进程结束时，init会释放其进程表资源
 * 实验：可以ps看到child2由init进程接管
 * meplusplus@qq.com
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void main()
{
	pid_t pid;
	if ((pid = fork()) == 0)  //第一次fork
	{
		printf("Child1[%d]\n", getpid());
		if ((pid = fork()) == 0)  //第二次fork
		{
			printf("Child2[%d]\n", getpid());
			sleep(20);
			exit(0);   //第二次创建的子进程退出
		}
		exit(0);	   //第一次创建的子进程退出
	}
	waitpid(pid, NULL, WUNTRACED);
	printf("Parent[%d]\n.", getpid());
	sleep(60);
}
