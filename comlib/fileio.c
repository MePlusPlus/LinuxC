/*
 * 文件读写函数封装库阻塞读写
 * meplusplus@qq.com
 */
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include "comlib.h"
/*-------  文件阻塞读写函数库 保证读写确定字符数的函数 -------*/
//读取*size个数据 或者遇到结束错误  size返回实际的字符数
//读取函数容易出现错误或者不足值，必须处理
int read_file(int fd, void *ptr, int *size)
{
	assert(ptr!=NULL && fd >= 0 && size != NULL);
	int n = *size; //每次要读取的数据大小
	int r = 0;     //每次已读取的数据
	//处理信号中断或者其它不足值情况
	while(n > 0)
	{
		if ((r = read(fd, ptr, n)) < 0)
		{
			if (errno != EINTR)
				assert(0);
			r = 0;
		}
		else if (r == 0) break;
		n -= r;			//更新剩下需要读取的数据大小
		ptr += r;		//更新读取的缓冲区位置
	}
	
	*size -= n;   //返回已读取数据大小  如果读完，n=0, *size不变
	return 0;
}

//写入size个字符
int write_file(int fd, void *ptr, int size)
{
	assert(fd >=0 && ptr != NULL);
	int n = size;	//剩下未读取的
	int w = 0;	//已经写入的数据大小
	while(n > 0)
	{
		if ((w = write(fd, ptr, n)) <= 0)
		{
			if (errno != EINTR)
				assert(0);
			w = 0;
		}
		n -= w;
		ptr += w;
	}
	return 0;
}


