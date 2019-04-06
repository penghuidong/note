##protobuf是什么
* 一个跨语言，跨平台以及支持可扩展的序列化结构数据的格式  
* 简单来说，是一种google定义的结构化数据格式
* 用于数据的序列化与反序列化
* 直接对二进制源数据进行操作，相对XML小，快，简单
* 适合数据存储，网络间的数据传输





#安装Google protocol buffer
1. 官网下载解压
2. tar -xzf protobuf-2.1.0.tar.gz 
3. cd protobuf-2.1.0
4. ./configure --prefix=$INSTALL_DIR
5. make 
6. make check
7. make install

__proto文件更新需要重新进行编译__