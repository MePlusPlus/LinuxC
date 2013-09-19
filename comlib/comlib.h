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
#include <assert.h>
//格式化日志输出函数
int print_log(FILE *fp,const char *format, ...);
int print_trace_log(const char *format, ...);

//十六进制格式化日志输出
int print_hex_log(FILE *fp,void *data, int size);
int print_trace_hex_log(void *data, int size);
//验证函数  当status=0，不执行任何操作 否则向日志文件
//输出源文件名 行号 错误信息
int verify(int status, const char *buf, const char *filename, int linenum);

/*-------  文件阻塞读写函数库 保证读写确定字符数的函数 -------*/

//读取*size个数据 或者遇到结束错误  size返回实际的字符数
//读取函数容易出现错误或者不足值，必须处理
int read_file(int fd, void *ptr, int *size);

//写入size个字符
int write_file(int fd, void *ptr, int size);

/*------- 守护进程生成器，将普通进程转为守护进程 -------*/

//处理SIGCLD信号 预防僵死进程
void clear_child(int sig);

//将普通进程转为守护进程
//后台进程特点：后台运行，独立域控制终端，清除文件掩码，处理信号
int init_server();


#endif
