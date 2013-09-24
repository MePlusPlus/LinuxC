/*
 * 获取对方的套接字地址
 * 使用telnet localhost 9001测试
 * meplusplus@qq.com
 */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

//利用宏实现精简if-else代码
//确保b为真，否则返回0  b必须加上括号
#define ASSURE(b,nSock,msg) if(!(b))\
	{\
		close(nSock);\
		fprintf(stderr, "error:%s\n", msg);\
		return;\
	}
void main()
{
	int nSock1, nSock2;  //定义socket描述符，已连接的描述符
	char szAddr[30];
	//创建端口号为9001的监听套接字
	struct sockaddr_in addrin;
	struct sockaddr *paddr = (struct sockaddr*)&addrin;
	memset(&addrin, 0, sizeof(addrin));
	addrin.sin_family = AF_INET;
	addrin.sin_addr.s_addr = htonl(INADDR_ANY);
	addrin.sin_port = htons(9001);
       	
	if ((nSock1 = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "Create sock failed.\n");
		return;
	}
	//命名套接字
	ASSURE(bind(nSock1, paddr, sizeof(addrin)) >= 0, nSock1, "bind error");
	//监听套接字
	ASSURE(listen(nSock1, 100) >= 0, nSock1, "listen error");
	struct sockaddr_in addr_client;
	memset(&addr_client, 0, sizeof(addr_client));
	int size = sizeof(addr_client);
	//等待客户端套接字
	nSock2 = accept(nSock1, (struct sockaddr*)&addr_client, &size);
	ASSURE(nSock2 >=0 , nSock2, "accept error");
	struct sockaddr_in addr_tmp;
	memset(&addr_tmp, 0, sizeof(addr_tmp));
	size = sizeof(addr_tmp);
	ASSURE(getpeername(nSock2, (struct sockaddr*)&addr_tmp, &size)>=0,
		nSock2, "getpeername error");   //获取对方套接字协议地址
	strcpy(szAddr, inet_ntoa(addr_tmp.sin_addr));
	fprintf(stderr, "ip=%s\n", szAddr);
	close(nSock2);
	close(nSock1);
}
