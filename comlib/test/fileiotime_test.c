/*
 * 定时读写函数实例
 * meplusplus@qq.com
 */
#include "comlib.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
void main()
{
	char c;
	int size =1, i=0;
	i = read_file_time(STDIN_FILENO, &c, &size, 10);
	if (i == 0)
		printf("%c\n", c);
	else if (i == 1)
		printf("Timeout\n");
	else
		printf("Error\n");
}
