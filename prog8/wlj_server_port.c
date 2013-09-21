/*
 * 服务协议名称与端口转换
 * meplusplus@qq.com
 */
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	struct servent *serv;
	if (argc != 2) return -1;
	if ((serv = getservbyname(argv[1], "tcp")) == NULL)
	{
		herror("getservbyname");
		return -2;
	}
	printf("Serv name:%s\n", serv->s_name);
	printf("Serv port:%d\n", ntohs(serv->s_port));
	return 0;
}
