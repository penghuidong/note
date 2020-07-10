# strtol & strtoll

### 功能

* 将一个C字符串转换成一个`长整形(long int、long long int)`

### 原型

```c
long int strtol(const char *nptr, char **endptr, int base);
```

* strtol会将nptr指向的字符串，根据base，按权转化为long int, 并返回
* strtol当检测到第一个非法字符时， 立即停止检测， 其后的所有字符都会被当做非法字符处理
* 从第一个非法字符开始的非法字符串的，被赋给`*endptr`, 这里注意`endptr`是双重指针
* nptr字符串中前后的空格会被忽视，但是nptr中间有空格则会视为非法字符

##### 非法字符演示

```c
#include <stdlib.h>
#include <stdio.h>

int main()
{
    char* strString = "0x78910h11111";
    char* strEndStr;
    long int li = strtol(strString, &strEndStr, 16);

    printf("strString = %s\nstrEndStr = %s\n", strString, strEndStr);
    printf("li = 0x%X\n", li);                                                          
    return 0;
}
```

