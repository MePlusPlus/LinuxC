/*
 * UDP函数封装
 * meplusplus@qq.com
 */
#include <assert.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
//创建服务器端UDP套接字
//成功返回0，否则-1  sock返回创建的描述符
int create_server_udpsock(int *sock, int port)
{
	struct sockaddr_in addrin;
	struct sockaddr *paddr = (struct sockaddr *)&addrin;
	if(sock == NULL || port <=0)
		return -1;
	memset(&addrin, 0, sizeof(addrin));
	
	addrin.sin_family = AF_INET;
	addrin.sin_addr.s_addr = htonl(INADDR_ANY);
	addrin.sin_port = htons(port);
	
	//创建套接字描述符
	if((*sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		return -1;
	//命名套接字
	if(bind(*sock, paddr, sizeof(addrin)) >= 0)
		return 0;
	close(*sock);
	return -1;
}

//发送数据
//成功返回0，失败返回-1
int send_udp_msg(void *msg, int size, char *addr, int port)
{
	if (msg == NULL || size < 0 || addr == NULL || port < 0)
		return -1;
	int sock;
	struct sockaddr_in addrin;
	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		return -1;
	memset(&addrin, 0, sizeof(addrin));
	addrin.sin_family = AF_INET;
	addrin.sin_addr.s_addr = inet_addr(addr);
	addrin.sin_port = htons(port);
	
	if (sendto(sock, msg, size, 0, (struct sockaddr *)&addrin,
			 sizeof(addrin)) >= 0)
		return 0;
	close(sock);
	return -1;
}

//接收数据
int recv_udp_msg(int sock, void *msg, int *size)
{
	if (sock < 0 || msg == NULL || *size < 0)
		return -1;
	*size = recvfrom(sock, msg, *size, 0, NULL, NULL);
	if (*size > 0)
		return 0;
	return -1;
}
