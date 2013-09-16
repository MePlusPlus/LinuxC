/*
 * 块写入函数，将数据数据写入文件
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *p;
	//数组数据
	int narray[12] = {1989, 2002, 2005, 2008, 2012, 2015, 2019, 2022,2049,
			  2059, 2069, 0xFFFFFFFF};
	int all = 12; //数组长度
	
 	if ((p = fopen("./array.dat", "wb")) == NULL)
	{
		printf("Open file array.dat failed.\n");
		exit(1);
	}
	//将数据数写入文件  1*sizeof(int) = 4个字符
	fwrite(&all, sizeof(int), 1, p);
	//实际写入数据  
	fwrite(narray, sizeof(int), all, p);
	fclose(p);
	return 0;
}
