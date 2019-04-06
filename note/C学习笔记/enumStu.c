/*
	enum是C语言中的一种自定义类型
	enum值是可以根据需要自定义的整形值
	第一个定义的enum值默认为0
	默认情况下的enum值是在前一个定义值的基础上加1
	enum类型的变量只能取定义时的离散值
*/

/*
	enum中定义的值是C语言中真正意义上的常量
	在工程中enum多用于定义整形常量
*/
#include <stdio.h>

enum 
{
	ARRAY_SIZE = 10
};

enum Color
{
	RED = 0x00FF0000,
	GREEN = 0x0000FF00,
	BLUE = 0X000000FF
};

void printColor(enum Color c)
{
	switch(c)
	{
		case RED:   printf("Color:RED (0x%08X)\n",c); break;
		case GREEN: printf("Color:GREEN (0x%08X)\n",c); break;
		case BLUE:  printf("Color:BLUE (0x%08X)\n",c); break;
	}
}

void initArray(int array[])
{
	int i = 0;
	for(i=0; i<ARRAY_SIZE; i++)
		array[i] = i+1;
}

void printArray(int array[])
{
	int i = 0;
	for(i=0; i<ARRAY_SIZE; i++)
		printf("%d\n",array[i]);
}

int main(void)
{
	enum Color c = GREEN;
	int array[ARRAY_SIZE] = {0};
	printColor(c);
	initArray(array);
	printArray(array);
	
	return 0;
	
}