# redis通信协议

### 1. redis协议

* `liline协议`，只在命令行下的客户端使用
* `multibulk协议`，客户端传送过来的数据的第一个字符是"*"
* C-S之间发送的命令或数据一律以"\r\n"结尾(CRLF)
* 





> 参考文档http://redisdoc.com/topic/protocol.html#

