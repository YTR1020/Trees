# Linux初级（Linux简单介绍、kali-vnc、shell的认识、重定向、各文件夹的作用、基本文件管理命令、文件类型、文本编辑器、用户管理、权限管理、用户和组的添加删除、进程查看和管理、优先级和作业控制、包管理、链接文件、计划任务、防火墙基础）

# linux简单介绍



GNU/Linux ——内核



版本：

Redhat(RHEL)    收费版  企业多用

SUSE   美观

Debian     免费，优点多，kali的内核

Ubuntu   桌面友好 (kde gnome两类)

Gentoo   可以修改为私人的，基于源代码发行，安装缓慢

Slackware     linux里最老的，但是有一些缺陷

Knoppix      和kali像，可以在光盘上运行（LiveCD），完整版需要安装。硬件检测、修复能力等很好。

FreeBSD——不是linux系统，用户多，相当于BSD的系统家族，多数情况下用于服务器的操作系统，速度快，但不支持桌面界面，使用资源相对少。





# kali-vnc

大多数情况我们使用linux系统是用虚拟机。

可以下载centos 、Debian 或者Ubuntu到虚拟机

配置ssh对虚拟机进行管理。

或者使用kali，自带vnc，图形界面的效果。——便于对自己多个操作系统的演示。



## kali消除命令提示

新版kali里有命令提示，初学可以关掉提示：

```
chsh
```

即要改变登录的shell。

显示目前使用的shell：`Login Shell [/user/bin/zsh]:`因为有些命令是支持shell格式有些是不支持的，所以我们可以把它改为`/bin/sh`

```
/bin/sh
```

然后重启系统：

```
shutdown -r now
```



## kali开启vnc——便于可以远程控制等

```
vncserver :1
```

开启vnc

普通的windows系统里要连接vnc（5900端口）就直接连接ip地址即可，但是kali的vnc需要上述命令开启，说明kali的vnc开启是连接的5901端口上的

连接kali：

```
[kali的ip] :1
```

但是实际上无法连接。



所以需要我们用root用户去编辑：

```
sudu su
vi /root/.vnc/xstartup


# ls -a
# cd ./.vnc/
【ls -a才能看到的隐藏文件】
```

然后把里面内容全部替换成以下内容：

```
#!/bin/sh

# Uncomment the following two lines for normal desktop:
unset SESSION_MANAGER
unset DBUS_SESSION_BUS_ADDRESS
# exec /etc/X11/xinit/xinitrc

[ -x /etc/vnc/xstartup ] && exec /etc/vnc/xstartup
[ -r $HOME/.Xresources ] && xrdb $HOME/.Xresources
xsetroot -solid grey
vncconfig -iconic &
x-terminal-emulator -geometry 80x24+10+10 -ls -title "$VNCDESKTOP Desktop" &
#x-window-manager &
#gnome-session &
x-session-manager & xfdesktop & fce4-panel &
xfce4-menu-plugin &
xfsettingsd &
xfconfd &
xfwm4 &
```

然后重启，开启vnc

```
shutdown -r now
vncserver :1
```

用vnc去连接：

```
[kali的ip] :1
```



![image-20220120134634341](02 kali-vnc.assets/image-20220120134634341.png)





# 关于操作系统shell的认识

## 定义

shell——即系统的一个控制权

确切来说：

**shell是系统和文件系统之间的东西。**

windows上的cmd就是windows的shell，即可以通过操作系统来操作一些文件



## linux里shell的使用

### 基本的简单命令

```
data
输出当前的时间

whoami
查看当前使用的用户

passwd
修改当前用户的密码

history
查看之前敲过的哪些命令
```

### 命令的别名——电脑重启即没用了

```
cat /etc/passwd
查看所有的用户名和信息

alias haha='cat /etc/passwd'
给上述命令取一个别名

haha
此时即相当于执行cat /etc/passwd，即可以进行简写

unalias haha
取消命令的别名

alias
查看当前操作系统中现有的所有别名
```

