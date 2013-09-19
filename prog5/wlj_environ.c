/*
 * 读取操作系统环境变量
 * meplusplus@qq.com
 */
#include <stdio.h>
extern char **environ;
void main()
{
	char **p = environ;
	while(*p)
	{
		fprintf(stderr,  "%s\n", *p);
		p++;
	}
}
