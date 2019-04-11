### hash知识点
* ANSI:American National Standards Institute 美国国家标准组织，ISO中代表美国的成员
* IEEE:The Institute of Electrical and Electronics Engineers 国际电气与电子工程师学会
* ISO:International Organization for Standardization 国际标准化组织
* IEC:International Electro technical Commission 国际电子技术委员会
* OSF:Open System Software Foundation 开放系统软件基金会
* Open Group是X/Open和OSF合并构成的


### ISO C语言
* C语言的ANSI标准于1990年被ISO采纳
* ISO C标准现由ISO/IEC维护和开发
* ISO C标准的意图是提供C语言的可移植性，使其能适合不同的的操作系统

### IEEE POSIX
* POSIX: Portable Operating System Interface，可移植操作系统接口
* POSIX: 最初是由IEEE制定的标准族，后来扩展成包括1003标记的标准和标准草案
* 1003.1标准说明的是接口而不是实现，标准中所有的例程称为函数
* 1003.1标准1988版交由ISO修订出IEEE 1003.1990标准，称为POSIX.1
* POSIX.1标准现由开放工作组维护

### 单一UNIX规范 SUS
* SUS第一版由X/Open发布
* Single UNIX Specification,是POSIX.1标准的一个超集
* 定义了附加接口，扩展了POSIX.1规范提供的功能
* POSIX.1相当于SUS的基本规范部分
* Open Group发布了第二版，第三版，第四版，称第四版为SUSv4

### UNIX系统
* POSIX.1的X/Open系统接口(X/Open System Interface,XSI)描述了可选的接口，也定义了遵循XSI的实现必须支持POSIX.1的那些可选部分
    * 文件同步
    * 线程栈地址和长度属性
    * 线程进程共享同步
    * \_XOPEN_UNIX符号常量
* 只有遵循XSI的实现才能称为UNIX系统


## UNIX系统实现
* 以上标准只是接口规范
* 标准由厂商采用，转变成具体实现
* UNIX的各种版本和变体起源于运行于PDP－11上的UNIX分时系统v6和v7
* v6和v7是在贝尔实验室以外首先得到广泛应用的UNIX系统
* v6和v7演化出三个分支
    * AT&T: 引出系统III和系统V
    * 加州大学伯克利分校： 4.x BSD
    * AT&T贝尔实验室计算科学研究中心，终止于UNIX第10版
    * 
 