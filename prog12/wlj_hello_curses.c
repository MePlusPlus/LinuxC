/*
 * curses库函数
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <curses.h>
void main()
{
	initscr();   //初始化curses
	clear();     //清屏
	move(10,20); //光标移到10,20的位置
	addstr("Hello,Curses");  //在光标出画字符串
	move(LINES-1,0);
	refresh();
	getch();	
	endwin();
}
