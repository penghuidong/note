/*
	typedef用于给一个已经存在的数据类型重命名
	typedef本质上不能产生新的类型
	typedef重命名的类型：
		可以在typedef语句之后定义
		不能被unsigned和signed修饰
		
	用法： typedef type new_name;
*/

#include <stdio.h>

typedef int int32;

struct _tag_point
{
	int x;
	int y;
};

typedef struct _tag_point point;

typedef struct 
{
	int length;
	int array[];
}SoftArray;

typedef struct _tag_list_node ListNode;

struct _tag_list_node
{
	ListNode* next;
};

int main(void)
{
	int332 i = -100;
	unsigned int32 ii = 0;
	point p;
	SoftArray* sa = NULL;
	ListNode* node = NULL;
	
	return 0;
}



