/*
 * web服务程序
 * 接收浏览器请求，并在服务器端打印出
 * meplusplus@qq.com
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void main()
{
	int listen_fd,conn_fd; //监听套接字  连接套接字
	char buf[2048];
	//创建端口号为9001的监听套接字
	struct sockaddr_in addrin;
	struct sockaddr *paddr = (struct sockaddr*)&addrin;
	memset(&addrin, 0, sizeof(addrin));
	addrin.sin_family = AF_INET;
	addrin.sin_addr.s_addr = htonl(INADDR_ANY);	//自动分配地址
	addrin.sin_port = htons(9001);
	
	//创建TCP套接字描述符
	if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "Create sock failed.\n");
		return;
	}
	//命名套接字
	if (bind(listen_fd, paddr, sizeof(addrin)) < 0)
	{	
		close(listen_fd);
		return;
	}
	//套接字进入监听状态
	if(listen(listen_fd, 1000) < 0) 
	{
		close(listen_fd);
		return;
	}
	
	//等待客户端连接
	struct sockaddr_in addr_client;
	int size;
	while(1)
	{
		size = sizeof(addr_client);
		memset(&addr_client, 0, sizeof(addr_client));
		//阻塞接收客户端连接请求，并创建新的连接套接字
		conn_fd = accept(listen_fd, (struct sockaddr*)&addr_client,
			&size);
		if (conn_fd > 0)
		{
			memset(buf, 0, sizeof(buf));
			//接收客户端TCP数据消息
			recv(conn_fd, buf, sizeof(buf), 0);
			fprintf(stderr, buf);
			close(conn_fd);	
			continue;
		}
		else if (errno == EINTR) 
			continue;
		else
		{
			fprintf(stderr, "accept failed.\n");
			return;
		}
	}
	
//	memset(buf, 0, sizeof(buf));
	//接收客户端TCP数据消息
//	recv(conn_fd, buf, sizeof(buf), 0);
//	fprintf(stderr, buf);
	close(listen_fd);
	close(conn_fd);	
}
