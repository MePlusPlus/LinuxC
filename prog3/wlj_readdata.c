/*
 * 块读入 
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp;
	int *narray;
	int all = 0, i = 0;
	if ((fp = fopen("./array.dat", "rb")) == NULL)
	{
		printf("Open file array.dat failed.\n");
		exit(1);
	}
	//读取文件中的第一个整数，获取存储数据的个数
	fread(&all, sizeof(int), 1, fp);
        
	if ((narray = (int *)malloc(sizeof(int)*all)) == NULL)
	{
		printf("Alloc Memory failed.\n");
		exit(1);
	}

	fread(narray, sizeof(int), all, fp);
	printf("all=%d\n", all);
	for (i=0; i<all; ++i)
	{
		printf("[%d]=%d ", i, narray[i]);
		printf("\n");
	}
	fclose(fp);
	return 0;

}
