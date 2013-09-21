/*
 * 域名转换程序
 * 根据域名打印IP
 * meplusplus@qq.com
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	struct hostent *host;
	if (argc != 2) 
	{
		printf("usage:domain\n");
		return -1;
	}
	if ((host = gethostbyname(argv[1])) == NULL)
	{
		herror("gethostbyname");
		return -2;
	}
	printf("Host name:%s\n", host->h_name);
	printf("Host IP:%s\n", inet_ntoa(*((struct in_addr *)host->h_addr)));
	return 0;
}
