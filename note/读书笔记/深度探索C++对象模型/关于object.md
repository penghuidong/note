# 关于对象

__在C++中，有两种class data members: statis和nonstatis，以及三种class member functions: statis, nonstatis和virtual。__

# C++程序设计模型直接支持三种programming paradigms(程序设计范式)：

## 1. 程序模型(procedural model)
## 2. 抽象数据类型模型(abstruct data type model,ADT)(现被称为OB:object-based)
## 3. 面向对象模型(object-oriented model)





__C++中凡处于同一个access section的数据，必定保证以其声明顺序出现在内存布局当中。__




__base classes 和 derived classes 的 data members的布局也未有谁先谁后的强制规定。__



__组合，而非继承，才是把C和C++ 结合在一起的唯一可行的方法。__

> ​	C struct在C++中的一个合理用途，是当你要传递“一个复杂的class object的全部或部分”到某个C函数去时，struct声明可以将数据封装起来，并保证拥有与C兼容的空间布局。



__原则上，被指定的object的真实类型在每一个特定执行点之前，是无法解析的。在C++中，只有通过pointer和reference的操作才能够完成。__



#### 多态

![](多态的理解.png)

> ​	多态的主要用途是经由一个共同的接口来影响类型的封装，这个接口通常被定义在一个抽象的base class中。这个共享接口是以virtual function机制引发的，它可以在执行期根据object的真正类型解析出到底是哪一个函数实例被调用。

#### class object占用内存的影响因素

* 非静态成员变量的大小
* 内存对齐
* 为了支持virtual所产生的额外内存