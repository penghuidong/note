#include <stdio.h>
#include <stdlib.h>
/*void������
void���κ�������ֵ�Ͳ���
	�������û�з���ֵ����ôӦ�ý�������Ϊvoid
	�������û�в�����Ӧ�����������Ϊvoid
void���κ�������ֵ�Ͳ�����Ϊ�˱�ʾ���ޡ�
*/

/*
ANSI C����׼C���ԵĹ淶
sizeof(void)��ANSI C���������޷�ͨ�����룬���Ƕ���֧��GNU��׼��gcc�����������ǺϷ��ġ�
*/
/*
voidָ�������
	C���Թ涨ֻ����ͬ���͵�ָ��ſ����໥��ֵ
	voidָ����Ϊ��ֵ���ڡ����ա��������͵�ָ��
	voidָ����Ϊ��ֵʹ��ʱ��Ҫ����ǿ������ת��
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
