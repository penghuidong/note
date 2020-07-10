#include <malloc.h>
#include <stdio.h>
/*C语言中的struct可以看作变量的集合：
struct TS{}; 问题TS占用多大内存？ sizeof(struct TS) = 0 or编译出错
*/


/*
	结构体与柔性数组：
		柔性数组即数组大小待定的数组
		C语言中可以由结构体产生柔性数组
		C语言中结构体的最后一个元素可以是大小未知的数组
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






