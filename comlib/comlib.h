/*
 * 通用函数库头文件
 * 主要是常用库函数封装
 */

/* -------  调试库 --------*/
#ifndef _COMLIB_H
#define _COMLIB_H

//必须要包含所用到的头文件
#include <stdio.h>
#include <error.h>
//格式化日志输出函数
int print_log(FILE *fp,const char *format, ...);
int print_trace_log(const char *format, ...);

//十六进制格式化日志输出
int print_hex_log(FILE *fp,void *data, int size);
int print_trace_hex_log(void *data, int size);
//验证函数  当status=0，不执行任何操作 否则向日志文件
//输出源文件名 行号 错误信息
int verify(int status, const char *buf, const char *filename, int linenum);



#endif
