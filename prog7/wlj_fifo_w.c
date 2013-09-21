/*
 * 有名管道的使用
 * 双进程读写管道，特殊文件FIFO
 * 管道在读写的时候，两端必须同时打开
 * 写进程打开写端，运行后阻塞，直到读进程打开读端，开始读取
 *
 * 这是写有名管道
 * meplusplus@qq.com
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <stdio.h>
#include <string.h>
extern int errno;
void main(int argc, char *argv[])
{
	FILE *fp;
	char buf[255];
	//创建管道，如果已存在则跳过
	if (mkfifo("/root/tempfiles/myfifo", S_IFIFO|0666) < 0 && errno != EEXIST) return;
	while(1)
	{
		if ((fp = fopen("/root/tempfiles/myfifo", "w")) == NULL)
			return;
		fprintf(stderr,"please input:");
		
		fgets(buf,sizeof(buf),stdin);
		fputs(buf, fp);
		//以换行符结束方便读端
		fputs("\n", fp);
		if (strncmp(buf, "quit", 4) == 0 ||
				 strncmp(buf, "exit", 4) == 0)
			break;
		//fclose应该在这理关闭，不然每次重新打开，存在多个写端
		//或者将打开文件移到循环外，否则无法读取数据
		//原因？
		fclose(fp);
	}
//	fclose(fp);
}
