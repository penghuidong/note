#C++和C相互调用
* 实际工程中C++和C代码相互调用是不可避免的
* C++编译器能够兼容C语言的编译方式
* C++编译器会优先使用C++的编译方式
* extern关键字能强制让C++编译器进行C方式的编译

使用C方式编译：

	extern "C"
	{
		// c-style code 
	}


##使用宏以统一C方式进行编译
* __cplusplus是C++编译器内置的标准宏定义
* __cplusplus的意义
	* 确保C代码以统一的C方式被编译成目标文件  

示例代码：

	// add.h
	int add(int a, int b);

	// add.c
	#include "add.h"
	int add(int a, int b){return a + b;}

	// main.cpp
	#include <iostream>
	#ifdef __cplusplus
	extern "C"{
	#endif
	#include "add.h"
	#ifdef __cplusplus
	}
	#endif

	int main()
	{
		std::cout << " add(1,2) = " << add(1,2) << std::endl;
		return 0;
	}
