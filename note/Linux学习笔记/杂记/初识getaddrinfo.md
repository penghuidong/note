# 初识getaddrinfo

### 1. 原型与头文件

```c
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
int getaddrinfo(const char* node, 
                const char* service, 
                const struct addrinfo* hints, 
                struct addrinfo** res);
```

### 2. 功能

&emsp;&emsp;getaddrinfo处理__名字到地址__以及__服务到端口__的转换，解决了__把主机名和服务名转换成套接字地址结构__问题。

### 3.  参数与返回值

​		

