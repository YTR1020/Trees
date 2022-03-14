# Linux-1

## Linux基础

### Linux操作系统以及层级架构

#### 关于操作系统

**操作系统（operating system，简称OS）**
实质就是“一个可以安装其他程序的程序”。

1 使用文件系统（file system）来沟通连接硬盘和软件读取的地方。

2 含有设备驱动程序（Device Driver）使计算机和设备进行相互通信，相当于硬件的接口，操作系统只有通过这个接口，才能控制硬件设备的工作，假如某设备的驱动程序未能正确安装，便不能正常工作。因此，驱动程序被比作“ 硬件的灵魂”、“硬件的主宰”、“硬件和系统之间的桥梁”等。

3 还有用户接口（User Interface，简称 UI）——系统和用户之间进行交互和信息交换的媒介，实现信息的内部形式与人类可以接受形式之间的转换。通常指软件接口，一般有命令接口、程序接口、图形接口三种。

4 含有系统服务程序(system services)（系统自带），指执行指定系统功能的程序、例程或进程，以便支持其他程序，尤其是底层(接近硬件)程序。通过网络提供服务时，服务可以在Active Directory（活动目录）中发布，从而促进了以服务为中心的管理和使用。

内核（kernel）是操作系统最基本的部分。它是为众多应用程序提供对计算机硬件的安全访问的一部分软件，这种访问是有限的，并且内核决定一个程序在什么时候对某部分硬件操作多长时间。内核的分类可分为单内核和双内核以及微内核。严格地说，内核并不是计算机系统中必要的组成部分。

**操作流程**
用户——应用程序——操作系统——硬件

#### Linux操作系统

特点：开源，类Unix操作系统。【最早的系统是Unix操作系统——开源内核——Linux被开发出来】

**Linux的内核**
（从内到外层）

硬件——内核层（Linux操作系统核心的基础，附着在硬件平台上，即控制操作系统的各种资源并进行调配）——shell层（敲代码、可以输入命令、完成一些简单的编程）——应用层（基于x window环境）。

**Linux的脚本语言**

（大部分shell层基本都是用C语言编写的）但C语言属于通用编程语言，需要编译；而shell编程就不需要经历编译过程，几行脚本即可解决大多数问题。

**Linux的发行版本**

商业发行版：red hat为代表

社区组织维护发行版：debian为代表

关于red hat“红帽”：RHEL（Red Hat Enterprise Linux）即红帽的企业版Linux，收费；Centos（内核与RHEL一样，适合入门），不收费；Fedora core（RHEL的桌面版本），不收费。

关于Ubuntu：debian发展来的，适合菜鸟上手并且操作界面友好。

关于suse Linux：吸取红帽的特性，图形化非常方便。

关于gentoo：所有Linux版本里安装最复杂的，虚拟机安装需要编译安装系统，极客偏好。

关于Debian：安全，固若金汤，基本不死机。

#### Linux系统的层次结构

##### 操作命令行：

`[root@sk-1 ~]#` 

`[]`表示分隔符，没有实际意义；

`root` 表示当前登录的用户；

`@`分隔符；

`sk-1` 当前服务器取的名字；

`~`表示当前目录，单独只有`~`则表示此时在home目录下；

`#`在用户方来说，即是用户权限 = root；
`$`在用户方来说，即 = 其他人。

root用户的家目录在 /root。
其他用户的家目录在 /home/用户名。

##### Linux的结构
树状结构——根目录下有很多小目录：

