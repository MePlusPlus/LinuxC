/*
 * 读取进程的各种标识号
 * meplusplus@qq.com
 */
#include <unistd.h>
#include <stdio.h>
void main()
{
	printf("pid=[%d], gid=[%d], ppid=[%d]\n", getpid(), 
			getpgrp(), getppid());
	printf("uid=[%d], euid=[%d], gid=[%d], egid=[%d]\n",
			getuid(), geteuid(), getgid(), getegid());
}
