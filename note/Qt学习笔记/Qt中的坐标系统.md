# 坐标系统
* GUI操作系统都有特定的坐标系统
* 图形界面程序在左边系统中进行窗口和部件的定位
* 定位类型：
  * 顶级窗口部件的定位
  * 窗口内部件的定位
  * 窗口部件的大小设置

#QT的坐标系统
* Qt使用统一的坐标系统定位窗口部件的位置和大小
* Qt部件类提供成员函数在坐标系统中进行定位
* QWidget类提供了窗口部件所需的坐标系统成员函数

![Qt Window Geometry](pic\QtWindowGeometry.bmp "Qt 窗口坐标系统")

注意事项：  
__geometry()和frameGeometry()中的几何数据必须在show()调用后才有效。__


#窗口部件的大小设置
