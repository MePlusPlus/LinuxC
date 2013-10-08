/*
 * 基于数据报的服务器，负责接收客户端信息v1.0
 *
 * 未实现向客户端发送数据 可以接收地址发送回复
 * meplusplus@qq.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define oops(m,x) {perror(m);exit(x);}

//在 wlj_dgram.c中函数
int make_dgram_server_socket(int);
int get_internet_address(char *, int, int *, struct sockaddr_in *);
void say_who_called(struct sockaddr_in *);

int main(int argc, char* argv[])
{
	int port;
	int sock;
	char buf[BUFSIZ];
	size_t msglen;
	struct sockaddr_in saddr;
	socklen_t  saddrlen;
	
	if (argc == 1 || (port = atoi(argv[1])) <= 0)
	{
		fprintf(stderr, "Usage: dgrecv portnumber\n");
		exit(1);
	}
	
	if ((sock = make_dgram_server_socket(port)) == -1)
		oops("cannot make socket", 2);
	
	saddrlen = sizeof(saddr);
while((msglen = recvfrom(sock, buf, BUFSIZ, 0,(struct sockaddr *) &saddr, &saddrlen)) > 0)
	{
		buf[msglen] = '\0';
		printf("dgrecv:got a message:%s\n", buf);
		say_who_called(&saddr);
	}
	return 0;
}

void say_who_called(struct sockaddr_in *addrp)
{
	char host[BUFSIZ];
	int port;
	get_internet_address(host, BUFSIZ, &port, addrp);
	printf("from:%s:%d\n",host, port);
}
