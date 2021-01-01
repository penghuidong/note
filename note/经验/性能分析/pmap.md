# pmap 查看进程用了多少内存



- Address: 内存开始地址
- Kbytes: 占用内存的字节数（KB）
- RSS: 保留内存的字节数（KB）
- Dirty: 脏页的字节数（包括共享和私有的）（KB）
- Mode: 内存的权限：read、write、execute、shared、private (写时复制)
- Mapping: 占用内存的文件、或[anon]（分配的内存）、或[stack]（堆栈）
- Offset: 文件偏移
- Device: 设备名 (major:minor)