#笔试题：统计对象中某个成员变量的访问次数

##mutable关键字
* mutable是为了突破const函数的限制而设计的
* mutable成员变量将永远处于可改变的状态
* mutable在实际的项目开发中被严禁滥用
##mutable的深入分析
* mutable成员变量破坏的了只读对象的内部状态
* const成员函数保证只读对象的状态不变性
* mutable成员变量的出现无法保证状态不变性

使用mutabl属性修饰访问次数统计量：

    #include <iostream>
    using namespace std;
    
    class Test{
    private:
      int m_value;
      mutable size_t m_count;
    
    public:
      Test(int value = 0) : m_value(value), m_count(0) {}
    
      int getValue() const {
        m_count++;
    	return m_value;
      }
    
      void setValue(int value){
        m_count++;
    	m_value = value;
      }
    
      int getCount() const {
        return m_count;
      }
    
      ~Test(){}
    };
    
    int main(){
      Test t;
    
      t.setValue(100);
      cout << "t.m_value = " << t.getValue() << endl;
      cout << "t.m_count = " << t.getCount() << endl;
    
      const Test ct(200);
      cout << "ct.m_value = " << ct.getValue() << endl;
      cout << "ct.m_count = " << ct.getCount() << endl;
      return 0;
    }


##更优解决方案：使用指针常量
    #include <iostream>
    using namespace std;
    
    class Test{
    private:
      int m_value;
      size_t* const m_count;
    
    public:
      Test(int value = 0) : m_value(value), m_count(new size_t(0)) {}
    
      int getValue() const {
        ++*m_count;
    	return m_value;
      }
    
      void setValue(int value){
        ++*m_count;
    	m_value = value;
      }
    
      size_t getCount() const {
        return *m_count;
      }
    
      ~Test(){
        delete m_count;
      }
    };
    
    int main(){
      Test t;
    
      t.setValue(100);
      cout << "t.m_value = " << t.getValue() << endl;
      cout << "t.m_count = " << t.getCount() << endl;
    
      const Test ct(200);
      cout << "ct.m_value = " << ct.getValue() << endl;
      cout << "ct.m_count = " << ct.getCount() << endl;
      return 0;
    }

