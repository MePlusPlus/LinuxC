/*
 * 目录操作实例
 * meplusplus@qq.com
 */
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

void main()
{
	int flag = 0;
	char c[128];
	DIR *pdir;
	char cmd[256];
	//之前由于这里pringf写错，编译未检测出，
	printf("按照下列提示，操作\n");
	while(1)
	{
		printf("[1]改变当前工作目录 [2]创建目录 [3]删除目录 [4]读取目录	[5]目录定位  [0]退出\n");
		//scanf("%c", &c);
		//switch出现以下错误
		//a label can only be part of a statement
		//应该在case语句加上{}	
		scanf("%s", c); //回车符去掉
		printf("输入目录路径 回车结束\n");
		scanf("%s", cmd);
		switch(c[0])
		{//这两句放在这里无法执行，switch直接跳转到case
	//		printf("输入目录路径 回车结束\n");
	//		scanf("%s", cmd);
			case '1':
			{
				chdir(cmd);
				printf("当前工作目录= [%s]\n",
					getcwd(cmd, sizeof(cmd)));
				break;
			}
			case '2':
			{
				mkdir(cmd, 0777);
				printf("OK!\n");
				break;
			}
			case '3':
			{
				rmdir(cmd);
				printf("OK!\n");
				break;
			}
			case '4':
			{
	//			DIR *pdir;
				struct dirent *pent;
				if ((pdir = opendir(cmd)) == NULL)
				{
					printf("failed!\n");
					break;
				}
				while((pent = readdir(pdir)) != NULL)
				{
					
					//文件i节点号  文件名
					printf("%5d %s\n", pent->d_ino,
						pent->d_name);
			 	}
				closedir(pdir);
				break;
			}
			case '5':
			{
				//目录定位不能任意 位置必须是目录流的返回值
				long int loc;
	//			DIR *dir;
				if ((pdir = opendir(cmd)) == NULL)
				{
					printf("failed.\n");
					break;
				}
				loc = telldir(pdir);
				seekdir(pdir, loc);  //重新访问当前目录项
				closedir(pdir);
				//rewinddir(dir); //重新开始位置
				//seekdir(dir, 0); //等价
				break;
			}
			case '0':
				return;
			default:
				break;
		}
	}	
}
