
/*
	sizeof �Ǳ�����������ָʾ��
	sizeof���ڼ������ͻ������ռ���ڴ��С
	sizeof��ֵ�ڱ����ھ��Ѿ�ȷ��
*/

/*
	sizeof��C�������ڴ�Ĺؼ��ֶ����Ǻ���
		�ڱ�����������е�sizeof�����������ֵ���滻
		�����ִ�й�����sizeofû���κι�ϵ
*/


/*
	����ĳ������ʲô��
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
//sizeof �����������׵�ַ���Ե���Ԫ�ش�С���������������С
int main(void)
{
	int var = 0;
	int size = sizeof(f());
	int a[5] = {0};
	printf("size = %d\n", size);
	printf("use sizeof calculate array size = %d", sizeof(a)/sizeof(a[0]));
	return 0;
}

