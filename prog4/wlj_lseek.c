/*
 * lseek 增加文件长度，形成空洞
 * 操作系统对于空洞过大的文件只修改inode的长度，不分配实际空间
 * meplusplus@qq.com
 */
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
void main()
{
	int fd;
	if ((fd = open("hole.dat", O_WRONLY|O_CREAT, 0755)) < 0)
	{
		printf("Open file hole.dat failed.\n");
		return ;
	}
	lseek(fd, 1000000000, SEEK_SET);
	write(fd, "meplusplus", 3);
	close(fd);
}
