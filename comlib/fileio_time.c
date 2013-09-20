/*
 * 定时读写函数
 * 超时则返回
 * meplusplus@qq.com
 */
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/select.h>
#include <time.h>
#include <sys/types.h>
#include "comlib.h"
/*---------- 定时读写函数-----*/
//函数在接收足够的输入或写入足够的输出后返回 如果无输入输出则定时完成后函数返回
//0正常 1 超时返回 2 错误
int read_file_time(int fd, void *ptr, int *size, int timeout)
{
	assert(ptr!=NULL && fd>=0 && size != NULL);
	int n = *size;  //每次要读取的数据大小
	int r = 0;	//每次实际读取的数据
	
	time_t t1,t2;
	fd_set read_fds;
	struct timeval tt;  
	int usedtime = 0;
	int flag;
	while(n > 0)
	{
		if(timeout != 0)   //计算剩余时间
			timeout -= usedtime;
		FD_ZERO(&read_fds);   //设置要监控的文件
		FD_SET(fd, &read_fds);
		tt.tv_sec = timeout;   //设置超时时间
		tt.tv_usec = 0;
		t1 = 0;
		t2 = 0;
		time(&t1);    // 获取开始时间
		flag = select(fd+1, &read_fds, NULL, NULL, &tt);
		if (flag == 0)  //超时退出
		{
			*size -= n;
			return 1;
		}
		else if (flag < 0)
		{
			if (errno != EINTR) return 2;
			else
			{
				time(&t2);
				n = 0;
				usedtime = t2 - t1;
			}
		}else
		{
			time(&t2);
			usedtime = t2 - t1;
			if ((r = read(fd, ptr, n)) < 0)
			{
				if (errno != EINTR)
					return 2;
				r = 0;
			}
			else if (r == 0)  //读取结束
				break;
		}
		
		n -= r;
		ptr += r;
	}
	*size -= n;
	return 0;
}

int write_file_time(int fd, void *ptr, int size, int timeout)
{
		assert(fd >=0 && ptr != NULL);
		int n = size;
		int w = 0;
		
		int usedtime = 0;
		time_t t1,t2;
		fd_set write_fds;
		struct timeval tt;
		int flag;
		while (n > 0)
		{
			if (timeout != 0) 
				timeout -= usedtime;
			FD_ZERO(&write_fds);
			FD_SET(fd, &write_fds);
			tt.tv_sec = timeout;
			tt.tv_usec = 0;
			time(&t1);
			flag = select(fd+1,NULL,&write_fds,NULL,&tt);
			if (flag == 0) //超时
			{
				return 1;
			}
			else if (flag < 0)
			{
				if (errno != EINTR) return 2;
				else
				{
					time(&t2);
					usedtime = t2 - t1;
					w = 0;
				}	
			}else
			{
				time(&t2);
				usedtime = t2 - t1;
				if ((w = write(fd, ptr, n)) <=0 )
				{
					if (errno != EINTR) return 2;
					w = 0;
				}
			}
			n -= w;
			ptr += w; 
		}
		return 0;
}
