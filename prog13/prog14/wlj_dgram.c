/*
 * UDP Socket封装
 * meplusplus@qq.com
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

#define HOSTLEN 256

int make_internet_address();


//获得一个服务器端的socket
int make_dgram_server_socket(int portnum)
{
	struct sockaddr_in saddr;
	char hostname[HOSTLEN];
	int sock_id;
	
	sock_id = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_id == -1)
		return -1;
	gethostname(hostname, HOSTLEN);
	if(make_internet_address(hostname, portnum, &saddr)!= 0)
		return -1;
	
	if (bind(sock_id, (struct sockaddr *)&saddr, sizeof(saddr))!=0)
		return -1;
	return sock_id;
}

//获得一个客户端udp sock用来发送数据
int make_dgram_client_socket()
{
	return socket(AF_INET, SOCK_DGRAM, 0);
}

//根据主机名和端口号，构造和填充sock地址
int make_internet_address(char *hostname, int port, struct sockaddr_in *addrp)
{
	struct hostent *hp;
	bzero((void *)addrp, sizeof(struct sockaddr_in));
	hp = gethostbyname(hostname);
	
	if (hp == NULL)
		return -1;
	bcopy((void *) hp->h_addr, (void *)&(addrp->sin_addr), hp->h_length);
	
	addrp->sin_port = htons(port);
	addrp->sin_family = AF_INET;
	return 0;
}

//根据Sock地址返回主机名和端口号
int get_internet_address(char *host, int len, int *portp, struct sockaddr_in *addrp)
{
	strncpy(host, inet_ntoa(addrp->sin_addr), len);
	*portp = ntohs(addrp->sin_port);
	return 0;
}
