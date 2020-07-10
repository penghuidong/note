#设计思路
* 在类中重载new/delete操作符
* 在new的操作符重载函数中返回指定的地址
* 在delete操作符重载中标记对应的地址可用


自定义动态对象的存储空间：

    #include <iostream>
    #include <string>
    #include <cstdlib>  
    using namespace std;
    
    class Test
    {
        static unsigned int c_count;
        static char* c_buffer;
        static char* c_map;
        
        int m_value;
    public:
        static bool SetMemorySource(char* memory, unsigned int size)
        {
            bool ret = false;
            
            c_count = size / sizeof(Test);
            
            ret = (c_count && (c_map = reinterpret_cast<char*>(calloc(c_count, sizeof(char)))));
            
            if( ret )
            {
                c_buffer = memory;
            }
            else
            {
                free(c_map);
                
                c_map = NULL;
                c_buffer = NULL;
                c_count = 0;
            }
            
            return ret;
        }
        
        void* operator new (unsigned int size)
        {
            void* ret = NULL;
            
            if( c_count > 0 )
            {
                for(int i=0; i<c_count; i++)
                {
                    if( !c_map[i] )
                    {
                        c_map[i] = 1;
                        
                        ret = c_buffer + i * sizeof(Test);
                        
                        cout << "succeed to allocate memory: " << ret << endl;
                        
                        break;
                    }
                }
            }
            else
            {
                ret = malloc(size);
            }
            
            return ret;
        }
        
        void operator delete (void* p)
        {
            if( p != NULL )
            {
                if( c_count > 0 )
                {
                    char* mem = reinterpret_cast<char*>(p);
                    int index = (mem - c_buffer) / sizeof(Test);
                    int flag = (mem - c_buffer) % sizeof(Test);
                    
                    if( (flag == 0) && (0 <= index) && (index < c_count) )
                    {
                        c_map[index] = 0;
                        
                        cout << "succeed to free memory: " << p << endl;
                    }
                }
                else
                {
                    free(p);
                }
            }
        }
    };
    
    unsigned int Test::c_count = 0;
    char* Test::c_buffer = NULL;
    char* Test::c_map = NULL;
    
    int main(int argc, char *argv[])
    {
        char buffer[12] = {0};
        
        Test::SetMemorySource(buffer, sizeof(buffer));
        
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
