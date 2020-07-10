#include <malloc.h>
#include <stdio.h>
/*C�����е�struct���Կ��������ļ��ϣ�
struct TS{}; ����TSռ�ö���ڴ棿 sizeof(struct TS) = 0 or�������
*/


/*
	�ṹ�����������飺
		�������鼴�����С����������
		C�����п����ɽṹ�������������
		C�����нṹ������һ��Ԫ�ؿ����Ǵ�Сδ֪������
*/

struct SoftArray
{
	int len;
	int array[];
};

struct SoftArray* createSoftArray(size_t size)
{
	struct SoftArray* ret = NULL;
	if(size>0)
	{
		ret = (struct SoftArray*)malloc(sizeof(struct SoftArray) + sizeof(int)*5);
		ret->len = size;
	}
	return ret;
}

void deleteSoftArray(struct SoftArray* sa) {free(sa);}

void func(struct SoftArray* sa)
{
	int i=0; 
	if(NULL!=sa)
		for(i=0; i<sa->len; i++)
			sa->array[i] = i+1;
}


int main(void)
{
	struct SoftArray sarr;
	struct SoftArray* sa = createSoftArray(10);
	int i = 0;
	
	func(sa);
	
	for(i=0; i<sa->len; i++)
		printf("%d\n", sa->array[i]);
	
	printf("sizeof(struct SoftArray) = %d", sizeof(sarr));
	deleteSoftArray(sa);
	
	return 0;
}






