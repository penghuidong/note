# 关于对象

__在C++中，有两种class data members: statis和nonstatis，以及三种class member functions: statis, nonstatis和virtual。__

# C++程序设计模型直接支持三种programming paradigms(程序设计范式)：

## 1. 程序模型(procedural model)
## 2. 抽象数据类型模型(abstruct data type model,ADT)(现被称为OB:object-based)
## 3. 面向对象模型(object-oriented model)





__C++中凡处于同一个access section的数据，必定保证以其声明顺序出现在内存布局当中。__




__base classes 和 derived classes 的 data members的布局也未有谁先谁后的强制规定。__



__组合，而非继承，才是把C和C++ 结合在一起的唯一可行的方法。__



__原则上，被指定的object的真实类型在每一个特定执行点之前，是无法解析的。在C++中，只有通过pointer和reference的操作才能够完成。__