/*
 * 无名管道的使用
 * 父子进程间通信，父进程向管道写入一行字符，子进程读取并打印
 * meplusplus@qq.com
 */
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
void main()
{
	int fds[2];
	pid_t pid;
	int i,j;
	char buf[256];
	if (pipe(fds) < 0)
	{
		fprintf(stderr, "Pipe error!\n");
		return;
	}
	if ((pid = fork()) < 0)
	{
		fprintf(stderr, "Fork error!\n");
		return;
	}
	if (pid == 0)          //子进程
	{ 
	      	close(fds[1]);  //子进程关闭输出端
		memset(buf, 0, sizeof(buf));
		j = read(fds[0], buf, sizeof(buf));
		fprintf(stderr, "[Child] buf=[%s] len[%d]\n", buf, j);
		return;
	}
	close(fds[0]);		//父进程关闭输入
	write(fds[1], "Hello!", strlen("Hello!"));
	write(fds[1], "Pipe!", strlen("Pipe!"));
}
