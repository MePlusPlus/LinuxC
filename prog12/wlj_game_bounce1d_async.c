/*
 * 一维，弹球游戏
 * 使用O_ASYNC标记实现异步IO
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#define MESSAGE "meplusplus"
#define BLANK   "          "

int row = 10;
int col = 0;
int dir = 1;
int delay = 200;
int done = 0;

void main()
{
	void on_alarm(int);	//SIGALRM信号处理函数
	void on_input(int);	//输入事件处理
	void enable_kdb_signals();

	initscr();
	crmode();
	noecho();
	clear();
	
	signal(SIGIO, on_input);
	enable_kbd_signals();		//开启异步IO信号
	signal(SIGALRM, on_alarm);	
	set_ticker(delay);
	
	move(row, col);
	addstr(MESSAGE);
	
	while(!done)
		pause();
	endwin();
}

//简单起见，未处理控制速度
void on_input(int signum)
{
	int c = getch();
	if (c == 'Q' || c == EOF)    //退出，或者 读到结束或中断返回
		done = 1;
	else if(c == ' ') 	     //空格改变方向
		dir = -dir;
}

void on_alarm(int signum)
{
	signal(SIGALRM, on_alarm);
	mvaddstr(row, col, BLANK);
	col += dir;
	mvaddstr(row, col, MESSAGE);
	refresh();

	if(dir == -1 && col <=0)
		dir = 1;
	else if (dir == 1 && col+strlen(MESSAGE) >= COLS)
		dir = -1;
}

//开启异步IO
void enable_kbd_signals()
{
	int fd_flags;
	//设置内核发送输入信号给当前进程，避免发送给其它连接键盘的进程
	fcntl(0, F_SETOWN, getpid());
	fd_flags = fcntl(0, F_GETFL);
	//设置标准输入中异步IO标记，当键盘有字符输入，内核向进程发送SIGIO信号
	fcntl(0, F_SETFL, (fd_flags | O_ASYNC));
}

//设在定时器
int set_ticker(int msec)
{
	struct itimerval timerval;
	long sec,usec;
	
	sec = msec/1000;
	usec = (msec%1000)*1000L;
	
	timerval.it_interval.tv_sec = sec;
	timerval.it_interval.tv_usec = usec;
	
	timerval.it_value.tv_sec = sec;
	timerval.it_value.tv_usec = usec;
	
	return setitimer(ITIMER_REAL,&timerval, NULL);
}
