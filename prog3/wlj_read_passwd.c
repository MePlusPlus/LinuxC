/*
 * 读取/etc/passwd文件中的注册名称域
 * 字符串解析  注册名:passwd:uid:gid:用户名:/home/xxx:/bin/bash
 * 一个个字符读取 解析
 * 按行读取解析 见其它例子
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fpr, *fpw;
	int c = 0,f = 0;
	//打开文件
	if ((fpr = fopen("/etc/passwd", "r")) == NULL)
	{
		printf("Open file /etc/passwd failed.\n");
		exit(1);
	}
	
	if ((fpw = fopen("./passwd.txt", "w")) == NULL)
	{
		printf("Open file ./passwd.txt failed.\n");
		exit(1);
	}
	
	while ((c = getc(fpr)) != EOF)
	{
		//f是标记，表明是否遇到：
		if (f == 0)
		{
			if (c != ':')
				putchar(fputc(c, fpw));
			else
				f = 1;
		}
		else if (c == '\n')
		{
			f = 0;
			putchar(fputc(c, fpw));
		}
		//其它情况，继续读取下一个字符
	}
		fclose(fpr);
		fclose(fpw);
			
	return 0;
}
