/*
 * 时间封装
 * meplusplus@qq.com
 */
#include "comlib.h"
#include <string.h>
//读取时间 返回自定义结构
time_struct* get_time(time_struct *timeptr)
{
	static time_struct tmp;
	if (timeptr == NULL)
	{
		timeptr = &tmp;
	}
	time_t t;
	struct tm *when;
	time(&t);
	when = localtime(&t);
	timeptr->nYear = when->tm_year + 1900;
	timeptr->nMon = when->tm_mon + 1;
	timeptr->nDay = when->tm_mday;
	timeptr->nMin = when->tm_min;
	timeptr->nHour = when->tm_hour;
	timeptr->nSec = when->tm_sec;
	return timeptr;
}

//时间差
time_struct get_offset_time(time_struct *timeptr, int offsetsec)
{
	time_struct ts;
	if (timeptr == NULL)
	{
		get_time(&ts);
	}
	time_t t;
	struct tm when;
	memset(&when, 0, sizeof(when));
	when.tm_year = timeptr->nYear - 1900;
	when.tm_mon = timeptr->nMon - 1;
	when.tm_mday = timeptr->nDay;
	when.tm_hour = timeptr->nHour;
	when.tm_min = timeptr->nMin;
	when.tm_sec = timeptr->nSec;
	t = mktime(&when);
	t += offsetsec;
	when = *localtime(&t);
	ts.nYear = when.tm_year + 1900;
	ts.nMon = when.tm_mon + 1;
	ts.nDay = when.tm_mday;
	ts.nMin = when.tm_min;
	ts.nHour = when.tm_hour;
	ts.nSec = when.tm_sec;
	return ts;
}
