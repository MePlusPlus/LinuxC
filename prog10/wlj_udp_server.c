/*
 * UDP服务器端数据接收程序
 * meplusplus@qq.com
 */
#include "wlj_udp.h"
#include <stdio.h>
#include <string.h>

void main()
{
	int sock, size;
	char buf[256];
	create_server_udpsock(&sock, 9999);
	size = sizeof(buf);
	
	//循环接收数据
	while(recv_udp_msg(sock, buf, &size) == 0)
	{
		printf("Recv UDP Data:[%d][%s]\n", size, buf);
		size = sizeof(buf);
	}
	close(sock);
}
