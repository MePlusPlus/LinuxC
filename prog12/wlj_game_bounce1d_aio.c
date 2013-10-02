/*
 * 一维，弹球游戏
 * 使用aio_read标记实现异步IO
 * aio_read会在读取完成发送信号，进程可以在此期间做其它事情
 *
 * 编译时必须使用 -lcurses -lrt rt库支持aio调用
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <aio.h>
#define MESSAGE "meplusplus"
#define BLANK   "          "

int row = 10;
int col = 0;
int dir = 1;
int delay = 200;
int done = 0;

struct aiocb kbcbuf;		//aio控制缓冲区
void main()
{
	void on_alarm(int);	//SIGALRM信号处理函数
	void on_input(int);	//输入事件处理
	void setup_aio_buffer();

	initscr();
	crmode();
	noecho();
	clear();
	
	signal(SIGIO, on_input);
	setup_aio_buffer();
	aio_read(&kbcbuf);	//不会阻塞进程，完成时发送信号
	signal(SIGALRM, on_alarm);	
	set_ticker(delay);
	
	mvaddstr(row, col, MESSAGE);
	
	while(!done) 		//在这里可以用来做其它事情
		pause();
	endwin();
}

//简单起见，未处理控制速度
void on_input(int signum)
{
	int c;
	char *cp = (char *)kbcbuf.aio_buf;
	
	if (aio_error(&kbcbuf) != 0)
		perror("reading failed");
	else if (aio_return(&kbcbuf) == 1)
	{
		c = *cp;
		if (c == 'Q' || c == EOF)
			done = 1;
		else if (c == ' ')
			dir = -dir;
	}
	//不会阻塞进程，在完成时发送信号
	aio_read(&kbcbuf);
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

//设置aio缓冲区
void setup_aio_buffer()
{
	static char input[1];  //一个字符的输入
	kbcbuf.aio_fildes = 0;	//标准输入，监听标准输入描述符
	kbcbuf.aio_buf    = input; //缓冲区
	kbcbuf.aio_nbytes = 1;	   //需要读取的数目
	kbcbuf.aio_offset = 0;     //从哪里开始读取

	kbcbuf.aio_sigevent.sigev_notify = SIGEV_SIGNAL;  
    	kbcbuf.aio_sigevent.sigev_signo = SIGIO;
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
