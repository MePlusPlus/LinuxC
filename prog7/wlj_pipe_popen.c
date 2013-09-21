/*
 * 实现ps -ef|grep init功能
 * 用popen自动在父进程和exec创建的子进程之间建立管道
 */
#include <stdio.h>

void main()
{
	FILE *out, *in;
	char buf[255];
	if ((out = popen("grep init", "w")) == NULL)  //创建写管道流
	{
		fprintf(stderr, "Error!\n");
		return;
	}
	if ((in = popen("ps -ef", "r")) == NULL) //创建读管道流
	{
		fprintf(stderr, "Error!\n");
		return;
	}
	while (fgets(buf, sizeof(buf), in))  //读取管道流
		fputs(buf, out);
	pclose(out);
	pclose(in);
	
}
