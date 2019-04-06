##打包
    //讲所有.jpg图片打包成名为all.tar的包 -c create -f filename
    tar -cf all.tar *.jpg

##增加打包
	// 将所有.gif文件添加到all.tar包中 -r increase
	tar -rf all.tar *.gif

##更新文件
	// 原来tar包中的文件更新 -u new 
	tar -uf all.tar logo.gif

##列出文件
	// 列出tar包中的所有文件 -t 列出
	tar -tf all.tar 

##解压包
	// 解压出包中所有文件
	tar -xf all.tar
	