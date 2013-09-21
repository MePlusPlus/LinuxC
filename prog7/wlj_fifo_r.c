/*
 * 读取有名管道
 * meplusplus@qq.com
 */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

void main()
{
	FILE *fp;
	char buf[255];
	while(1)
	{
		if ((fp = fopen("/root/tempfiles/myfifo", "r")) == NULL)
			return;
		fgets(buf, sizeof(buf), fp);
		fprintf(stderr,"gets:[%s]", buf);
		if (strncmp(buf, "quit", 4) == 0 || 
				strncmp(buf, "exit", 4) == 0)
		break;
		//fclose放在这里才可以，否则无法读取
		fclose(fp);
	}
//	fclose(fp);
}
