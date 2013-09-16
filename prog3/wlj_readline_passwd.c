/*
 * 按行读取解析 /etc/passwd  输入用户名和用户ID
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	FILE *fpr, *fpw;
	char buf[1024], *p1, *p2;
	
	if ((fpr = fopen("/etc/passwd", "r")) == NULL)
	{
		printf("Open file /etc/passwd failed.\n");
		exit(1);
	}
	if ((fpw = fopen("./readline_pw.txt", "w")) == NULL)
	{
		printf("Open file ./readline_pw.txt failed.\n");
		fclose(fpr);
		exit(1);
	}

	memset(buf, 0, sizeof(buf));
	while (fgets(buf,sizeof(buf), fpr) != NULL)
	{
		if ((p1 = strstr(buf, ":")) == NULL) break;
		if ((p2 = strstr(p1+1, ":")) == NULL) break;
		p1++; //p1指向第二个域
		p2++; //p2指向第三个域
		//以下将ID字段移到用户名字段前面
		while ( *p2 != ':')
		{
			*p1 = *p2;
			p1++;
			p2++;
		}
		*p1 = 0;
		puts(buf);
		fputs(buf, fpw);
		fputs("\n", fpw);
		memset(buf, 0, sizeof(buf));
	}
	fclose(fpr);
	fclose(fpw);
	return 0;
}
