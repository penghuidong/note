#问题
服务器在接收到服务器的请求后，会自动调用对应的逻辑代码进行请求处理，但是逻辑代码是由程序员编写并放到服务器中，那么服务器怎么直到该给调用哪个类和哪个方法进行请求处理

#解决
程序员在编写代码的时候如果能够按照服务器能够识别的规则进行编写，浏览器按照指定的规则进行发送请求，那么服务器就可以调用并执行相应的逻辑代码进行请求处理了

#实现技术:servlet技术
##概念
侠义的servlet是指java语言实现的一个接口，广义的servlet是指任何实现了这个servlet接口的类，一般情况下，人们将servlet理解为后者。servlet运行于支持java的应用服务器中。从原理上讲，servlet可以响应任何类型的请求，但绝大多数情况下servlet只用来扩展基于http协议的web服务器。

##特点
* 运行在支持java的应用服务器上
* servlet的实现遵循了服务器能够识别的规则，也就是服务器会自动地根据请求调用对应地servlet进行请求处理
* 简单方便，可移植性强

##使用
1. 创建普通的Java类并继承HttpServlet
2. 覆盖HttpServlet的service方法
3. 在service方法中写逻辑代码
4. 在webRoot下的WEB-INF文件夹下的web.xml文件中配置servlet

##运行流程
浏览器发送请求到服务器，服务器根据请求URL地址中的URL信息在webapps目录下找到对应的项目文件夹，然后在web.xml中检索对应的servlet，找到后调用并执行servlet

例：URL: http://localhost:8080/project/my2
组成： 服务器地址:端口号/webapps下的文件夹名称/要执行的servlet的url-pattern
URI:虚拟项目名 /servlet的别名