#Qt Creator工程管理
* Qt Creator以工程项目的方式对源码进行管理
* 一个Qt Creator工程包含不同类型的文件
	* .pro 项目描述文件
	* .pro.user 用户配置描述文件
	* .h 头文件
	* .cpp 源文件
	* .ui 界面描述文件
	* 资源文件：图片，音频等

#.pro项目描述文件的基本构成
* #：注释起始符
* QT:模块声明
* TARGET:可执行文件
* TEMPLATE:程序模板声明
* SOURCE：源码文件声明
* HEADERS：头文件声明
* FORMS：界面文件声明
* RC_FILE:资源文件声明

#.pro项目描述文件中的高级变量
* INCLUDEPATH：头文件搜索路径
* CONFIG:设定项目的配置信息和编译选项
* LIBS:添加第三方库文件
* DEFINES:定义编译宏

#CONFIG配置
* CONFIG用于设定项目的配置信息和编译选项
* CONFIG的常用选项
	* debug：构建debug版本的可执行程序
	* release：构建release版本的可执行程序
	* debug_and_release：同时构建debug版和release版
	* warn_on:尽可能多的输出警告信息
	* warn_off：不输出警告信息

__.pro文件的本质是Qt中的Makefile文件__


#项目文件
* 一般来说，项目文件中的描述都使用相对路径
* 而相对路径是相对于项目文件本身而言
* Qt Creator将项目文件作为目标文件

注意：

1. Qt Creator在打开项目文件的同时会生成.pro.user文件
2. .pro.user文件包含一些与Qt相关的本地配置信息
3. 当需要在不同计算机之间移动项目源码时，建议删除.pro.user文件

#工程中的概念
* 构建build
	* 对项目中的所有文件进行编译，最终生成可执行程序
* Debug版
	* 可以进行程序调试的构建版本
	* 可执行程序中包含调试信息，运行效率不高
* Release版
	* 最终发布的应用程序构建版本
	* 无调试信息，运行效率高