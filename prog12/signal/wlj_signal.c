/*
 * 测试系统原始信号机制的不可靠问题
 * C表示ctrl+C  \表示ctrl+\
 * CCCC  信号是否排队
 * \C\C  信号中断
 * helloCreturn 输入被中断
 * \\helloC
 * meplusplus@qq.com
 */
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#define INPUTLEN 100
void main()
{
	void inthandler(int);	//SIGINT处理函数
	void quithandler(int);
	char input[INPUTLEN];
	int nchars;

	signal(SIGINT, inthandler);
	signal(SIGQUIT, quithandler);
	
	do
	{
		printf("\n输入一个信息\n");
		nchars = read(STDIN_FILENO, input, INPUTLEN-1);
		if (nchars == -1)
			perror("read error");
		else
		{
			input[nchars] = '\0';
			printf("你输入了:%s", input);
		}

	}while(strncmp(input, "quit", 4)!=0);
}

void inthandler(int s)
{
	printf("收到信号 %d.. waiting\n", s);
	sleep(3);
	printf("退出inthandler\n");
}

void quithandler(int s)
{
	printf("收到信号 %d.. waiting\n", s);
	sleep(4);
	printf("退出quithandler\n");
}
