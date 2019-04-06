/*
	enum��C�����е�һ���Զ�������
	enumֵ�ǿ��Ը�����Ҫ�Զ��������ֵ
	��һ�������enumֵĬ��Ϊ0
	Ĭ������µ�enumֵ����ǰһ������ֵ�Ļ����ϼ�1
	enum���͵ı���ֻ��ȡ����ʱ����ɢֵ
*/

/*
	enum�ж����ֵ��C���������������ϵĳ���
	�ڹ�����enum�����ڶ������γ���
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