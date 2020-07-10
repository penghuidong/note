# eval

## 1. 用法

* eval 命令
* 两次扫描，第一次进行字符替换



## 2. 例子

* 获取最后一个参数

  ```shell
  cat xxx.txt
  eval echo \$$#
  
  ```



* 创建指向变量的指针

```shell
x=100
ptrx=x
eval $ptrx=50
echo $x        # x等于50
```

