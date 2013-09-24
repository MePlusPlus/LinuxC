/*
 * 获取套接字level=SOL_SOCKE层的套接字选项
 * meplusplus@qq.com
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <assert.h>

//选项数组
//对于零散数据，用数组组织，循环处理，减少代码使用
int optname[] = 
{
	SO_DEBUG,  //调试跟踪
	SO_REUSEADDR, //重用tcp连接的地址

	//SO_REUSEPORT, //重用端口  
	//linux不支持/usr/include/asm/socket.h
	///* To add :#define SO_REUSEPORT 15 */
	//
	SO_KEEPALIVE, //周期性测试套接字连接是否存在，2个小时
	SO_DONTROUTE, //发送消息是否越过底层协议的路由机制
	SO_LINGER,    //指示是否发送完后立即关闭，不等带确认
	SO_BROADCAST, //是否发送数据包广播
	SO_OOBINLINE, //是否允许外带数据在输入队列中
	SO_SNDBUF,   //发送缓冲区
	SO_RCVBUF,   //接收缓冲区
	SO_SNDLOWAT, //最小发送数据量
	SO_RCVLOWAT, //最小接收数据量
	SO_SNDTIMEO, //发送超时时间
	SO_RCVTIMEO, //接收超时时间
	SO_TYPE,     //套接字类型 SOCK_STREAM, SOCK_DGRAM, SOCK_RAW
	SO_ERROR     //获取和清除error错误，不能应用域setsockopt
};
char  optstr[][20] = 
{
	"SO_DEBUG",  //调试跟踪
	"SO_REUSEADDR", //重用tcp连接的地址
	"SO_REUSEPORT", //重用端口
	"SO_KEEPALIVE", //周期性测试套接字连接是否存在，2个小时
	"SO_DONTROUTE", //发送消息是否越过底层协议的路由机制
	"SO_LINGER",    //指示是否发送完后立即关闭，不等带确认
	"SO_BROADCAST", //是否发送数据包广播
	"SO_OOBINLINE", //是否允许外带数据在输入队列中
	"SO_SNDBUF",   //发送缓冲区
	"SO_RCVBUF",   //接收缓冲区
	"SO_SNDLOWAT", //最小发送数据量
	"SO_RCVLOWAT", //最小接收数据量
	"SO_SNDTIMEO", //发送超时时间
	"SO_RCVTIMEO", //接收超时时间
	"SO_TYPE",     //套接字类型 SOCK_STREAM, SOCK_DGRAM, SOCK_RAW
	"SO_ERROR"     //获取和清除error错误，不能应用域setsockopt
};

void main()
{
	int nSock;
	int i, result, nSize;
	struct linger ling;  //选项SO_LINGER传输数据结构
	struct timeval val1, val2;  //发送，接收超时数据结构
	assert((nSock = socket(AF_INET, SOCK_STREAM, 0)) >= 0);
	for(i=0; i<sizeof(optname)/sizeof(SO_DEBUG);++i)
	{
		result = -1;
		nSize = sizeof(result);
		if((optname[i]==SO_LINGER) ||(optname[i]==SO_SNDTIMEO)||
			(optname[i]==SO_RCVTIMEO))
			continue;
		//获取套接字的值并存入result中
		getsockopt(nSock, SOL_SOCKET, optname[i], &result, &nSize);
		printf("%s:%d\n", optstr[i], result);
	}
	//获取SO_LINGER取值
	nSize = sizeof(ling);
	getsockopt(nSock, SOL_SOCKET, SO_LINGER, &ling, &nSize);
	printf("SO_LINGER:%d.%d\n", ling.l_onoff, ling.l_linger);
	
	//获取SO_SNDTIMEO
	nSize = sizeof(val1);
	getsockopt(nSock, SOL_SOCKET, SO_SNDTIMEO, &val1, &nSize);
	printf("SO_SNDTIMEO:%d.%d\n", val1.tv_sec, val1.tv_usec);
	
	//获取套接字选项SO_RCVTIMEO
	nSize = sizeof(val2);
	getsockopt(nSock, SOL_SOCKET, SO_RCVTIMEO, &val2, &nSize);
	printf("SO_RCVTIMEO:%d.%d\n", val2.tv_sec, val2.tv_usec);
}
