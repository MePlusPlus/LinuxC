/*
 * unlink删除文件
 * 对于临时文件打开以后，可以先删除，再使用，不会造成磁盘垃圾
 * meplusplus@qq.com
 */

#include <stdio.h>
#include <fcntl.h>

void main()
{
	int fd;
	if ((fd = open("./tmpfile", O_RDWR|O_CREAT|O_EXCL, 0755)) < 0)
	{
		fprintf(stderr, "Open file error!\n");
		return ;
	}
	//执行这部操作，其它进程无法访问 tmpfile
	//当该进程执行完毕，自动删除tmpfile
	unlink("./tmpfile");
	sleep(60);
	printf("End.\n");
}
