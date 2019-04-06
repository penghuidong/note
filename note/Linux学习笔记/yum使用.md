##yum的使用


###没有可用软件包问题
* 当在Linux系统中使用yum安装软件时提示“没有可用软件包”时，表示yum源中没有对应的安装包了
* 这时需要安装EPEL
* EPEL(Extra Packages for Enterprise Linux),企业版Linux额外包，RHEL分布非标准包的社区类库  
* 如果yum没有找到docker包，则要更新epel第三方软件库  

命令：

    yum install -y epel-release
* 更新完epel第三方软件库后，再次尝试使用yum命令安装对应的软件包