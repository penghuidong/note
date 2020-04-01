# protobuf文件功能及描述


# 1. google::protobuf文件
### 1.1 google/protobuf/arena.h
arena.h定义了一个Arena的类，用于更好地提供内存分配性能

### 1.2 google/protobuf/descriptor.h
descriptor.h包含了一系列描述protocol message 类型的类

### 1.3 google/protobuf/descriptor.pb.h
descriptor.pb.h“重写”了descriptor

### 1.4 google/protobuf/descriptor_database.h
提供了操作descriptor数据库的一些接口

### 1.5 google/protobuf/dynamic_message.h
定义了一个能在编译时仿真未知类型的Message类的实现

### 1.6 google/protobuf/map.h
定义容器类

### 1.7 google/protobuf/message.h
定义了用于non-lite protocol message对象实现的抽象接口类--Message

### 1.8 google/protobuf/message_lite.h
定义了用于所有protocol message（non-lite和lite）对象的抽象接口类--MessageLite

### 1.9 google/protobuf/repeated_field.h
对于repeated域的操作，RepeatedField和RepeatedPtrField用于产生操作repeated域的protocol message类

### 1.10 google/protobuf/service.h
声明了proto2RPC服务的底层抽象类

### 1.11 google/protobuf/text_format.h
以人类可读的文本格式打印和解析protocol message

### 1.12 google/protobuf/unknown_field_set.h
包含了在解析protocol message时用于保持追踪未识别域的类

### 1.13 google/protobuf/stubs/common.h
包含了基础类型和工具

# 2. google::protobuf::io文件
google::protobuf::io文件夹下定义了一些用于IO操作的辅助类，protobuf使用这些类处理IO、编码解码raw字节。大多数用于不需要关心这些package, 但是，如果想要适配protobuf工作在自己的IO接口上，这将需要进一步了解。

### 2.1 google/protobuf/io/coded_stream.h
