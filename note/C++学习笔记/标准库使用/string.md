#历史遗留问题
* C语言不支持真正意义上的字符串
* C语言用字符数组和一组函数实现字符串操作
* C语言不支持自定义类型，因此无法获得字符串类型

#字符串与数字的转换
* 标准库中提供了相关的类对字符串和数字进行转换
* 字符串流类用于string的转换
  * <sstream>-相关头文件
  * istringstream-字符串输入流
  * ostringstream-字符串输出流

##string向数字转换
    int        stoi( const std::string& str, std::size_t* pos = 0, int base = 10 );
    int        stoi( const std::wstring& str, std::size_t* pos = 0, int base = 10 );

    long       stol( const std::string& str, std::size_t* pos = 0, int base = 10 );
    long       stol( const std::wstring& str, std::size_t* pos = 0, int base = 10 );
    long long stoll( const std::string& str, std::size_t* pos = 0, int base = 10 );
    long long stoll( const std::wstring& str, std::size_t* pos = 0, int base = 10 );

    unsigned long      stoul( const std::string& str, std::size_t* pos = 0, int base = 10 );
    unsigned long      stoul( const std::wstring& str, std::size_t* pos = 0, int base = 10 );
    unsigned long long stoull( const std::string& str, std::size_t* pos = 0, int base = 10 );
    unsigned long long stoull( const std::wstring& str, std::size_t* pos = 0, int base = 10 );
* 它们会跳过前导的任何空白字符
* 它们允许返回“被处理之最末字符”后的第一个字符的索引
* 如果转换无法发生，它们会抛出std::invalid_argument
* 如果被转换值超出返回类型的可表达范围，抛出std::out_of_range

实例代码

    #include <string>
    #include <iostream>
    #include <limits>
    #include <exception>
    
    using std::cout;
    using std::endl;
    using std::string;
    
    int main()
    {
      try{
        cout << std::stoi("  77") << endl;
    	cout << std::stod("  77.7") << endl;
    	cout << std::stoi("-0x77") << endl;  //遇到x终止
    
    	size_t idx;
    	cout << std::stoi(" 42 is the truth", &idx) << endl;
    	cout << " idx of first unprocessed char: " << idx << endl;
    
    	cout << std::stoi(" 42", nullptr, 16) << endl;
    	cout << std::stol("789", &idx, 8) << endl; // 8在8进制中不是有效数字
    	cout << " idx of first unprocessed char: " << idx << endl;
    
    	long long ll = std::numeric_limits<long long>::max();
    	string s = std::to_string(ll);
    	cout << s << endl;
    
    	cout << stoi(s) << endl;
      } catch(const std::exception& e) {
    	cout << e.what() << endl;
      }
      return 0;
    }

#使用基于对象的思想而不是程序模型式思想
##问题1：下面代码输出什么？

    #include <iostream>
    #include <string>
    using namespace std;
    int main(){
      string s = "12345";
      const char*p = s.c_str();
      cout << p << endl;
      s.append("abcde");
      cout << p << endl;
    }
__string对象内部维护了一个指向数据的char*指针，这个指针可能在程序运行的过程中发生改变。__

##问题2：下面的代码输出什么？
    #include <iostream>
    #include <string>
    usnig namespace std;
    int main(){
      const char* p = "12345";
      string s = "";
      s.reserve(10);
      for(int i=0; i<5; i++){
        s[i] = p[i];
      }
      cout << s << endl;
    }
__对象内部表示长度的成员变量并没有被改变。__