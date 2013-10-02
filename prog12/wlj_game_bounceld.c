/*
 * 弹球游戏：单人弹球v1.0  一维
 * 存在问题：当多次减速以后，两次计时器定时的间隔可能小于一次处理的时间
 * 	     造成多次调用处理函数，是阻塞还是递归调用处理 应该阻塞处理
 * 
 * 单词平滑在屏幕上移动，用户按下空格键就反方向移动
 * s键和f键增加或者减少单词的移动速度
 * Q键退出程序
 *
 * 游戏原理：
 * 状态变量和事件处理
 * 记录位置，方向，延时定义了状态
 * 输入和计时器是改变状态的事件
 * meplusplus@qq.com
 */

#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#define MESSAGE "meplusplus"
#define BLANK   "          "

int row,col;	//位置
int dir; 	//方向

void main()
{
	int delay;	//延时
	int ndelay;	///新的延时
	int c;		//用户输入
	void move_msg(int);	//定时器处理
	int set_ticker(int s); //精确计时器
	
	initscr();
	
	crmode();	//不进行行缓冲，输入立即处理
	noecho();	//输入的字母不回显到屏幕上,可以注释掉这行，看效果
	clear();
	
	row = 10;
	col = 0;
	dir = +1;
	delay = 200;	//200毫秒
	
	move(row, col);
	addstr(MESSAGE);
	signal(SIGALRM, move_msg);
	
	set_ticker(delay);
	
	while(1)
	{
		ndelay = 0;
		c = getch();
		if (c == 'q') break;
		if (c == ' ') dir = -dir;
		if (c == 'f' && delay > 2) ndelay = delay/2;
		if (c == 's') ndelay = delay*2;
		if (ndelay > 0)
			set_ticker(delay=ndelay);
	}
	endwin();
}

void move_msg(int signum)
{
	signal(SIGALRM, move_msg);
	move(row,col);
	addstr(BLANK);
	col += dir;
	move(row, col);
	addstr(MESSAGE);
	refresh();
	
	if(dir == -1 && col <= 0)
		dir = 1;
	else if(dir == 1 && col+strlen(MESSAGE) >= COLS)
		dir = -1;
}

int set_ticker(int s)
{
	struct itimerval timerval;
	long n_sec, n_usec;
	n_sec = s/1000;
	n_usec = (s%1000)*1000L;
	
	timerval.it_interval.tv_sec = n_sec;
	timerval.it_interval.tv_usec = n_usec;
	
	timerval.it_value.tv_sec = n_sec;
	timerval.it_value.tv_usec = n_usec;

	return setitimer(ITIMER_REAL, &timerval, NULL);	
}
