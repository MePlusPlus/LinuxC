/*
 * 文件读写定位，随机读取文件
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <stdlib.h>

//写入第rec个整数
void seekwrite(FILE *fp, int data, int rec)
{
	fseek(fp, sizeof(int)*rec, SEEK_SET);
	fwrite(&data, sizeof(int), 1, fp);
}

//读取文件第rec个整数
int seekread(FILE *fp, int *data, int rec)
{
	fseek(fp, sizeof(int)*rec, SEEK_SET);
	fread(data, sizeof(int), 1, fp);
	return *data;
}

int main(int argc, char *argv[])
{
	FILE *fp;
 	int narray[5] = {100, 200, 300, 400, 500};
	int data[2];
	if ((fp = fopen("seek.dat", "wb")) == NULL)
	{
		printf("Open file seek.dat failed.\n");
		exit(1);
	}
	seekwrite(fp, narray[0], 1);
	//形成空洞
	seekwrite(fp, narray[1], 10);
	
	seekread(fp, data, 1);
	seekread(fp, data+1, 10);
	
	printf("now data1=%d, data10=%d\n", data[0], data[1]);
	fclose(fp);
	return 0;
}
