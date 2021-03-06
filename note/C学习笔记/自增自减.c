/*
	++ 和 -- 操作符对应两条汇编指令
	前置：
		变量自增/减一  ->> 取变量值
	后置：
		取变量值  ->> 变量自增/减一

	int i = 0;
	int result;
	result = (i++) + (i++) + (i++); // result == ??
	result = (++i) + (++i) + (++i); // result == ??
	
	C语言中只规定了++和--对应指令的相对执行次序
	++ 和 -- 对应的汇编指令不一定连续运行
	在混合运算中，++ 和 -- 的汇编指令可能被打断执行
	
		++ 和 -- 参与混合运算的结果是不确定的
*/

/*	编译器究竟如何解释？
	1. ++i+++i+++i
	2. a+++b
	贪心法：++,--表达式的阅读技巧
	1. 编译器处理的每个符号应该尽可能多的包含字符
	2. 编译器以从左向右的顺序一个一个尽可能多的读入字符
	3. 当读入的字符不可能和已读入的字符组成合法符号为止
	
	空格可以作为C语言中一个完整符号的休止符
	编译器读入空格后立即对之前读入的符号进行处理
*/

int main(void)
{
	int i = 0;
	int r = 0;
	
	r = (i++) + (i++) + (i++);
	printf("i = %d\n", i);
	printf("r = %d\n", r);
	r = (++i) + (++i) + (++i);
	printf("i = %d\n", i);
	printf("r = %d\n", r);
	
	return 0;
}

/*
int main()
{   
    int i = 0;
    int j = ++i+++i+++i;
    
    int a = 1;
    int b = 4;
    int c = a+++b;
    
    int* p = &a;
    
    b = b/*p;

    printf("i = %d\n", i);
    printf("j = %d\n", j);
    printf("a = %d\n", a);
    printf("b = %d\n", b);
    printf("c = %d\n", c);
      
    return 0;
}
*/



