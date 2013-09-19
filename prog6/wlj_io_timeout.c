/*
 * 单进程IO超时处理三种方式
 * 终端方式，信号跳转方式，多路复用方式
 *
 * 一般接收输入或者发送，超过一定时间，超时返回
 *
 * 本例子从标准输入读取一个字符，3秒后超时返回
 * meplusplus@qq.com
 */
#include <unistd.h>
#include <termio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>

void termio();   //终端方式
void sigio();	 //信号跳转方式
void selectio();  //IO多路复用方式
void main()
{
	char cmd[256];
	printf("IO超时处理方式选择\n");
	while(1)
	{
		printf("[1]终端方式 [2]信号跳转方式 [3]多路服用方式\n");
		scanf("%s", cmd);
		switch(cmd[0])
		{
			case '1':
				termio();
				break;
			case '2':
				sigio();
				break;
			case '3':
				selectio();
				break;
			case '0':
				exit(0);
				break;
			default:
				break;
		}
				
        }
}

void termio()
{
	struct termio old, new;
	char c = '0';
	//读取终端配置
	ioctl(STDIN_FILENO, TCGETA, &old);
	new = old;
	new.c_lflag &= ~ICANON;
	new.c_cc[VMIN] = 0;
	new.c_cc[VTIME] = 30;	//超时时间为3秒
	//设置终端配置
	ioctl(STDIN_FILENO, TCSETA, &new);
	if ((read(STDIN_FILENO, &c, 1)) != 1)
		printf("timeout\n");
	else printf("\n%c\n", c);
	ioctl(STDIN_FILENO, TCSETA, &old);
}
jmp_buf env;
int timeout = 0;

void time_handler(int sig)
{
	timeout = 1;
	longjmp(env,1);
}
void sigio()
{
	char c;
	signal(SIGALRM, time_handler);
	setjmp(env);
	if (timeout == 0)  //正常处理
	{
		alarm(3);
		read(STDIN_FILENO, &c, 1);
		alarm(0);
		printf("%c\n", c);
	}
	else
		printf("timeout\n");
}

void selectio()
{
	struct timeval tt;
	fd_set readfds;
	int i;
	char c;
	tt.tv_sec = 3;
	tt.tv_usec = 0;
	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);
	//第一个参数是文件描述符数量
	i = select(1, &readfds, NULL, NULL, &tt);
	if (i > 0)
	{
		read(STDIN_FILENO, &c, 1);
		printf("%c\n", c);
	}
	else if (0 == i)
		printf("timeout\n");
	else
		printf("error\n");
}
