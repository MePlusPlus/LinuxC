/*
 * 双向管道流模型
 * 管道为单向通信模型，必须建立两个管道才能建立双向通信
 *
 * 本例子父进程首先向子进程传送两次数据，再接收子进程
 * 回复的两次数据
 * 数据传输采用显示长度+数据，采用网络字节序
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
//管道 固定长度操作 每次发送或读取固定长度的数据
//缺少则填充
void write_same(int fd, char *ptr, int len)
{
	assert(len <= 255);
	char buf[255];
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%s", ptr);
	write(fd, buf, len);
}

char *read_same(int fd, char *ptr, int len)
{
	static char buf[255];
	if (ptr == NULL)  ptr = buf;
	memset(ptr, 0, sizeof(buf));
	read(fd, ptr, len);
	return ptr;
}

//显示长度，发送数据前先发送长度 例如0006Hello!
//采用网络字节序
//但是本列子采用字符串传递，不需要考虑字序
void write_len(int fd, char *str)
{
	char buf[255];
	sprintf(buf, "%04d%s", strlen(str), str);
	write(fd, buf, strlen(buf));
}

char *read_len(int fd, char *ptr)
{
	static char buf[255];
	if (ptr == NULL) ptr = buf;
	int i,j;
	memset(ptr, 0, sizeof(ptr));
	j = read(fd, ptr, 4);  //读取长度域
	i = atoi(ptr);
	j = read(fd, ptr, i);
	return ptr;
}

void main()
{
	int fds1[2], fds2[2];
	pid_t pid;
	char buf[255];
	if (pipe(fds1) < 0 || pipe(fds2) < 0)
	{
		fprintf(stderr,"Pipe error!\n");
		return;
	}
	if ((pid = fork()) < 0)
	{
		fprintf(stderr, "Fork error!\n");
		return;
	}
	if (pid == 0)
	{
		//子进程
		close(fds1[1]);
		close(fds2[0]);
		strcpy(buf, read_same(fds1[0], NULL, 20));
		fprintf(stderr, "[child] buf=[%s]\n", buf);
		write_len(fds2[1], "Hello father!");  //回传
		return;
	}
	//父进程
	close(fds1[0]);
	close(fds2[1]);
	write_same(fds1[1], "Hello child!", 20);
	fprintf(stderr, "[father] buf=[%s]\n", read_len(fds2[0], NULL));
}
