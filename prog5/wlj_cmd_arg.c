/*
 * 命令行参数读取
 * meplusplus@qq.com
 */
#include <stdio.h>
int main(int argc, char *argv[])
{
	int i;
	fprintf(stderr, "argc=[%d]\n", argc);
	for (i=0; i<argc; ++i)
		fprintf(stderr, "argv[%d]=[%s]\n", i, argv[i]);
	return 0;
}
