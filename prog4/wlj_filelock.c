/*
 * 文件锁操作
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <fcntl.h>

//查询文件fd 从start开锁的len个字节的锁信息
void see_lock(int fd, int start, int len)
{
	struct flock arg;
	arg.l_type = F_WRLCK;
	arg.l_whence = SEEK_SET;
	arg.l_start = start;
	arg.l_len = len;
	
	if (fcntl(fd, F_GETLK, &arg) == -1)
		fprintf(stderr, "See lock failed.\n");
	else if (arg.l_type == F_UNLCK)
		fprintf(stderr, "No lock from %d to %d\n", start, start+len);
	else if (arg.l_type == F_WRLCK)
		fprintf(stderr, "Write lock from %d to %d, id=%d\n", start, 
			start+len, arg.l_pid);
	else if (arg.l_type == F_RDLCK)
		fprintf(stderr, "Read lock from %d to %d, id=%d\n", start,
			start+len, arg.l_pid);
}

//阻塞申请读锁
void get_read_lock(int fd, int start, int len)
{
	struct flock arg;
	arg.l_type = F_RDLCK;
	arg.l_whence = SEEK_SET;
	arg.l_start = start;
	arg.l_len = len;
	if (fcntl(fd, F_SETLKW, &arg) == -1)
		fprintf(stderr, "[%d] Set read lock failed.\n", getpid());
	else
		fprintf(stderr, "[%d] Set read lock from %d to %d\n",
				getpid(), start, start+len);
}

//阻塞申请写锁
//不阻塞版本，使用 F_SETLK
void get_write_lock(int fd, int start, int len)
{
	struct flock arg;
	arg.l_type = F_WRLCK;
	arg.l_whence = SEEK_SET;
	arg.l_start = start;
	arg.l_len = len;
	if (fcntl(fd, F_SETLKW, &arg) == -1)
		fprintf(stderr, "[%d] Set write lock failed.\n", getpid());
	else
		fprintf(stderr, "[%d] Set write lock from %d to %d\n",
				getpid(), start, start+len);
}

//释放锁 有选择释放设置的锁
void release_lock(int fd, int start, int len)
{
	struct flock arg;
	arg.l_type = F_UNLCK;
	arg.l_start = start;
	arg.l_len = len;
	arg.l_whence = SEEK_SET;
	if (fcntl(fd, F_SETLKW, &arg) == -1)
		fprintf(stderr, "[%d] Unlock failed.\n");
	else
		fprintf(stderr, "[%d] Unlock from %d to %d\n",
			getpid(), start, start+len);
}

//测试
void main()
{
	int fd;
	struct flock arg;
	if ((fd = open("./tmplock.txt", O_RDWR|O_CREAT, 0755)) < 0)
	{
		fprintf(stderr, "Open file failed.\n");
		return;
	}
	//查看第1个字节到第10字节
	see_lock(fd,0, 10);
	get_read_lock(fd,0, 10);
	see_lock(fd, 11, 20);
	get_write_lock(fd, 11, 20);
	see_lock(fd, 11, 20);
	sleep(10);
	release_lock(fd, 0, 10);
	release_lock(fd, 11, 20);

	//测试下文件SEEK_SET指向第一个字节前面，还是第一个字节
	//1表示读取第2个字节
	//0表示读取第1个字节
	lseek(fd,0, SEEK_SET);
	char c;
	read(fd, &c, sizeof(c));
	printf("offset=0,char=%c", c);
}
