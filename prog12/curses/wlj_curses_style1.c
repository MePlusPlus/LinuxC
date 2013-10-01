/*
 * curses初步使用  
 * 效果1：移动，反色对角线显示
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <curses.h>
void main()
{
	int i;
	initscr();
	clear();
	
	for(i=0; i<LINES; i++)
	{
		move(i, i+i);
		if (i%2 == 1)
			standout();
		addstr("Hello, world");
		if( i%2 == 1)
			standend();
		refresh();
		sleep(2);
	}
	endwin();
}
