# main函数的本质
* main函数是操作系统调用的函数
* 操作系统总是将main函数作为应用程序的开始
* 操作系统将main函数的返回值作为程序的退出状态

思考：
__为什么C编译器支持那么多不同的main函数原型？__

	int main()
	{
	}

	main()
	{
	}

	void main()
	{
	}

	int main()
	{
		return 0;
	}

#main函数一定是第一个执行的函数吗？

GNU C：


	#include <stdio.h>	
	#ifndef __GNUC__
	#define __attribute__(x) 
	#endif	
	__attribute__((constructor))
	void before_main()
	{
	    printf("%s\n",__FUNCTION__);
	}
	
	__attribute__((destructor)) 
	void after_main()
	{
	    printf("%s\n",__FUNCTION__);
	}
	
	int main()
	{
	    printf("%s\n",__FUNCTION__);	    
	    return 0;
	}

   

