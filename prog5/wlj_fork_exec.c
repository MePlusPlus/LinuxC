/*
 * 启动运行进程的fork-exec模型
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <unistd.h>
void main()
{
	pid_t pid;
	if ((pid = fork()) == 0) //子进程
	{
		fprintf(stderr, "--begin--\n");
		sleep(2);
		//execl会替换掉子进程的空间
		execl("/bin/ls", "-l", "/root", 0);
		//该句不会执行
		fprintf(stderr, "--end--\n");
	}else if (pid > 0) //父进程
		fprintf(stderr, "Fork child pid=[%d]\n", pid);
	else
		fprintf(stderr, "Fork failed.\n");
	fprintf(stderr, "--parent process end--\n");
}
