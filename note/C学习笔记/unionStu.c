#include <stdio.h>

/*
	C�����е�union���﷨����struct����
	unionֻ��������Ա�Ŀռ䣬���г�Ա��������ռ�
*/

/*
	С��ģʽ�����ֽ������ڵ͵�ַ�ڴ���
	���ģʽ�����ֽ������ڸߵ�ַ�ڴ���
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