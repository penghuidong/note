
/*
	sizeof 是编译器的内置指示符
	sizeof用于计算类型或变量所占的内存大小
	sizeof的值在编译期就已经确定
*/

/*
	sizeof是C语言中内存的关键字而不是函数
		在编译过程中所有的sizeof将被具体的数值所替换
		程序的执行过程与sizeof没有任何关系
*/


/*
	下面的程序输出什么？
	int var = 0;
	int size = sizeof(var++);
	printf("var = %d, size = %d\n", var, size);
*/

#include <stdio.h>

int f(void)
{
	printf("test\n");
	return 0;
}
//sizeof 作用于数组首地址除以单个元素大小可以算整个数组大小
int main(void)
{
	int var = 0;
	int size = sizeof(f());
	int a[5] = {0};
	printf("size = %d\n", size);
	printf("use sizeof calculate array size = %d", sizeof(a)/sizeof(a[0]));
	return 0;
}

