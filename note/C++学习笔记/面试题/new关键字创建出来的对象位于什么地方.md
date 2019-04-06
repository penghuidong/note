#被忽略的事实
* new/delete的本质是C++预定义的操作符
* C++对这两个操作符做了严格的行为定义
* 在C++中能够重载new/delete操作符
  * 全局重载(不推荐)
  * 局部重载(针对具体类进行重载)
* 重载new/delete的意义在于改变动态对象创建时的内存分配方式
##new
1. 获取足够大的内存空间(默认为堆空间)
2. 在获取的空间中调用构造函数创建对象
##delete
1. 调用析构函数销毁对象
2. 归还对象所占用的空间(默认为堆空间)


#在静态存储区中创建动态对象
    
    #include <iostream>
    #include <string>
    
    using namespace std;
    
    class Test
    {
        static const unsigned int COUNT = 4;
        static char c_buffer[];
        static char c_map[];
        
        int m_value;
    public:
        void* operator new (unsigned int size)
        {
            void* ret = NULL;
            
            for(int i=0; i<COUNT; i++)
            {
                if( !c_map[i] )
                {
                    c_map[i] = 1;
                    
                    ret = c_buffer + i * sizeof(Test);
                    
                    cout << "succeed to allocate memory: " << ret << endl;
                    
                    break;
                }
            }
            
            return ret;
        }
        
        void operator delete (void* p)
        {
            if( p != NULL )
            {
                char* mem = reinterpret_cast<char*>(p);
                int index = (mem - c_buffer) / sizeof(Test);
                int flag = (mem - c_buffer) % sizeof(Test);
                
                if( (flag == 0) && (0 <= index) && (index < COUNT) )
                {
                    c_map[index] = 0;
                    
                    cout << "succeed to free memory: " << p << endl;
                }
            }
        }
    };
    
    char Test::c_buffer[sizeof(Test) * Test::COUNT] = {0};
    char Test::c_map[Test::COUNT] = {0};
    
    int main(int argc, char *argv[])
    {
        cout << "===== Test Single Object =====" << endl;
         
        Test* pt = new Test;
        
        delete pt;
        
        cout << "===== Test Object Array =====" << endl;
        
        Test* pa[5] = {0};
        
        for(int i=0; i<5; i++)
        {
            pa[i] = new Test;
            
            cout << "pa[" << i << "] = " << pa[i] << endl;
        }
        
        for(int i=0; i<5; i++)
        {
            cout << "delete " << pa[i] << endl;
            
            delete pa[i];
        }
        
        return 0;
    }