**根目录/**   （最上面的目录）

##### Linux的一些基本shell命令

```
pwd     #查看当前自己在哪个文件夹中
cd..    #退到上一级目录下
ls      #查看当前目录下所有文件夹
cd bin    #进入bin目录下
cd root   #进入root文件夹下
cd /root 
cd /home/htsnhe    #切换目录
```

**查看Linux里的基本文件类型**

```
mkdir haha     #新建文件夹haha   
touch 123.txt    #创建一个文本文件
ls -la       #直观地看到当前目录下所有文件的详细信息
#例如从权限栏可得：dr-xr-x---以d开头则表示是文件夹；-rw-r--r--不以d开头则表示是其他类型的一些文件。
```

**Linux的常用shell命令**

```
whoami      #我是谁
passwd       #修改当前用户的密码（如果不想修改就Ctrl+c结束）
clear        #清理当前界面
history        #查看之前敲过的命令
cat /etc/passwd     #查看用户密码的文件
alias ha='cat /etc/passwd'          #给'cat /etc/passwd'命令起个别名为ha（系统重启后失效）
unalias ha                   #取消之前的系统的别名
alias                  #查看当前系统中所拥有的别名
#（tab键可以自动补全部分可以确定的命令）

#若想创建长期有效的别名，可以通过vi /etc/bashrc编辑在其中末尾加入alias ha='cat /etc/passwd'命令，然后重启系统即生效
vi /etc/bashrc
按i键（insert模式）才可以进行修改输入
按esc键+“：wq”表示保存并退出。
```

获得帮助:

```
ls --help    #获得帮助
yum -y install man-pages-zh-CN.noarch      #安装中文的手册
echo "alias cman='man -M /user/share/man/zh_CN'" >> .bashrc
source .bashrc
#把之后要查询的内容变成中文
cman ls   #即可用中文版查看ls的命令介绍
```

**重定向:**

输入输出：

0=标准输入
1=标准正确输出
2=标准错误输出

```
echo haha
echo 'nihao a'
echo nihao a

echo 'haha123' > 123.txt    #在123.txt文件里追加内容

echo $?   #查看上一个程序退出的状态码，不是0就是错误的。
```

重定向符号：

`>` 覆盖重定向；
`>>` 追加重定向；
`2>` 覆盖重定向错误输出数据流；
`2>>` 追加重定向错误输出数据流。

```
echo 'haha' > 1.txt
ls
cat 1.txt
#得到：
haha

echo 'nihao' > 1.txt
cat 1.txt
#得到：
nihao

echo 'today' >> 1.txt
cat 1.txt
#得到：
nihao
today
```

合并输出：

`&>` 覆盖重定向；
`&>>` 追加重定向；
`2>&1` 把错误流重定向到标准的输出文件中；
`1>&2` 把正确的输出流重定向到标准的错误输出文件中。

```
echo haha 1> ./yes.out 2> ./no.out
#运行echo haha程序，如果正确，就把结果输出到当前目录下的yes.out下，如果错误就把结果输出到当前目录下的no.out下

rm -rf *.out
#删除所有.out后缀的文件

mkdir path   #新建文件夹
echo haha 1> /root/path/yes.out 2> /root/path/no.out
#用绝对路径输出正确和错误的结果

echo hahanihao 1>&2 2> /root/path/no.out
#运行echo hahanihao程序，把正确的输出流重定向到标准的错误输出文件中，如果错误就会将错误结果的输出到/root/path/no.out，如果正确就直接输出到屏幕上。
rm -rf ./*
ls
echo hahanihao 1>&2 2> /root/path/no.out
#得到：hahanihao
ls
#得到:no.out
cat no.out
#发现里面并没有东西，而是在前面就已经输出了结果

echo hahanihao 2>&1 1> /root/path/yes.out
#运行echo hahanihao程序，把错误流重定向到标准的输出文件中，如果错误就会将错误结果的输出到屏幕，如果正确就输出到文件中。
ls
#得到：yes.out
cat yes.out
#得到：hahanihao
```

```
cat > haha.file <<EOF
#一直输入东西，直到输入EOF才结束，此时haha.file里面的内容就是你输入的内容。（EOF是标识符，不会输入到内容里）

[root@sk-1 path]# cat > haha.file <<EOF
>diyihang
>dierhang
>haha
>EOF

ls
cat haha.file
#得到：
diyihang
dierhang
haha

>会覆盖，>>则追加
```





















