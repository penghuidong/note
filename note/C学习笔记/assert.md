### assert宏分析

##### assert宏用于为程序增加诊断功能

__用法：__

​			assert(表达式);

__实现：__

``` c
# define assert(expr)                   \ 
   ((expr)                               \
   ? __ASSERT_VOID_CAST (0)             \                                            
   : __assert_fail (#expr, __FILE__, __LINE__, __ASSERT_FUNCTION)) 
```

​		如果执行语句`assert(表达式)`时，表达式的值为0，`__assert_fail`会在stderr中打印“Assertion failed”和表达式等信息，并调用abort。

​		如果定义了`NDEBUG`,又包含了头文件<assert.h>,assert宏将被忽略。