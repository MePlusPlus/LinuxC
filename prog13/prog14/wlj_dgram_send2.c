/*
 * UDP 客户端发送数据给服务器器端v2.0
 * 实现接收服务器端数据
 * meplusplus@qq.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define oops(m,x) {perror(m);exit(x);}

int make_dgram_client_socket();
int make_internet_address(char *,int, struct sockaddr_in *);

int main(int argc, char *argv[])
{
	int sock;
	char *msg;
	struct sockaddr_in saddr;
	char recvdata[BUFSIZ*2];

	if (argc != 4)
	{
		fprintf(stderr, "usage:dgsend host port 'message'\n");
		exit(1);
	}
	
	msg = argv[3];
	if ((sock = make_dgram_client_socket()) == -1)
		oops("cannot make socket", 2);
	
	make_internet_address(argv[1], atoi(argv[2]), &saddr);
	//sendto需要sock，和目的地址
	if (sendto(sock, msg, strlen(msg), 0,(struct sockaddr *) &saddr, sizeof(saddr)) == -1)
		oops("sendto failed", 3);
	
	struct sockaddr_in retaddr;
	socklen_t len = sizeof(retaddr);
	memset(recvdata, 0, sizeof(recvdata));
	//recv只需要sock即可，本地的地址和端口信息已经在sock描述符中
	recvfrom(sock, recvdata, BUFSIZ*2, 0, (struct sockaddr *)&retaddr, &len);
	 	
	printf("reponse from %s:%s", inet_ntoa(retaddr.sin_addr), recvdata); 
	return 0;
}
