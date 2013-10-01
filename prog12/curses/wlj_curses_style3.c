/*
 * curses效果：字符串在屏幕左右弹来弹去
 * meplusplus@qq.com
 */
#include <curses.h>


#define LEFTEDGE 10
#define RIGHTEDGE 20
#define ROW 10

void main()
{
	char *message = "Hello~";
	char *blank = "      ";
	int dir = 1;
	int pos = LEFTEDGE;
	
	initscr();
	clear();
	
	standout();
	move(ROW,pos);
	addstr("                ");
	while(1)
	{
		move(ROW, pos);
		addstr(message);       //绘制字符串
		move(LINES-1, COLS-1); //光标移到最右下端
 		refresh();	       //展示字符串
		sleep(1);
		move(ROW, pos);
		addstr(blank);	
		pos += dir;
		if (pos >= RIGHTEDGE)
			dir = -1;
		if (pos <= LEFTEDGE)
			dir = +1;
	}
}
