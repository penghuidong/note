#类型识别
在面向对象中可能出现下面的情况：

* 基类指针指向子类对象
* 基类引用成为子类对象的别名

#多态解决方案的缺陷
* 必须从基类开始提供类型虚函数
* 所有的派生类都必须重写类型虚函数
* 每个派生类的类型名必须唯一

#类型识别关键字
C++提供了typeid关键字用于获取类型信息

* typeid关键字返回对应参数的类型信息
* typeid返回一个type_info类对象
* 当typeid的参数为NULL时将抛出异常


typeid的使用：

    #include <iostream>
    #include <string>
    #include <typeinfo>
    using namespace std;
    
    class Base{
    public:
      virtual ~Base(){}
    };
    
    class Derived : public Base{
    public:
      void print(){
        cout << "I'am a Derived." << endl;
      }
    };
    
    void test(Base* b){
      const type_info& tb = typeid(*b);
      cout << tb.name() << endl;
    }
    
    int main(){
      int i =0;
      const type_info& tiv = typeid(i);
      const type_info& tii = typeid(int);
    
      cout << (tiv==tii) << endl;
    
      Base b;
      Derived d;
    
      test(&b);
      test(&d);
    
      return 0;
    }


#typeid的注意事项
* 当参数为类型时：返回静态类型信息
* 当参数为变量时：
  * 不存在虚函数表则返回__静态类型__信息
  * 存在虚函数表则返回__动态类型__信息，结果直到运行时才可知