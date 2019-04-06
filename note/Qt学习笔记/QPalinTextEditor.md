###简介与概念
&emsp;&emsp;QPlainTextEdit是一个多行文本编辑器，可以显示和编辑多行文本文字，被用于处理大型文档与快速响应用户输入。QPlainTextEdit使用许多和QTextEdit一样的技术和概念，但是QPlainTextEdit更适用于对纯文本处理。  
&emsp;&emsp;QPlainTextEdit工作在图形和表格中，在图形中字符串被一个字一个字格式化以适应图形的大小。在读普通文本时，默认一行表示一个段落，一篇文档由零个或更多的段落组成。段落被hard断行分割，在段落中的每个字符有自己的各种属性，如字体和颜色等。  
&emsp;&emsp;QPlainTextEdit中默认的鼠标光标是Qt::IBeamCursor,通过`viewport()`的光标属性修改QPlainTextEdit的光标形状。

###将QPlainTextEdit作为展示组件
&emsp;&emsp;可以使用`setPlainText()`设置或替换文本，`setPalinText()`删除已经存在的文本并替换它。  
&emsp;&emsp;通过`QTextCursor`类可以将文本插入，获取使用`insertPlainText()`,`appendPlainText()`,或者`paste()`。  
&emsp;&emsp;文本编辑会默认以空格为间隔把单词包裹起来以适应文本编辑组件。`setLineWrapMode()`函数用来指定你想要的换行类型，如果换行时不想使用任何字符，使用WidgetWidth或者NoWrap。如果使用WidgetWidth组件的换行，可以指定是否以空格换行，或者在任意地方使用setWordWrapMode()。
&emsp;&emsp;`find()`函数能被用于在文本中查找和选择给出的字符串。
&emsp;&emsp;如果你想要限制在QPlainTextEdit中的段落数量，那么可以使用maximumBlockCount属性，正如在日志查看器中，限制段落数量很有用。`setMaximumBlockCount()`和`appendPlainText()`将QPlainTextEdit转变成一很有效的日志文本查看器。