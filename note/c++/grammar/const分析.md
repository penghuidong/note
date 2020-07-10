# C语言中的const
* const修饰的变量是只读的，本质还是变量
* const修饰的局部变量在栈上分配空间
* const修饰的全局变量在.ro data只读数据区分配空间
* const只在编译期有效，在运行期无用

&emsp;&emsp;__const修饰的变量不是真的变量，它只是告诉编译器该变量不能出现在赋值符号的左边。__

# C++中的const
C++在C的基础上对const进行了进化处理：

* 当碰见const声明时在符号表中放入常量
* 编译过程中若发现使用常量则直接以符号表中的值替换
* 编译过程中若发现下述情况则给对应的常量分配存储空间
	* 对const常量使用了extern
	* 对const常量使用&操作符

__注意：C++编译器虽然可能为const常量分配空间，但不会使用其存储空间中的值。__

	#include <iostream>
	int main()
	{
		const int c = 0;
		int* p = &c;
		cout << "c = " << c << endl;
		cout << "*p = " << *p << endl;
		cout << "c = " << c << endl;
		cout << "*p = " << *p << endl;
		return 0;
	}


# const与宏

* C++中的const常量类似于宏定义
	* const int c= 5; ≈ #define c 5
* C++中const常量与宏定义的不同
	* const常量是由编译器处理
	* 编译器对const常量进行类型检查和作用域检查
	* 宏定义由预处理器处理，单纯的文本替换
	
实例： 

	#include <iostream>
	void f()
	{
		#define a 3
		const int b = 4;
	}
	viod g()
	{
		cout << "a = " << a << endl;
		//cout << "b = " << b << endl;
	}
	int main()
	{
		const int A = 1;
		const int B = 2;
		int array[A+B] = {0};
		for(int i =0; i<(A+B); i++)
			cout << "array[ " << i << "]" << array[i] << endl;
		f();
		g();
		return 0;
	}

# const常量的判别准则
* 只有用字面量初始化的const常量才会进入符号表
* 使用其他变量初始化的const常量仍然时只读变量
* 被volatile修饰的const变量不会进入符号表
* const引用的类型与初始化变量的类型
	* 相同：初始化变量成为只读变量
	* 不同：生成一个新的只读变量

&emsp;&emsp;__在编译期间不能直接确定初始值的const标识符，都被作为只读变量处理。__

	#include <iostream>
	using std::cout;
	using std::endl;
	int main()
	{
		const int x = 1;  					//进入符号表
		const int& rx = x;					//在栈中分配内存，只读变量
		int& nrx = const_cast<int&>(rx);
		nrx = 5;
		cout << "x = " << x << endl;
		cout << "rx = " << rx << endl;
		cout << "nrx = " << nrx << endl;
		cout << "&x = " << &x << endl;
		cout << "&rx = " << &rx << endl;
		cout << "&nrx = " << &nrx << endl;

		volatile const int y = 2;			//只读变量
		int* p = const_cast<int*>(&y);
		*p = 6;
		cout << "y = " << y << endl;
		cout << "p = " << p << endl;
		
		const int z = y;
		p = const_cast<int*>(&z);
		cout << "z = " << z << endl;
		cout << "p = " << p << endl;
		
		char c = 'c';
		char& rc = c;
		const int& crc = c; 				//新的只读变量
		cout << "c = " << c << endl;
		cout << "rc = " << rc << endl;
		cout << "crc = " << crc << endl;

		return 0;
	}

# 关于const对象的疑问
* const关键字能够修饰对象
* const修饰的对象为只读对象
* 只读对象的成员变量不允许被改变
* 只读对象是编译阶段的概念，运行时无效

# C++中的const成员函数
* const对象只能调用const的成员函数
* const成员函数中只能调用const成员变量
* const成员函数中不能直接改写成员变量的值

示例代码：

	#include <stdio.h>
	
	class Test
	{
	    int mi;
	public:
	    Test(int i);
	    Test(const Test& t);
	    int getMi();
	};
	
	Test::Test(int i) { mi = i;}
	
	Test::Test(const Test& t) {}
	    
	int Test::getMi() { return mi;}
	
	int main()
	{
	    Test t(1);	    
	    return 0;
	}
