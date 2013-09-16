/*
 * 变长参数使用 不定长参数求和
 * meplusplus@qq.com
 */
#include <stdarg.h>
#include <stdio.h>

int sum(int count, ...)
{
	int res = 0, i = 0;
	va_list ap;
	va_start(ap, count);
	for(i=0; i<count; ++i)
		res += va_arg(ap, int);
	va_end(ap);
	return res;
}

void main()
{
	printf("sum(1,4)=%d\n", sum(1,4));
	printf("sum(2,4,6)=%d\n",sum(2,4,8));
}
