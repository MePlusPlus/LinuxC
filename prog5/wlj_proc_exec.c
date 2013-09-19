/*
 * 执行或启动新进程的各种方式
 * meplusplus@qq.ocm
 */
#include <stdio.h>
#include <unistd.h>
extern char *environ;
int main(int argc, char *argv[])
{
	fprintf(stderr, "--begin--\n");
	
	//绝对路径 变长参数 
	execl("/bin/ls", "-l", "-u", 0);
	//绝对路径+变长参数+环境变量
	execle("/bin/ls", "-l", "-u", 0, environ);
	//相对路径，采用在PATH变量中查找  
	execlp("ls", "-l", "-u", 0);
	
	char *arg[] = {"-l", "-u", 0};
	//绝对路径 + 指针数组
	execv("/bin/ls", arg);
	//绝对路径 + 指针数组 + 环境变量
	execve("/bin/ls", arg, environ);
	//相对路径PATH变量 + 指针数组
	execvp("ls", arg);
	return 0;
}
