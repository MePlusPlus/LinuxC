/*
 * 输入输出缓冲实例
 * fflush打开 可以保证顺序 1，2，3，4
 * 否则输入 2，1，3，4
 * 因为stdout 是行缓存 \n导致刷新
 * stderr无缓冲
 * meplusplus@qq.com
 */
#include <stdio.h>
void main()
{
	printf(" 1---1 ");
	//fflush(stdout);
	fprintf(stderr, " 2---2 ");
	printf(" 3---3\n");
	fprintf(stderr, " 4---4\n");
}
