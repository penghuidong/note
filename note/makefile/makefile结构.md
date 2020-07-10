# makefile的结构

## 1. makefile的意义

* makefile用于定义源文件间的依赖关系
* makefile说明如何编译各个源文件并生成可执行文件



## 2. makefile中的元素含义

### 2.1 targets

* 通常是需要生成的目标文件名
* make所需要执行的命令名称
* targets可以包含多个目标，使用空格对多个目标名进行分隔

### 2.2 prerequisities

* 当前目标所依赖的其他目标或文件

### 2.3 command

* 完成目标所需要执行的命令

### 2.4 规则中的注意事项

* tab键
  * 每一个命令行必须以`\t`字符开始
  * `\t`字符告诉make此行是一个命令行
* 续行符: `\`
  * 可以将内容分开写到下一行，提高可读性



## 3. 依赖规则

* 当目标对应的文件不存在，执行对应命令
* 当依赖在时间上比目标更新，执行对应命令
* 当依赖关系连续发生时，对比依赖链上的每一个目标



__makefile中可以在命令前加上`@`符，作用为命令`无回显`。__



### 4. 案例

```makefile
hello.out :main.o func.o

	gcc -o hello.out main.o func.o

main.o : main.c

	gcc -o main.o -c main.c

func.o : func.c

	gcc -o func.o -c func.c	
```





#### 小技巧



