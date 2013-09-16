/*
 * 调试库函数封装
 * meplusplus@qq.com
 */
#include "comlib.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define TRACE_FILE "./trace_file.txt"

static int vprint_log(FILE *fp, const char *format, va_list _va_list);
//格式化日志输出函数
int print_log(FILE *fp, const char *format, ...)
{
	va_list _va_list;
	va_start(_va_list, format);
	int ret = vprint_log(fp, format, _va_list);
	va_end(_va_list);
	return ret;
}

static int vprint_log(FILE *fp, const char *format, va_list _va_list)
{
	struct tm  *t;
	char buf[1024];
	int len;
	if (format == NULL || fp == NULL) 
		return -1;
	time_t tt = time(NULL);
	t = localtime(&tt);
	
	len = sprintf(buf, " %4d.%02d.%02d %02d:%02d:%02d [%d]: ",
		t->tm_year+1900, t->tm_mon+1, t->tm_mday,
		t->tm_hour, t->tm_min, t->tm_sec, getpid());
	len += vsprintf(buf+len, format, _va_list);
	len += sprintf(buf+len, "\n");
	if (fputs(buf, fp) != EOF && fflush(fp) != EOF)
		return 0;
	return -2;
}
//将日志写入TRACE_FILE文件
int print_trace_log(const char *format, ...)
{
	FILE *fp;
	va_list ap;
	int ret;
	va_start(ap, format);
	if ((fp = fopen(TRACE_FILE, "a")) != NULL)
	{
		ret = vprint_log(fp, format, ap);
		fclose(fp);
	}
	va_end(ap);
	return ret;
}

//十六进制日志输出函数
//每16字节化为一行十六进制字符串
int print_hex_log(FILE *fp, void *ptr, int size)
{
	
	if (fp == NULL || ptr == NULL)
		return -1;
	int linenum=0;
	int linesize = 0;
      	char line[16];
	int i;
	int len = 0;
	char buf[256];
	for(i=0; i<size; ++linenum)
	{	
		linesize = (size-i>16?16:(size-i)); //处理最后一行不够16
		memcpy(line, ptr+i, linesize);
		memset(buf, 0, sizeof(buf));
		i += linesize;
		len += sprintf(buf+len, "[%02d]: ", linenum);
		int n = 0;
		//以十六进制输出字节数据
		for(n = 0; n < linesize; ++n)
		{
			if (n == 8)
				len += sprintf(buf+len, " ");
			len += sprintf(buf+len, "%02X", line[n] & 0X00FF);
		}
		//最后一行补空格
		for (n = linesize; n < 16; ++n)
		{
			if (n == 8)
				len += sprintf(buf + len, " ");
			len += sprintf(buf + len, "   ");
		}
		
		len += sprintf(buf + len, " :");
	 	for (n=0; n < linesize; ++n)
		{
			if (!isprint(line[n])) line[n]='.';
			len += sprintf( buf + len, "%c", line[n]);
		}
		len += sprintf(buf+len, "\n");
		if(fputs(buf, fp) == EOF)
			return -1;
	}
	fflush(fp);
	return 0;
}
int print_trace_hex_log(void *ptr, int size)
{
	FILE *fp;
 	if ((fp = fopen(TRACE_FILE, "a")) != NULL)
		return print_hex_log(fp, ptr, size);
	return -1;
}

//验证函数  当status=0，不执行任何操作 否则向日志文件
//输出源文件名 行号 错误信息
int verify(int status, const char *buf, const char *filename, int linenum)
{
	FILE *fp;
	char fileline[128], error[128];
	if (!status)
	{
		memset(fileline, 0, sizeof(fileline));
		memset(error, 0, sizeof(error));
		if (errno != 0)
			sprintf(error, "\t> %0.64s\n", strerror(errno));
		if (filename == NULL)
			strcpy(fileline, "\t> Invalid file name");
		else
			sprintf(fileline, "\t> In line %d file %0.32s",
				linenum, filename);
		if (buf == NULL) buf = "";
		fp = fopen(TRACE_FILE, "a");
		if (fp != NULL)
		{
			print_log(fp, "%s[%d]\n%s%s", buf, getpid(), error,
				fileline);
			fclose(fp);
		}
		errno = 0;
	}
	return status;
}

