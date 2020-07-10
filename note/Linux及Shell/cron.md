# cron: 执行调度命令的daemon
* 每个用户都有自己的cron表
* crontab命令用于处理cron表


# cron表
* cron表指定了执行时间以及要执行的命令
* cron表以表创建者的身份执行命令，并不会去执行.bashrc文件
* crontab -e编辑cron表
* crontab -l列出当前用户的cron表
* crontab -r删除当前用户的cron表

# cron表的字段
__cron表中的每一行有6个字段，代表`分`，`时`，`日`，`月`，`周几`，`命令`__


* 字段之间以空格隔开

 例子：

    02 * * * * ./some.sh #每小时第二分钟执行some.sh
    
    00 5,6,7 * * *  ./some.sh #每天的第5，6，7小时执行
    
    */1 * * * * ./some.sh #每隔一分钟执行