### 永久别名（kali里没有，其他linux系统中可能有）

```
vi /etc/bashrc

然后把取别名的命令添加进去即可。alias haha='cat /etc/passwd'
```



### 关于命令帮助手册

```
ls
列出当前文件夹

ls --help
可以查看命令帮助

man ls
查看详细的ls命令帮助
（按q结束查看）
```





# 重定向

## 输入输出：

0=标准输入

1=标准的正确输出

2=标准的错误输出



`echo $?`查看上一个程序的退出状态码，不是0就是错误的。



## 重定向符号

`>` 覆盖的重定向

`>>` 追加重定向

`2>` 覆盖重定向错误输出流

`2>>` 追加重定向错误输出流



## 合并输出

`&>` 覆盖的重定向

`&>>`追加重定向

`2>&1`把错误流重定向到标准输出文件【屏幕】中

`1>&2`和上面相反，把正确流重定向到标准输出文件中



新建两个.out文件

`echo haha 1>./path/yes.out 2>./path/no.out`如果前面的程序是正确的就输出到yes.out，如果是错误的就输出到no.out

#### **正确和错误分别输出到某个地方**——可以根据这点来查找大文件的出错点



`echo hahanihao 1>&2 2>./path/no.out`

####**正确的输出到屏幕，错误的输出到no.out里**



#### 一直输入东西【尤其是多行】，知道打EOF才结束，此时haha.txt就是你刚刚输入的东西

```
cat > haha.txt << EOF
> ddddd
> aaa
> fffff
> eeee
> EOF
```

然后`cat haha.txt`

得到：

```
ddddd
aaa
fffff
eeee
```

此时`>`可以替换为`>>`



## 关于大小写转换——tr

```
head -n 5 /etc/passwd | tr 'a-z' 'A-Z' > ./path/passwd.out

取/etc/passwd中的前五行字，把小写字母都转换成大写并输出到./path/passwd.out文件里。
```






# kali各文件夹的作用

——linux里万物都是文件，包括进程等

文件系统FSH（**Filesystem Hierarchy Standard**文件系统层次化标准）

`/`根

`bin` 普通用户使用的命令

`sbin` 管理员使用的命令

`dev` 设备文件

`/dev/null`= 垃圾桶



`root` 最高用户root的home目录

`home` 普通用户的home目录

`proc` 虚拟文件系统，内核，进程信息



`usr` 系统文件

`/usr/local` 软件安装目录——比如Nginx服务器下载

`/usr/bin` 普通用户使用的程序

`/usr/`管理员用户使用的程序

`/usr/lib` 库文件类似windows上的`dll`——比如游戏的库

`/usr/lib64` 64位库文件



`boot` 存放系统启动相关的文件，比如kernel引导程序

`etc` 软件的配置文件——arp欺骗需要在该文件里去修改一些东西。

`tmp` 临时文件——可以存放木马，并且一直存在

`var` 存档，存储一些变化的文件，数据库，日志，邮件等。所以如果需要在日志里提权，一定不能忘了var

`media` 移动设备挂载

`mnt` 手工挂载






# 基本文件管理命令

```
touch [文件名]
创建一个文件——具体类型取决于你想把它当做什么

mkdir ./path/haha{1,2,3}
创建多个文件夹

cp -v abc.txt ./path/haha1/cde.txt
拷贝abc.txt到./path/haha1并顺便把名字修改为cde.txt了

rm -rf [文件夹或者文件名]
强制删除并不提醒

rm -rf /*
删除整个系统

查看文件内容
cat tac less more head tail tailf grep paste 等

cat -n [文件]
显示行号

cat -n -A [文件]
显示控制
```




# 文件类型

`ls -l` 查看文件类型

`-` 普通文件

`d` 目录文件——只能cd去进入

`b` 设备文件

`c` 字符设备文件

`s` 套接字文件

`p` 管道文件

`l` 链接文件



`file /etc/hosts`可以看到是ASCII text文件

`file [文件/文件名]`会得到属性类型






# 文本编辑器

编辑文件内容：

