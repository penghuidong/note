#Meta-Object Compiler(moc)：Qt C++扩展处理程序
##概述
&emsp;&emsp;moc工具读取C++头文件，如果moc在类声明中包含有Q_BJECT宏，它将为这个类产生一个包含元对象代码的C++源文件。除此以外，信号与槽机制、运行时类型信息、动态property系统也需要元对象代码。  
&emsp;&emsp;由moc产生的C++源文件必须与类实现一起编译、链接。  
&emsp;&emsp;如果使用qmake创建makefile，在调用moc时编译规则将被包含进makefile中，所以不必直接手工调用moc。

##用法
     class MyClass : public QObject
     {
         Q_OBJECT
         Q_PROPERTY(Priority priority READ priority WRITE setPriority)
         Q_ENUMS(Priority)
    
     public:
         enum Priority { High, Low, VeryHigh, VeryLow };
    
         MyClass(QObject *parent = 0);
         ~MyClass();
    
         void setPriority(Priority priority) { m_priority = priority; }
         Priority priority() const { return m_priority; }
    
     private:
         Priority m_priority;
     };

* Q_PROPERTY()宏声明一个对象property
* Q_ENUMS()声明一系列枚举类型

