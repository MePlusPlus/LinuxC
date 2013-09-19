/*
 * 守护进程生成器
 * meplusplus@qq.com
 */
#include <comlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
//处理SIGCLD信号 预防僵死进程
void clear_child(int sig)
{
	pid_t pid;
	int status;
	//等待任意子进程结束
	//如果没有直接返回  不增加进程负担
	while ((pid = waitpid(-1, &status, WNOHANG)) > 0);
	signal(SIGCHLD, clear_child);
}

//将普通进程转为守护进程
//后台进程特点：后台运行，独立域控制终端，清除文件掩码，处理信号
int init_server()
{
	pid_t pid;
	assert((pid = fork()) >= 0);  //创建子进程
	if (pid != 0)	//父进程退出，子进程托管 实现后台运行
	{
		sleep(1);
		exit(0);
	}
	//独立于控制终端，新建进程组和session
	assert(setsid() >= 0);  
	umask(0);	//清除文件创建掩码
	signal(SIGINT, SIG_IGN);	//忽略SIGINT信号
	signal(SIGCHLD, clear_child);	//处理SIGCLD信号，预防僵死进程
	return 0;
}


