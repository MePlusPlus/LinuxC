/*
 * 使用comlib的调试库
 * meplusplus@qq.com
 */
#include <comlib.h>
#include <stdio.h>
void main()
{
	int i = 10000;
	print_log(stderr, "This is test[%d]", i);
	print_trace_log("This is test[%d]", i);
	print_hex_log(stderr, &i, sizeof(i));
	print_trace_hex_log(&i, sizeof(int));
	print_trace_log("---------------");
	verify(0, NULL, __FILE__, __LINE__);
	print_trace_log("---------------");
	verify(1, NULL, __FILE__, __LINE__);
}
