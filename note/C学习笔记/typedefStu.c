/*
	typedef���ڸ�һ���Ѿ����ڵ���������������
	typedef�����ϲ��ܲ����µ�����
	typedef�����������ͣ�
		������typedef���֮����
		���ܱ�unsigned��signed����
		
	�÷��� typedef type new_name;
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



