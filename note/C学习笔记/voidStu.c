#include <stdio.h>
#include <stdlib.h>
/*void的意义
void修饰函数返回值和参数
	如果函数没有返回值，那么应该将其声明为void
	如果函数没有参数，应该声明其参数为void
void修饰函数返回值和参数是为了表示“无”
*/

/*
ANSI C：标准C语言的规范
sizeof(void)在ANSI C编译器中无法通过编译，但是对于支持GNU标准的gcc编译器而言是合法的。
*/
/*
void指针的意义
	C语言规定只有相同类型的指针才可以相互赋值
	void指针作为左值用于“接收”任意类型的指针
	void指针作为右值使用时需要进行强制类型转换
*/

void* myMemset(void* dist, unsigned char tofill, size_t byteAll)
{
	unsigned char* p = (unsigned char*)dist;
	int i=0;
	for(i; i<byteAll; i++)
		p[i] = tofill;
	return p;
}

int main(void)
{
	int i=0;
	int* a = malloc(sizeof(int)*5);
	double d[10];
	myMemset(d, 0, sizeof(d));
	for(i; i<5; i++)
		printf("%u\n",a[i]);
	free(a);
	return 0;
}
