/*
 * 多进程web服务器，执行cgi程序
 * 支持get方式请求，跳过所有参数
 * version 1.0
 * meplusplus@qq.com
 *  
 * 使用:webserv portnum
 * gcc wlj_webserv_cgi.c wlj_socklib.c -o webserv
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
//跳过请求参数
void read_til_crnl(FILE *fp);

//响应不支持的请求方式
void cannot_do(int fd);

//判断是否存在该文件或目录 .cgi文件，普通文件，目录文件
int not_exist(char *arg);

//当文件不存在时，响应
void do_404(char *arg, int fd);

//判断是否是目录文件
int isadir(char *f);

//运行ls命名显示目录内容
void do_ls(char *dir, int fd);

//判断是否是.cgi文件请求
int ends_in_cgi(char *arg);

//运行.cgi请求
void do_exec(char *f, int fd);

//显示普通文件内容
void do_cat(char *f, int fd);

//处理客户端请求
void process_rq(char *reques, int fd);
void main(int argc, char *argv[])
{
	int sock,fd;
	FILE *fpin;
	char request[BUFSIZ];
	
	//验证运行参数
	if (argc == 1)
	{
		fprintf(stderr, "usage:webserv portnum\n");
		exit(1);
	}
	
	int port = atoi(argv[1]);
	if (port<0 || port>0x0FFFFL)
	{
		fprintf(stderr, "portnum must be 0-65535\n");
		exit(1);
	}
	
	sock = make_server_socket(port);
	if (sock == -1)
		exit(2);
	
	while(1)
	{
		fd = accept(sock, NULL, NULL);
		if (fd == -1)
			continue;
		fpin = fdopen(fd, "r");
		
		fgets(request, BUFSIZ, fpin);
		printf("Got a call:request = %s\n",request);
		
		//跳过请求以后的所有参数，直到\r\n\r\n位置
		read_til_crnl(fpin);
		process_rq(request, fd);
		fclose(fpin);
	}

}

//每一行是以\r\n结尾
//最后以空行 \r\n结束请求
void read_til_crnl(FILE *fp)
{
	char buf[BUFSIZ];
	while(fgets(buf, BUFSIZ, fp) != NULL && strcmp(buf, "\r\n") != 0);
}

void process_rq(char *rq, int fd)
{
	char cmd[BUFSIZ], arg[BUFSIZ];
	if (fork() != 0)  //父进程返回
		return;
	//子进程处理  "./"也行 //表示/
	strcpy(arg, ".");
	if (sscanf(rq, "%s%s", cmd, arg+2) != 2)
		return ;
	

	if (strcmp(cmd, "GET") != 0)   //仅支持get方式
		cannot_do(fd);
	else if (not_exist(arg))   	//运行的程序是否存在
		do_404(arg, fd);
	else if (isadir(arg))  		//是否是个目录
		do_ls(arg, fd);
	else if (ends_in_cgi(arg))	//是否是cgi文件的程序
		do_exec(arg,fd);
	else  				//cat命令显示文件内容
		do_cat(arg, fd);
	
}

//输入应答头
void header(FILE *fp, char *content_type)
{
	fprintf(fp, "HTTP/1.0 200 OK\r\n");
	if (content_type)
		fprintf(fp, "Content-Type:%s\r\n", content_type);
}

void cannot_do(int fd)
{
	FILE *fp = fdopen(fd, "w");
	fprintf(fp, "HTTP/1.0 501 Not Implemented\r\n");
	fprintf(fp, "Content-Type:text/plain\r\n");
	fprintf(fp, "\r\n");
	
	fprintf(fp, "That command is not yet implemented\r\n");
	fclose(fp);
}

void do_404(char *item, int fd)
{
	FILE *fp = fdopen(fd, "w");
	fprintf(fp, "HTTP/1.0 404 Not Found\r\n");
	fprintf(fp, "Content-Type:text/plain\r\n");
	fprintf(fp, "\r\n");
	
	fprintf(fp, "The item you requested:%s\r\n is not found\r\n", item);
	fclose(fp);
}

int isadir(char *f)
{
	struct stat info;
	return (stat(f, &info) != -1 && S_ISDIR(info.st_mode));
}

int  not_exist(char *f)
{
	struct stat info;
	return (stat(f, &info) == -1);
}

void do_ls(char *dir, int fd)
{
	FILE *fp;
	fp = fdopen(fd, "w");
	header(fp, "text/plain");
	fprintf(fp, "\r\n");
	fflush(fp);
	
	dup2(fd,1);
	dup2(fd,2);
	close(fd);
	
	execlp("ls","-l", dir, NULL);
	perror(dir);
	exit(1);
}


char *file_type(char *f)
{
	char *cp;
	if ((cp = strrchr(f,'.')) != NULL)
		return cp+1;
	return "";
}

//判断是否是cgi文件类型
int ends_in_cgi(char *f)
{
	return (strcmp(file_type(f), "cgi") == 0);
}

void do_exec(char *prog, int fd)
{
	FILE *fp;
	fp = fdopen(fd, "w");
	header(fp, NULL);
	fflush(fp);
	dup2(fd,1);
	dup2(fd,2);
	close(fd);
	execl(prog,NULL);
	perror(prog);
}

void do_cat(char *f, int fd)
{
	char *extension = file_type(f);
	char *content = "text/plain";
	FILE *fpsock, *fpfile;
	int c;
	
	if (strcmp(extension, "html") == 0)
		content = "text/html";
	else if (strcmp(extension, "gif") == 0)
		content = "image/gif";
	else if(strcmp(extension, "jpg") == 0 || strcmp(extension, "jpeg"))
		content = "image/jpeg";
	
	fpsock = fdopen(fd, "w");
	fpfile = fopen(f, "r");
	
	if (fpsock != NULL && fpfile != NULL)
	{
		header(fpsock, content);
		fprintf(fpsock, "\r\n");
		while((c = getc(fpfile)) != EOF)
			putc(c, fpsock);
		fclose(fpfile);
		fclose(fpsock);
	}
	exit(0);
}

