/*
 * 守护进程库使用 
 * 通过ps -ef|grep 进程名查看 ?代表后台进程
 * makefile文件编译同不 待解决
 * meplusplus@qq.com
 */

#include "../comlib.h"
#include <unistd.h>
#include <stdio.h>
void main()
{
	printf("pid1=[%d]\n", getpid());
	init_server();
	printf("pid2=[%d]\n", getpid());
	sleep(120);
	//该进程产生的子进程进入后台进程
}
