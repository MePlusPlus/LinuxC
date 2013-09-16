/*
 * 标准IO库 文件打开和读写
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
	FILE *fp;
	char szBuf[100];
	
	//将屏幕输出的内容重定向到文件 ./1.tmp
	if ((fp = freopen("./1.tmp", "w", stdout)) == NULL)
	{
		printf("stdout -- ./1.tmp failed.\n");
		return 1;
	}
	
	//标注输出已经重定向 现在写入文件
	printf("I Like UNiX and C.\n");
	fflush(fp);
	fclose(fp);
	
	//由于标准输出已经重定向，未恢复，下面使用stderr作为输出
	//或者上面改为stderr
	//标准输入重定向
	if ((fp = freopen("./1.tmp", "r", stdin)) == NULL)
	{
		fprintf(stderr,"stdin -- ./1.tmp failed\n");
		return 1;
	}
	
	memset(szBuf, 0, sizeof(szBuf));
	//标准输入已经重定向，从文件中读取
	gets(szBuf);
	fprintf(stderr,"szBuf=[%s]\n", szBuf);
	fclose(fp);

	return 0;
}