`vi` `vim` `nano`基本在linux自带

`vim`按下i键才能进入insert模式输入字

`nano`里指令`^s`表示`Ctrl+s`



使用`vi`：

`vi /etc/1.txt`进入文件

不能使用鼠标，光标由h、j、k、l键跳转

`h`左

`j`下

`k`上

`l`右



`w`下个单词的词首

`e`当前单词的词尾

`b`上一个单词的词首



`^`跳到行首

`$`跳到行尾



`#[数字]`往下移多少行

`dd`删除一整行

`u` 撤销

`:[行号]`跳到第几行

`:wq`保存并退出

`:q!`退出不保存








# 用户管理

## 用户和组

`id`查看当前用户登录信息

`id [用户名]`查看别人的信息



`systemctl start ssh`打开ssh

`who`查看当前在线连接的用户，连接方式及ip地址。看到谁在登录

`wall '内容'`可以从本机发送对话给其它连接的用户



`ps aux | less`查看谁在执行什么进程，按q退出

`ps aux | grep [名字]`专门查看某个进程



`/etc/passwd`用户信息

`/etc/shadow` 用户密码信息



root用户，uid=0，最高权限

`useradd`添加用户

`-u`指定uid

`-g`指定gid

`-c`注释信息

`-d`家目录

`-s`指定shell【可以来限制其一些命令】

`-G`附加组

`-r`创建系统用户

`useradd -u 1020 -g 1000 -c "miaoshu" -d /home/user1 user1 `

`passwd user1`可以用来修改user1的密码





# 权限管理

## 提权

`sudo` 提权命令

`sudo su`直接提到root权限

`sudo [用户名]` `su [用户名]`切换用户

`sudo -l`查看什么命令可以让我sudo



`vi /etc/sudoers` 编辑sudo文件——可以留下后门（ALL=(ALL:ALL) ALL）

![image-20220121090943861](10 权限管理.assets/image-20220121090943861.png)



## 基本权限UGO

u = 属主

g = 属组

o = 其他人



权限类型

rwx = 421

可读可写可执行



`chmod [权限数字] [目标文件]` 修改权限

`chmod u+x [目标文件]` 增加属主的执行权限

`chmod a=rwx [目标文件]`  `a=rwx` 所有人可读可写可执行

`a=-` 所有人都没有权限



测试：

```
ls
cd /home/kali
ls
touch ceshi.txt

nano ceshi.txt

ze shi yige ceshi wenjian !!
en

ctrl+s保存

ls

cat ceshi.txt
ls -la

chmod u+x ceshi.txt   
ls -la ceshi.txt
chmod a=rwx ceshi.txt
ls -la ceshi.txt
chmod a=- ceshi.txt
```



`chown :[用户组] [文件]`

把文件组进行修改

`chown [用户名]:[用户组] [文件]`

修改用户名和所属组





# 用户和组的添加删除

linux里存储的密码是通过了哈希的加密的

`cat /etc/group ` 查看计算机上的组



## 关于用户

`usermod -l [新的名字] [以前的名字]` 修改用户名

`usermod -L [用户名]` 锁定用户

`usermod -U [用户名]` 解锁用户

`cat /etc/shadow` 查看用户名和密码等

`userdel -r [用户名]`彻底删除用户





## 关于组

`cat /etc/group ` 查看计算机上的组

`groupadd [组名]`创建添加一个组，然后再次查看能看到组id【组号】

`groupmod -g 1008 [组名]`修改组号

`groupdel [组名]`删除组

`gpasswd -a [用户名] [组名]`把用户挪动到哪个组里

`gpasswd -d [用户名] [组名]`把用户从某个组里移除






# 进程查看和管理

## 进程类型：

**守护进程：**

系统在引导过程中启动的进程，和终端无关

**前台进程：**

和终端有关，需要通过终端启动



`ps -aux` 查看进程



进程状态：

`<` 高优先级进程

`N` 低优先级进程

`+` 属于某个前台组的进程

`s` 某一个会话的leader进程

