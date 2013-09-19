/*
 * 读取特定的环境变量
 * meplusplus@qq.com
 */
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	int i = 0;
	for(i=1; i<argc; ++i)
		fprintf(stderr, "%s=%s\n", argv[i], getenv(argv[i]));
	//putenv("wlj=wlj"); //添加环境变量或修改或删除 wlj=
	return 0;
}
