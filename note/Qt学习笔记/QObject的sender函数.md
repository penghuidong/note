#QObject中的sender函数详解
函数原型

    QObject * QObject::sender () const [protected]

&emsp;&emsp;当槽函数被信号激活时，`sender()`返回一个指向发送信号的对象的指针，否则返回0。槽函数从对象的线程上下文中调用`sender()`，`sender()`返回的指针只在槽函数执行时有效。  
&emsp;&emsp;当发送信号的对象被销毁、信号与槽被`disconnect`时，`sender()`的返回值无效。