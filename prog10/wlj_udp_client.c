/*
 * UDP客户端发送程序
 * meplusplus@qq.com
 */
#include "wlj_udp.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
void main()
{
	char buf[100];
	int i=1,ret=0;
	while(1)
	{
		sprintf(buf, "第%d次发送数据", i);
		ret = send_udp_msg(buf, strlen(buf), "127.0.0.1",9999);
		if (0 == ret)
			printf("Send UDP Message Success:%s\n", buf);
		else
			printf("Send UDP Message Failed:%s\n", buf);
		sleep(2);
		++i;
	}
}
