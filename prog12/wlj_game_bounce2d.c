/*
 * 二维弹球游戏
 * 关键是球斜着移动
 * 构造两个定时器，用于控制水平和垂直方向移动
 * meplusplus@qq.com
 */

#include <curses.h>
#include <sys/time.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include "bounce.h"

struct ppball the_ball;

void set_up();
void wrap_up();

void main()
{
	int c;
	set_up();
	while((c = getchar()) != 'q')
	{
		//水平方向加减速
		if (c == 'f') 
			the_ball.x_ttm==1?the_ball.x_ttm:the_ball.x_ttm--;
		else if(c == 's') the_ball.x_ttm++;
		//垂直方向加减速度
		else if (c == 'e') 
			the_ball.y_ttm==1?the_ball.y_ttm:the_ball.y_ttm--;
		else if(c == 'c') the_ball.y_ttm++;
	}
	wrap_up();
}

void set_up()
{
	void ball_move(int);
	the_ball.y_pos = Y_INIT;	//球初始y位置
	the_ball.x_pos = X_INIT;	//球初始x位置
	//ttg 表明当前值，下次重画之前需要等待的计时信号数
	//ttm 表明间隔值，两次移动之间要等待的计时信号数
	//通过这两个值控制水平和垂直方向速度
	the_ball.y_ttg = the_ball.y_ttm = Y_TTM; //球初始水平方向
	the_ball.x_ttg = the_ball.x_ttm = X_TTM; //垂直方向，x轴表所行
	the_ball.y_dir = +1;
	the_ball.x_dir = +1;
	the_ball.symbol = DFL_SYMBOL;
	
	initscr();
	noecho();
	crmode();
	
	signal(SIGINT, SIG_IGN);
	//在指定位置输出字符
	mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);
	refresh();
	
	signal(SIGALRM, ball_move);
	//每个tick多少毫秒
	set_ticker(1000/TICKS_PER_SEC);
}

void wrap_up()
{
	set_ticker(0);
	endwin();
}

void ball_move(int signum)
{
	int y_cur, x_cur, moved;
	signal(SIGALRM, SIG_IGN);	//忽略SIGALRM信号
	
	y_cur = the_ball.y_pos;
	x_cur = the_ball.x_pos;
	moved = 0;
	
	//ttm表示重画间隔时间
	//ttg==1时，表示定时信号到了，要进行相应方向的移动
	//移动时水平和垂直方向以8:5左右移动
	//如果节拍TICKS_PER_SEC设在大一些，移动速度将快一点
	if (the_ball.y_ttm > 0 && the_ball.y_ttg-- == 1)
	{
		the_ball.y_pos += the_ball.y_dir;
		the_ball.y_ttg = the_ball.y_ttm;
		moved = 1;
	}
	if (the_ball.x_ttm > 0 && the_ball.x_ttg-- == 1)
	{
		the_ball.x_pos += the_ball.x_dir;
		the_ball.x_ttg = the_ball.x_ttm;
		moved = 1;
	}
	if (moved)
	{
		mvaddch(y_cur, x_cur, BLANK);
		mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);
		bounce_or_lose(&the_ball);
		move(LINES-1, COLS-1);
		refresh();
	}
	signal(SIGALRM, ball_move);
}

int bounce_or_lose(struct ppball *bp)
{
	int return_val = 0;
	if (bp->y_pos == TOP_ROW)
	{
		bp->y_dir = 1;
		return_val = 1;
	}
	else if(bp->y_pos == BOT_ROW)
	{
		bp->y_dir = -1;
		return_val = 1;
	}
	
	if (bp->x_pos == LEFT_EDGE)
	{
		bp->x_dir = 1;
		return_val = 1;
	}else if(bp->x_pos == RIGHT_EDGE)
	{
		bp->x_dir = -1;
		return_val = 1;
	}
	return return_val;
}

int set_ticker(int ms)
{
	struct itimerval timerval;
	long n_sec, n_usec;
	n_sec = ms/1000;
	n_usec = (ms%1000)*1000L;
	
	timerval.it_interval.tv_sec = n_sec;
	timerval.it_interval.tv_usec = n_usec;
	
	timerval.it_value.tv_sec = n_sec;
	timerval.it_value.tv_usec = n_usec;
	
	return setitimer(ITIMER_REAL, &timerval, NULL);
}
