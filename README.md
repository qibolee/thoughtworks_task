# ThoughtWorks 2018校园招聘作业

实现羽毛球场的预约管理系统, 项目由C++实现, 有以下几个目录:

### include:
包含项目的头文件，有如下几个:

booking_item.h: 表示预约系统的一条预约记录, 包含日期, 时间段, uid, 起始时间的秒数, 结束时间的秒数

booking_management.h: 预约系统的数据接口, 主要是提供预约, 取消预约,和显示各场地收入情况的功能, 内部提供了计算任意日期时间段的价格

date_util.h: 处理日期的工具类, 包括检查日期的合法性, 时间段的合法性, 日期时间段转化为秒数和秒数转化为日期字符串

mlog.h: 自己实现的简易版的log工具

string_util.h: 字符串的处理工具, 包括trim, split功能


### src:
包含项目的实现代码，有如下几个:

main.cpp: 程序的入口

booking_management.cpp: 对应于booking_management.h的实现代码

date_util.cpp: 对应于date_util.h的实现代码

mlog.cpp: 对应于mlog.h的实现代码

string_util.cpp: 对应于string_util.h的实现代码


### log:
项目的日志路径, 程序初次启动后会自动创建四个日志文件, 包括debug.log, trace.log, warning.log, fatal.log

### out:
项目编译后生成的可执行文件路径, 主要是源文件生成的一系列目标文件和main可执行文件


### Makefile
Makefile文件, 详细说明了项目的编译过程, 编译器要求支持C++14标准, 推荐使用clang++

编译: make

运行: ./out/main



