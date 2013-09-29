/*
 * GET方式的网页刷新器
 * 传递域名和GET参数，指定刷新次数
 * wlj_tcp_http2 www.sina.com /a.php?a=xxx  100
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//组装HTTP协议GET请求报文
char req_buf[] =   
"GET %s HTTP/1.0\r\n"
"Accept:*/*\r\n"
"Accept-Language:zh-cn\r\n"
"Accept-Encoding:gzip,deflate\r\n"
"User-Agent:Mozilla/4.0\r\n"
"Host:%s\r\n"
"Connection:Keep-Alive\r\n\r\n";

int main(int argc, char *argv[])
{
	char res_buf[1024];
	int nSock, i=9999, j=0, loop=0;
	struct hostent *host;
	if (argc != 4)
	{
		fprintf(stderr, "参数错误 主机名 路径  次数\n");
		return -1;
	}
	if ((host = gethostbyname(argv[1])) == NULL)
	{
		herror("gethostbyname");
		return -1;
	}
	loop = atoi(argv[3]);
	fprintf(stderr, "%s\n", inet_ntoa(*((struct in_addr *)host->h_addr)));
	
	FILE *file;
	file = fopen("res1.txt", "w");
	if (file == NULL)
		return -1;
	
	while(loop > 0)
	{
		fprintf(stderr, "-----------%d-------------\n", loop);
		if ((nSock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{
			fprintf(stderr, "create socket error!\n");
			return -1;
		}
		struct sockaddr_in addr_in;
		memset(&addr_in, 0, sizeof(addr_in));
		addr_in.sin_family = AF_INET;
		addr_in.sin_addr = *((struct in_addr *)host->h_addr);
		addr_in.sin_port = htons(80);
	
		if ((connect(nSock, (struct sockaddr *)&addr_in, 
				sizeof(addr_in))) == -1)
		{
			fprintf(stderr, "Connect error!\n");
			return -1;
		}
		//组装请求报文
		sprintf(res_buf, req_buf, argv[2], argv[1]);
		//发送请求报文
	
		int flag = 1;
		int count = 0;
		int len = strlen(res_buf);
		while((count < len) && flag > 0)
		{
			flag = send(nSock, res_buf+count, len-count, 0);
			if (flag > 0)
				count+=flag;
		}
		fprintf(stderr, res_buf);
		flag = 1;
		count = 0;
		while (flag > 0)
		{
			memset(res_buf, 0, strlen(res_buf));
			flag = recv(nSock, res_buf, sizeof(res_buf), 0);
			if (flag > 0)
			count += flag;
			fprintf(stderr, res_buf);
			fprintf(file, res_buf);
		}
		fprintf(stderr,"-----------------\n");
		close(nSock);
		loop--;
	}
	fclose(file);
	return 0;
}
