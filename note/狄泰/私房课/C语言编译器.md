## gcc 编译选项

#### 生成映射文件

```shell
gcc -Wl,-Map=xxx.map xxx.c
#-Wl选项告诉编译器将后面的参数传递给链接器
```

#### 获取系统头文件路径

```shell
gcc -v xxx.c 
```

#### 生成依赖关系

* 获取目标的完整依赖关系

  ```shell
  gcc -M xxx.c
  ```

* 获取目标的部分依赖关系

  ```shell
  gcc -MM xxx.c
  ```

#### 指定库文件及库文件搜索路径

* `-L` : 指定库文件的搜索路径

* `-l` : 指定库文件

  ```shell
  gcc xxx.c -L. -lxxx # -l连接库可以不写lib前缀和.a后缀
  ```

  

