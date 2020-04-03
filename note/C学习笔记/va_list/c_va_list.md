# C 可变参数

### 参数列表的构成

* 固定参数
* 可选参数  `...`

### 实现原理

```c
typedef char * va_list;

#define _INTSIZEOF(n)       ( (sizeof(n)+sizeof(int)-1) & ~(sizeof(int)-1) )

#define va_start(ap,v)        ( ap = (va_list)&v + _INTSIZEOF(v) )

#define va_arg(ap, type)    ( *(type *)((ap += _INTSIZEOF(type)) - _INTSIZEOF(type)) )

#define va_end(ap)             ( ap = (va_list)0 )
```



