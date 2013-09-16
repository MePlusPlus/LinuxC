/*
 * 读取文件系统信息
 * meplusplus@qq.com
 */
#include <sys/types.h>
#include <sys/statfs.h>
#include <sys/vfs.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
	struct statfs buf;
	if (argc != 2)
	{
		printf("Usage:fs filename.\n");
		exit(EXIT_FAILURE);
	}
	
	if (statfs(argv[1], &buf))
	{
		printf("read filesystem info failed.\n");
		exit(EXIT_FAILURE);
	}
	
	printf("File System:\ntype=%d\n", buf.f_type);	//文件系统类型
	printf("bsize=%d\n", buf.f_bsize);		//数据块大小
	printf("blocks=%d\n", buf.f_blocks);		//数据块总数
	printf("bfree=%d\n", buf.f_bfree);		//可用块数
	printf("files=%d\n", buf.f_files);		//可用inode总数
	printf("ffree=%d\n", buf.f_ffree);		//可用inode数
	printf("%s :%dblocks %di-nodes\n", argv[1],
		buf.f_bfree, buf.f_ffree);
	return 0;
}
