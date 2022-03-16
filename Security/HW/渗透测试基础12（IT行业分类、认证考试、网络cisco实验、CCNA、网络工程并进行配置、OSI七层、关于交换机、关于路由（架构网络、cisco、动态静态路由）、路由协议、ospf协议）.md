# 渗透测试基础12

# 企业内网环境介绍（IT行业分类、认证考试、网络cisco实验、CCNA、网络工程并进行配置、OSI七层、关于交换机、关于路由（架构网络、cisco、动态静态路由）、路由协议、ospf协议）



## IT行业分类

程序员

系统工程师（linux windows unix）

网络工程师（cisco huawei juniper....）

推荐cisco huawei 



## 认证考试

CCNA 、CCNP 、CCIE（可直接考）难考

R&S ISP SEC DC Voice Wire



笔试 、lab（ts+diag+cfg)全英文考试



## 关于网络cisco实验、CCNA

使用工具：cisco packet tracer
下载：winpcap





![image-20220110191839560](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110191839560.png)



![image-20220110191943883](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110191943883.png)

![image-20220110192056787](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110192056787.png)

![image-20220110192128289](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110192128289.png)

![image-20220110192226840](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110192226840.png)



## 网络工程

### 终端设备：

手机 电脑 服务器 ATM.....

### 以太网交换机:

连接同一个网段之间的东西
前身（hub=集线器）

### 路由器【商用】：

连接不同网段的东西



打开：

![image-20220110192445794](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110192445794.png)

![image-20220110192456044](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110192456044.png)

并做一些设置：

![image-20220110192559210](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110192559210.png)

![image-20220110192621049](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110192621049.png)

![image-20220110192639937](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110192639937.png)

查看可选择的设备：

路由器——Routers

![image-20220110192847278](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110192847278.png)

交换机——Switches

![image-20220110192910090](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110192910090.png)

集线器——Hubs

![image-20220110193017337](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110193017337.png)

无线设备——Wireless Devices

![image-20220110193041953](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110193041953.png)

网线——![image-20220110193055773](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110193055773.png)

终端设备——end Devices

![image-20220110193116889](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110193116889.png)

### 进行配置：

需要一台交换机、两台台式机：

![image-20220110193336806](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110193336806.png)

调试台式机：

![image-20220110193421245](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110193421245.png)

![image-20220110193442456](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110193442456.png)

第二台台式机：

![image-20220110193502640](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110193502640.png)

想要两台台式机都可以连在一起打游戏：需要将两者都连接到交换机上：

此时可以两者相互ping，都能连通。

![image-20220110193621794](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110193621794.png)

关于交换机：无电源开关，插电即启动。有许多插口。



关于路由器：

![image-20220110194132449](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110194132449.png)

有许多模块【现实需要花钱】



## OSI七层：

### ISO-OSI模型：

1.物理层
光电，电磁波，在线路上传输(hub)

2.数据链路层
数据交换(设备：以太网交换机)
定义数据如何格式化，进行编址mac地址

3.网络层
数据传递，路由信息报文（路由器）
可以选择最优的路径去访问目标（ip地址，路由协议）

4.传输层
端到端的通信（point-to-point）

5.会话层
主机到主机的通信
建立，管理，结束程序之间的会话

6.表示层
数据以什么形式表示出来（加密服务，格式化/结构化数据）

7.应用层
我们的程序（http https ftp smtp snmp...）



## 关于交换机

![image-20220110194928951](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110194928951.png)

![image-20220110195016457](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110195016457.png)

![image-20220110195026899](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110195026899.png)

![image-20220110195140686](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110195140686.png)

IP地址相当于门牌号，mac地址相当于身份证号

![image-20220110195233949](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110195233949.png)

![image-20220110195256667](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110195256667.png)



## 关于路由

![image-20220110195355743](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110195355743.png)

![image-20220110195405372](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110195405372.png)



### 架构一个网络

![image-20220110195451896](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110195451896.png)

![image-20220110195505265](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110195505265.png)

![image-20220110195542521](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110195542521.png)

中间为运营商

左边内网如下，右边内网同理：

![image-20220110195622715](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110195622715.png)

![image-20220110195825560](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110195825560.png)

设置左右两边网关地址：

![image-20220110195807358](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110195807358.png)

![image-20220110195931890](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110195931890.png)

设置外网地址：

![image-20220110200005704](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110200005704.png)

配置路由器：

![image-20220110200032287](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110200032287.png)

【交换机，接电后直接启动，大多数情况不需要命令配置】

**使用cisco路由器命令行配置路由器**：

选择no

![image-20220110200145236](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110200145236.png)



#### **cisco路由器命令行：**

```
en    # 进入特权模式，全写是enable

?    # 查看可用命令

conf t    # 进入全局配置模式——取名

ho R1     # 取名R1，全名为hostname
```

优化命令：

```
no ip domain-lo    # 不要查询出错的命令
line con 0     # 进入console 0调试
no exec-t    # 不要超时把我弹出
logg syn    # 命令和弹出的内容换行显示
```

配置路由器的接口：

```
int [接口]    # 进入某个接口进行配置
interface f0/0

no sh    # 物理开启接口

ip add [ip地址] [子网掩码]    # 配置ip地址
ip add 192.168.1.1 255.255.255.0

int loo [编号]    # 环回口（本地测试）

int loopback ?
ip add 1.1.1.1 255.255.255.0
exit

sh ip int bri   # 查看接口的所有信息
show ip interface brief

sh run   # 查看路由器中所有配置
```

连通成功后：

![image-20220110201139071](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110201139071.png)



### 静态路由：

路由器是靠路由表来知道目的地怎么走！！！！！

```
sh ip route    # 查看路由表

ip route [目标网段] [子网掩码] [下一跳ip/接口]    

no [命令] 删除命令
```

![image-20220110201441706](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110201441706.png)

![image-20220110201910467](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110201910467.png)



**理论上**：

路由器=点=网络节点=node



## 路由协议：

动态路由协议:

rip路由信息协议（最大16跳）

eigrp （cisco私有）增强内部网关路由协议

ospf（公有）最短路径优先（使用范围很广）

is-is（公有）中间系统到中间系统（运营商用的很多）

BGP（最强！公有，支撑着全球互联网运行的）边界网关路由协议



### 重新配置动态路由——ospf协议：

删除之前对r1、r2、r3的配置：

![image-20220110202806227](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110202806227.png)

![image-20220110202731129](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110202731129.png)

![image-20220110202741990](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110202741990.png)



R1

```
router ospf 1

router-id 1.1.1.1

network 192.168.1.0 0.0.0.255 area 0 # 0.0.0.255是反掩码。放入区域0

network 13.13.13.0 0.0.0.255 a 0

network 1.1.1.0 0.0.0.255 a 0

【或精确宣告network 1.1.1.1 0.0.0.0 a 0】
```



R2

```
router os 1

router-id 2.2.2.2

net 2.2.2.0 0.0.0.255 a 0

net 192.168.2.0 0.0.0.255 a 0

net 23.23.23.0 0.0.0.255 a 0
```



R3(isp)

```
router os 1

router-id 3.3.3.3 

net 3.3.3.0 0.0.0.255 a 0

net 13.13.13.0 0.0.0.255 a 0

net 23.23.23.0 0.0.0.255 a 0
```



```
sh ip os nei    # 查看ospf邻居
```



## 关于交换机

```
sh mac 查看mac地址表
```



![image-20220110204326023](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110204326023.png)



当然这都是很初级的内容，深入学习之后简历可以增加路由交换NAT等内容上去

