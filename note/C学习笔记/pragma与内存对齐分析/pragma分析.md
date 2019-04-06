#pragma简介
* #pragma用于指示编译器完成一些特定的动作
* #pragma所定义的很多指示字是编译器特有的
* \#pragma在不同的编译器间是不可移植的
	* 预处理器将忽略它不认识的#pragma指令
	* 不同的编译器可能以不同的方式解释同一条#pragma指令

一般用法：#pragma parameter

__&emsp;&emsp;不同的paremeter参数语法和意义各不相同。__

#\#pragma message

* message参数在大多数的编译器中都有相似的实现
* message参数在编译时输出消息到编译输出窗口中
* message用于条件编译中可提示代码的版本信息

__&emsp;&emsp;与#error和#warning不同，#pragma message仅仅代表一条编译消息，不代表程序错误。__

编译提示：

	#include <stdio.h>
	#if defined(ANDROID20)
    	#pragma message("Compile Android SDK 2.0...")
    	#define VERSION "Android 2.0"
	#elif defined(ANDROID23)
    	#pragma message("Compile Android SDK 2.3...")
    	#define VERSION "Android 2.3"
	#elif defined(ANDROID40)
    	#pragma message("Compile Android SDK 4.0...")
    	#define VERSION "Android 4.0"
	#else
    	#error Compile Version is not provided!
	#endif

	int main()
	{
   		printf("%s\n", VERSION);
    	return 0;
	}

#\#pragma once
* #pragma once用于保证头文件只被编译一次
* #pragma once是编译器相关的，不一定被支持

\#pragma once与头文件宏有什么区别？  
&emsp;&emsp;#pragme once平台独立，不便于移植但性能较高，而头文件宏能在不同编译器下编译，但性能较#pragme once弱。

示例代码：

	//global.h
	#pragma once
	int g_value = 1;

	//main.c
	#include <stdio.h>
	#include "global.h"
	#include "global.h"

	int main()
	{
    	printf("g_value = %d\n", g_value);
    	return 0;
	}

\#pragma pack
##内存对齐
* 不同类型的数据在内存中按照一定的规则排列。
* 而不一定是顺序的一个接一个地排列  

输出是什么？

	#include <stdio.h>
	struct Test1
	{
    	char  c1;
    	short s;
    	char  c2;
    	int   i; 
	};
	struct Test2
	{
    	char  c1;
    	char  c2;
    	short s;
    	int   i;
	};
	int main()
	{
    	printf("sizeof(Test1) = %d\n", sizeof(struct Test1));
    	printf("sizeof(Test2) = %d\n", sizeof(struct Test2));
    	return 0;
	}	
###\#pragma pack能够改变编译器的默认对齐方式

	//强制使用4字节内存对齐：
	#pragma pack(4)
	struct Test2
	{
    	char  c1;
    	char  c2;
    	short s;
    	int   i;
	};
	#pragma pack()
###struct占用的内存大小
* 对于结构的各个成员，第一个成员位于偏移为0的位置，以后每个数据成员的偏移量必须是min(#pragma pack()指定的数，这个数据成员的自身长度) 的倍数。
* 在数据成员完成各自对齐之后，结构(或联合)本身也要进行对齐，对齐将按照#pragma pack指定的数值和结构(或联合)最大数据成员长度中，比较小的那个进行。

2、  在数据成员完成各自对齐之后，结构(或联合)本身也要进行对齐，对齐将按照#pragma pack指定的数值和结构(或联合)最大数据成员长度中，比较小的那个进行。

&emsp;&emsp;__编译器在默认情况下按照4字节对齐。__

##为什么需要内存对齐
* CPU对内存的读取不是连续的，而是分成块读取的，块的大小只能是1、2、4、8、16...字节
* 当读取操作的数据未对齐，则需要两次总线周期来访问内存，因此性能会大打折扣
* 某些硬件平台只能从规定的相对地址处读取特定类型的数据，否则产生硬件异常

下列代码输出什么？：

代码1：

	#include <stdio.h>
	#pragma pack(2)
	struct Test1
	{
		char c1;
		short s;
		char c2;
		int i;
	};
	#pragma pack()
	#pragma pack(4)
	struct Test2
	{
		char cl;
		char c2;
		short s;
		int i;
	};
	#pragma pack()
	int main()
	{
		printf("sizeof(Test1) = %d\n", sizeof(struct Test1));
		printf("sizeof(Test2) = %d\n", sizeof(struct Test2));
		return 0;
	}

代码2：

	#include <stdio.h>
	#pragma pack(8)
	struct S1
	{
		short a;
		long b;
	};
	struct S2
	{
		char c;
		struct S1 d;
		double e;
	};
	#pragma pack()
	int main()
	{
		printf("sizeof(S1) = %d\n", sizeof(struct S1));
		printf("sizeof(S2) = %d\n", sizeof(struct S2));
		return 0;
	}

