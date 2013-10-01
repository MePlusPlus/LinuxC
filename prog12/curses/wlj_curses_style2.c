/*
 * curses初步使用  
 * 效果2：创造移动的假象
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
	//	if ( i%2 == 0)
			standout();
		addstr("Hello, world");
	//	if( i%2 == 1)
			standend();
		refresh();
		sleep(2);
		move(i, i+i);
		addstr("            ");
	}
	endwin();
}
