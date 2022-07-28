# RemoteWindowControl
自研跨平台远程桌面控制软件

# 适用平台
Windows、Linux

# 开发目的
由于目前网络上比较难找到远程控制软件，且开源的项目例如VNC的源码又较难阅读。
所以打算从最基础开始做一款开源的远程桌面控制软件。

# 使用方法
修改 src/windows/client_mainwindow.cpp 定义的远程IP

# TODO
1.界面完善。目前只是最简陋的QT界面  
2.支持数据转发。目前只支持直连，所以局域网使用，后期考虑支持在公网搭建数据转发端  
3.传输数据序列化、压缩  

# 编译方法
mkdir build && cd build  
cmake ..  
make
