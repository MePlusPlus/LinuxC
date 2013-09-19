/*
 * 忽略终止信号SIGINT
 *
 * 在程序运行的20秒内，键入Ctrl+C或delete命令均无法退出
 * meplusplus@qq.com
 */
#include <signal.h>
#include <stdio.h>
void main()
{
	signal(SIGINT, SIG_IGN);
	sleep(20);
}
