/*
 * curses库函数
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <curses.h>
void main()
{
	int i;
	initscr();
	clear();
	fprintf(stderr, "%d\n", LINES);	
	for(i=0; i<LINES; ++i);
	{
		move(i, i+1);
		if (i%2 == 1)
			standout();  //使屏幕反色
		addstr("Hello,Curses");
		if (i%2 == 1)
			standend();  //关闭反色模式
	}
	refresh();     //在屏幕上画图
	getch();
	endwin();      //关闭curses,并重置tty
}
