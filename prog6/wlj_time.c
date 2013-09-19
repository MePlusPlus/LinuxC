/*
 * Linux 时间读取和操作
 * meplusplus@qq.com
 */
#include <time.h>
#include <stdio.h>
#include <unistd.h>
void main()
{
	//读取系统时间秒数
	time_t start, finish;
	time(&start);
	sleep(6);
	time(&finish);
	printf("start=[%d],finish=[%d],difftime=[%f]\n", start, finish,
		difftime(finish,start));
	//读取本地时间字符串
	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);
	printf("now=[%d][%04d%02d%2d %02d:%02d:%02d]\n", now,
		when.tm_year+1900, when.tm_mon+1, when.tm_mday,
		when.tm_hour, when.tm_min, when.tm_sec);

}
