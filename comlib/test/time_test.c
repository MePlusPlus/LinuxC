/*
 * 时间封装函数库的使用
 * meplusplus@qq.com
 */
#include "comlib.h"
#include <stdio.h>
void main()
{
	time_struct now, yes, tom;
	get_time(&now);
  	yes = get_offset_time(&now, 0-24*60*60);
	tom = get_offset_time(&now, 24*60*60);
	printf("now[%04d%02d%02d], yes[%04d%02d%02d], tom[%04d%02d%02d]\n",
		now.nYear,now.nMon,now.nDay,
		yes.nYear,yes.nMon,yes.nDay,
		tom.nYear,tom.nMon,tom.nDay);	
}
