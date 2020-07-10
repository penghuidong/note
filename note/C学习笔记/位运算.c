/*
	位运算符分析：| or， &and , ~ not, ^ exclusive-or 
	左移和右移注意点：
	1. 左操作数必须为整数类型
		char 和 short 被隐式转换为int后进行移位操作
	2. 右操作数的范围必须为：[0, 31]
	3. 左移运算符 << 将运算数的二进制位左移
		规则：高位丢弃，低位补0
	4. 右移运算符 >> 把运算数的二进制位右移
		规则：高位补符号位，低位丢弃
*/

/*
防错准则：
1. 避免位运算符，逻辑运算符和数学运算符同时出现在一个表达式中
2. 当位运算符，逻辑运算符和数学运算符需要同时残余运算时尽量
	使用括号来表达计算次序
*/

/*
小技巧：
1. 左移n位相当于乘以2的n次方，但效率比数学运算符高
2. 右移n位相当于除以2的n次方，当效率比数学运算符高
*/


/*不使用中间变量交换两值   若a和b过大，可能导致变量溢出*/
#define swap1(a,b) \
{                 \
	a = a + b;    \
	b = a - b;    \
	a = a - b;    \
}

/*使用异或位运算交换两值 b = a ^ b ^b = a; */ 
#define swap2(a,b) \
{                  \
	a = a ^ b;     \
	b = a ^ b;     \
	a = a ^ b;     \
}

/*
	位运算的效率高于四则运算和逻辑运算
	运算优先级： 四则运算 > 位运算 > 逻辑运算
*/


