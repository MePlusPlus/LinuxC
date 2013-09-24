/*
 * 根据端口号查询系统服务名词
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
int main(int argc, char **argv)
{
	struct servent *serv;
	if (argc <2 || (serv = getservbyport(htons(atoi(argv[1])),"tcp")) == NULL)
	{
		herror("getservbyname");
		return -2;
	}
	printf("Serv name:%s\n", serv->s_name);
	printf("Serv port:%d\n", ntohs(serv->s_port));
	return 0;
}
