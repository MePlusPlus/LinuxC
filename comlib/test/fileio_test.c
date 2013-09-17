/*
 * 测试阻塞读写函数库
 * meplusplus@qq.com
 */

#include "comlib.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
//读取一定量的数据 
//从标准输入读取，只有读取到了一定量的数据后才返回输出
//只读取指定大小的数据
void main()
{
	//阻塞效果
	char buf[11];
	int size = sizeof(buf);
	read_file(STDIN_FILENO, buf, &size);
	printf("read %dB\n", size);
}
