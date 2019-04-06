#markdown语法笔记

#一级标题
##二级标题
###三级标题
	>符号表示引用其他文章
>引文
>>嵌套引文

这是正文
#无序表：*、+、-标记(这是正文)
#有序表：数字+英文句点 1.

	//代码块：
	#include <stdio.h>
	int main(void)
	{
		printf("hello world\n");
	}
#分隔符
*************************************
随意使用*或者-建立分割线

#链接
markdown官网[www.markdown.cn](http://www.markdown.cn "markdown官网")
#强调
##*、_作为标记强调字词的符号
* 空格
_ 空格
*强调*

_强调_

**强调**

#标记正文中的代码
使用反引号包起要标记的一小段行内代码：

Use the `printf()` function.

``There is a literal backtick (`) here.``

#插入图片
	![图片替代文字](图片网址 "title")
![图片例子](C:\Users\皮皮东\Pictures\5895671784d24.jpg "example")