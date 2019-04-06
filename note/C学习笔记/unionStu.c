#include <stdio.h>

/*
	C语言中的union在语法上与struct相似
	union只分配最大成员的空间，所有成员共享这个空间
*/

/*
	小端模式：低字节数据在低地址内存上
	大端模式：低字节数据在高地址内存上
*/

void systemEndian(void)
{
	union SE
	{
		int i;
		char c;
	};
	union SE se;
	se.i = 1;
	if(se.c)
		printf("little endian\n");
	else 
		printf("big endian\n");
}

int main(void)
{
	systemEndian();
	
	return 0;
}