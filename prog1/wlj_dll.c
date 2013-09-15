/*
 * 动态连接库的使用
 * 打开dlopen 获取对象地址dlsym  执行动态对象 关闭dlclose
 * meplusplus@qq.com
 */
#include <dlfcn.h>
#include <stdio.h>
int main(int args,char *argv[])
{
	void *pHandle;
	void (*pFunc)();	//指向函数的指针
	int *p;
	pHandle = dlopen("./dll.so", RTLD_NOW);	//打开动态库
	if (!pHandle)
	{
		printf("Cann't find dll.so\n");
		return ;
	}

	//获取库函数地址
	//返回一个没有参数和返回值的函数指针
	pFunc = (void (*)())dlsym(pHandle, "print");
	if (pFunc)
		pFunc();
	else
		printf("Cann't find func print\n");
	
	//获取库变量的地址
	p = (int *)dlsym(pHandle, "p");
	if (p)
		printf("p=%d\n", *p);
	else
		printf("Cann't find int p\n");
	
	dlclose(pHandle);
}