`l`进程加锁

`R` 运行

`S`睡眠

`D` 磁盘睡眠

`T` 停止

`X` 死亡

`Z` 僵尸



`ps -aux` 

`a` = 和终端相关的进程

`u` = 以用户为中心

`x` = 和终端无关的进程



`ps -ef`更详细一些

`e` = 显示所有进程

`f` = 显示完整格式的程序信息



`cat /run/sshd.pid`查看进程id

`ps aux | grep sshd`查看更详细的进程id

`ps -ef | grep [进程id]`

出现该命令时不用管：

![image-20220121210711022](12 进程查看和管理.assets/image-20220121210711022.png)

也可以查看进程id的：

`pgrep -l sshd`

`pidof sshd`



`pstree`树状图查看进程



`top` 命令——动态显示目前运行的，还可以自动刷新

`top -d 1` 每一秒监控一次

`top -d 1 -p [进程号]` 单监控某个进程

`top -d 1 -u [进程号]` 



Ctrl+C结束



`kill -9 [进程id]`发送关闭进程的信号——关闭子进程可能只能导致软件崩溃，彻底关闭需要关闭父进程

`kill -1 [进程id]` 发送重新装载的信号

`kill -l` 查看支持发送的所有信号




# 优先级和作业控制

## 优先级

进程优先级0——99，实时优先级，越小越优先

静态优先级0——139，越小越优先

nice值，-20——19

默认nice值为0，优先级120

`ps axo pid,command,nice --sort=nice`查看进程以及它的nice值



`sleep 10`

`sleep 10 $`发现进程被拖到后台执行

将进程拖到后台执行：`&`



`renice -20 [进程号]`

更改进程的优先级为-20



## 作业控制

`screen -S 'ping www.baidu.com'`【和windows不同，linux里会无限ping下去】用screen -S可以让它后台控制。



`screen -list`

列出所有后台执行的东西



`pkill screen`

删除所有后台进程






# 包管理

相当于软件商店。

常见软件商店：brew rpm apt......pip等 都是包管理器=软件商店



`rpm -ivh xxxxxx.rpm` 安装rpm软件包【rpm相关命令多用在centos里】

`i` = 安装

`v` = 可视化

`h` = 列出hash标记



`rpm -q  [软件包名字]`查询软件包

`-a` 查询所有软件

`-c` 查询配置文件

`-i` 查询程序信息



kali使用的Debian用的是`apt`软件包-包管理工具

`apt-get install [名]`去安装某软件



比如输入`beef`发现没有这个软件，然后kalil就会询问是否需要安装。

我们可以使用：`apt-get install beef-xss`这条命令去安装beef。

`apt-get install -y beef-xss`该命令即是安装过程中所有选择默认选yes

安装完成后，`beef-xss`即可点击执行，打开beef



`apt-cache search mysql`查看所有mysql名的安装包

`dpkg -l | grep mysql`查看本机安装了什么mysql名的东西

`apt list [软件名字]`列出安装了什么软件

`apt info [软件名]`查看软件的说明



`apt-get upgrade beef-xss`升级软件

`apt-get remove beef-xss`卸载软件【只会把软件本身卸载，不会把配置文件删除】

`apt-get purge beef-xss`顺带把配置文件删除






# 链接文件

实质是在linux系统里制作一个快捷方式



**软链接**——实质即快捷方式：

`ln -s [源文件名] [链接名]` 给目标创建一个快捷方式

不加`-s`就是硬链接

**硬链接**——指向源文件的指针，不是快捷方式，如果修改，源文件也会跟着变。

——两者在底层的区别较明显。






# 计划任务

## 单次执行

`at now +1min`从现在开始一分钟后

`useradd zj` 增加一个名为zj的用户

` Ctrl+d`结束



`systemctl start atd` 启动定时服务

`systemctl status atd` 查看定时服务的状态



`vi at.jobs`  使用文件的方式设置计划任务

`at now +1min < at.jobs`  里面添加要执行的内容：1分钟后去执行 



## 








