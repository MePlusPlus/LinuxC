/*
 * 网页后台服务程序
 * 客户端端通过http请求，服务器fork一个进程进行响应
 * 通过浏览器访问 localhost:9001/index.html
 * meplusplus@qq.com
 */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

//响应的网页内容
char res[] = 
"HTTP/1.1 200 OK\r\n\r\n"
"<html><head><title>Linux C编程，欢迎您</title></head>"
"<body><b>精通Linux下C语言编程</b><br><b>作者：meplusplus@qq.com</b>"
"<br><b>您的IP是%s</b></body></html>";

void main()
{
	int listen_sock, conn_sock;
	pid_t child;
	char buf[2048], ipaddr[30];
	memset(buf, 0, sizeof(buf));
	//创建TCP套接字描述符
	if((listen_sock=socket(AF_INET,SOCK_STREAM,0)) <= 0)
	{
		fprintf(stderr, "Create sock failed.\n");
		return;
	}
	//命名套接字
	struct sockaddr_in addr_in;
	memset(&addr_in, 0, sizeof(addr_in));
	addr_in.sin_family = AF_INET;
	addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_in.sin_port = htons(9001);
	
	if (bind(listen_sock, (struct sockaddr *)&addr_in, sizeof(addr_in))
		< 0)
	{
		close(listen_sock);
		fprintf(stderr, "Bind sock failed.\n");
		return;
	}
	
	//套接字进入监听状态
	if (listen(listen_sock, 1000) < 0)
	{
		close(listen_sock);
		return;
	}
	struct sockaddr_in addr_client;
	int size;
	memset(&addr_client, 0, sizeof(addr_client));
	size = sizeof(addr_client);
	/*--------父进程--------------------*/
	while(1)
	{
		conn_sock = accept(listen_sock, (struct sockaddr *)&addr_client,
				&size);
		if(conn_sock < 0)
		{
			close(listen_sock);
			fprintf(stderr, "Accept sock failed.\n");
		}
		child = fork();
		if (child == 0)
			break;
		close(conn_sock);   //父进程关闭连接套接字
	}
	/*------子进程-------*/
	close(listen_sock);  //子进程关闭监听套接字
	memset(&ipaddr, 0, sizeof(ipaddr));
	recv(conn_sock, buf, sizeof(buf), 0);
	fprintf(stderr, "-------请求------------\n");
	fprintf(stderr, buf);
	//组建应答包
	sprintf(buf, res, inet_ntoa(addr_client.sin_addr.s_addr));
	send(conn_sock, buf, strlen(buf), 0);
	fprintf(stderr, "---------响应---------------\n");
	fprintf(stderr, buf);
	fprintf(stderr,"\n");
	close(conn_sock);  
}

