## 1. protocol buffer是什么
* 一个跨语言，跨平台以及支持可扩展的序列化结构数据的格式  
* 简单来说，是一种google定义的结构化数据格式
* 用于数据的序列化与反序列化
* 直接对二进制源数据进行操作，相对XML小，快，简单
* 适合数据存储，网络间的数据传输

## 2. 安装Google protocol buffer
1. 官网下载解压
2. tar -xzf protobuf-2.1.0.tar.gz 
3. cd protobuf-2.1.0
4. ./configure --prefix=$INSTALL_DIR
5. make 
6. make check
7. make install

__proto文件更新需要重新进行编译__


## 3. 编写.proto文件

例：

    syntax = "proto2";
    package tutorial;
    
    message Person 
    {
        required string name = 1;
        required int32 id = 2;  // Unique ID number for this person.
        optional string email = 3;
    
      enum PhoneType 
      {
        MOBILE = 0;
        HOME = 1;
        WORK = 2;
      }
    
      message PhoneNumber 
      {
        required string number = 1;
        optional PhoneType type = 2;
      }
    
      repeated PhoneNumber phones = 4;
    }
    message AddressBook 
    {
      repeated Person people = 1;
    }

* .proto文件以package定义开头，这有利于解决不同项目的命名冲突
* 在C++中，.proto文件产生的类将会被置于package名的命名空间中
* 每个元素的"=1","=2"标记确定唯一的tag,这个tag将被字段用于二进制编码
* tag数量在1-15比高于15的tag数在编码时少一个字节
* 作为一个优化，可以将tags作为平常使用，或编入repeated，
* 每个在repeated里的域需要将tag数字重新编码
* 所以repeated域是优化的一个很好的选择


## 4. .proto文件中的域属性修饰
### 4.1 required
* 域中的值必须提供，否则message将会认为是未初始化的
* libprotobuf以debug方式编译，序列化一个未初始化的message将会造成断言失败
* required属性不能变 
    * 将required变为optiona，老的reader认为message没有这个域是不完整的
    * 老reader将会意外地拒绝或丢弃message

### 4.2 optional
* 域值可选
* 如果optional域值没有被设置，域值将被置为默认值
* 对于简单类型可以指定默认值
* 嵌入的message默认值总是message的默认实例或prototype

### 4.3 repeated
* 域将多次被复制
* repeated值的顺序将会在protocol buffer中保存


## 5. 编译.proto文件
1. 指定源文件目录
2. 指定产生源代码的目录
3. 将会在源代码目录生成addressbook.pb.h和addressbook.pb.cc文件

格式

    protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/addrssbook.proto
 

## 6. 标准message方法
每个message类会包含一系列其他的函数，这些函数能检查，操作整个message类

* bool IsInitialized() const;
    * 检查所有requited域知否被设置
* string DebugString() const;
    * 返回一个人类可读的messgage展示，debug时特别有用
* void CopyFrom(const Person& from);
    * 以给定的message值覆盖旧message
* void Clear();
    * 清除所有元素值，所有元素回到空的状态


## 7. 解析与序列化(定义在message.h)
* bool SerializeToString(string* output) const;
    * 序列化message并将序列化的字节存储在参数给出的字符串类中
    * 注意，这些字节是二进制的
* bool ParseFromString(const string& data);
    * 从data中解析出message
* bool SerializeToOstream(ostream* output) const;
    * 将message写入给出的C++ ostream中
* bool ParseFromIstream(istream* input);
    * 从给出的C++ istream中解析message
   


    