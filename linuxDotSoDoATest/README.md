## linux下.so库与.a库使用
通常把一些公用函数制作成函数库，供其他程序使用。函数库分为静态库和动态库两种。静态库在程序编译时会被连接到目标代码中， 程序运行将不需要改静态库。动态库在程序编译时并不会被连接到目标代码中，而是在程序运行时才被载入，因此在程序运行时还需要动态存在。
# 创建动态库程序及文件
sub_1.h、sumfloat.c、subfloat.c、main1.c
# 静态库
```shell
gcc -c sumfloat.c subfloat.c
ar crv libafile.a sumfloat.o subfloat.o
```  
>知识拓展：
<br>gcc是Gnu的c编译器，gcc在执行编译工作的时候，总共需要4步：
<br>1、预处理，生成.i的文件[预处理器cpp]
<br>2、将预处理后的文件转换成汇编语言，生成文件.s[编译器egcs]
<br>3、有汇编变为目标代码（机器代码）生成.o的文件[汇编器as]
<br>4、连接目标代码，生成可执行程序[链接器ld]
其中参数详解如下：
<br>-c:只编译，不链接成可执行文件，生成.o文件
<br>-o:链接生成可执行文件，默认是生成a.out

> 知识拓展：
ar命令可以用来创建修改库，也可以从库中提出单个模块。一般多用来生成静态库。
参数详解：
-c：创建一个库。不管库存不存在都将创建
-r：在库中插入模块（替换）
-v：程序执行时显示详细信息
> 
# 动态库
```shell
sudo cp libsofile.so /usr/lib
gcc -shared *.o -o libsofile.so
```
>知识拓展：
<br>参数详解：
-shared：生成共享库
*.o：将当前文件目录下的.o文件批操作
这里提供一下解决报错的
<br>方法二
gcc -o test main1.c -L. -lname
其中，
<br>-L：表示在当前目录下，可自行定义路径path，即使用<br>-lpath 即可。
<br>－lname：name:即对应库文件的名字(除开lib)，即若使<br>用libafile.a，则name 为afile；若要使用libsofile.so，则name 为sofile。
>
# 动态库链接失败问题
>链接器ld默认的目录是/lib和/usr/lib，如果放在其他路径也可以，需要让ld知道库文件在哪里。<br>
方法1：
export LD_LIBRARY_PATH=/home/kingwq/learn_ws/linuxDotSoDoATest:$LD_LIBRARY_PATH  <br>
方法2：
mv 动态库到 /lib和/usr/lib 以及动态库配置文件/etc/ld.so.conf内所列的目录下
>
