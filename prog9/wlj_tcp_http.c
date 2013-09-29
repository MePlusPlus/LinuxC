/*
 * 网页投票器v1.0
 * meplusplus@qq.com
 */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
//组装Http协议GET请求报文
//尝试自动投票  大众投票网
char request[] =
	"POST /2013/anlpwy/vote.jsp HTTP/1.1\r\n"
	"HOST:tp.dzwww.com\r\n"
	"Connection:keep-alive\r\n"
	"Content-Length:162\r\n"
	"Cache-Control:max-age=0\r\n"
	"Accept:text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
	"Origin:http://tp.dzwww.com\r\n"
	"User-Agent:Mozilla/5.0\r\n"
	"Referer:http://tp.dzwww.com/2013/anlpwy/\r\n"
	"Accept-Language:zh-cn\r\n"
	"Accept-Encoding:gzip,deflate,sdch\r\n"
	"Accept-Charset: GBK,utf-8\r\n"
	"Cookie: JSESSIONID=555033F94DFEE2B716305E2907B10EC2.a\r\n\r\n"
	"UserNo=38601&UserNo=38602&UserNo=38603&UserNo=38604&UserNo=38605&UserNo=38606&UserNo=38607&UserNo=38608&UserNo=38609&UserNo=38610&yzm=nxndd&input.x=110&input.y=19\r\n";

void main()
{
	char response[8192];
	int nSock;
	fprintf(stderr, "-------投票开始-------\n");
	if((nSock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		fprintf(stderr, "socket error!\n");
		return;
	}
	struct sockaddr_in addr_in;
	memset(&addr_in, 0, sizeof(addr_in));
	addr_in.sin_family = AF_INET;
//	addr_in.sin_addr.s_addr = inet_addr("119.75.217.56");
//	addr_in.sin_addr.s_addr = htonl(inet_addr("124.133.228.111"));
	addr_in.sin_addr = *((struct in_addr *)(gethostbyname("tp.dzwww.com")->h_addr)); 
	addr_in.sin_port = htons(80);
	struct sockaddr *addr = (struct sockaddr *)&addr_in;
	//注意：如果参数为sizeof(addr) 将导致 参数无效 错误，连接不上
	//sizeof指针变量 在32位系统为4字节
	//sizeof数组变量 求得是数组的大小 两者不同
	//本处必须是指针所指空间的大小
	if(connect(nSock, addr, sizeof(*addr)) == -1)
	{
		fprintf(stderr, "connect error:%s\n", strerror(errno));
		return;
	}
	send(nSock, request, sizeof(request), 0);
	fprintf(stderr, request);
	memset(response, 0, sizeof(response));
	recv(nSock, response, sizeof(response), 0);
	fprintf(stderr, response);
	FILE *file;
	if ((file = fopen("res.txt","w")) == NULL)
	{
		fprintf(stderr, "file create error!\n");
		return;
	}
	fprintf(file,"%s", response);
	fclose(file);
	close(nSock);
	fprintf(stderr, "-------投票结束[%d]---------\n", strlen(response));
}
