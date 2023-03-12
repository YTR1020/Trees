# 一、实验名称

上机任务1：Windows 和Linux操作系统的网络常用命令使用



# 二、实验者、实验时间

实验者：信息安全2102尹若彤（3201603102）

实验时间：2023年3月9日



# 三、实验目的

1. 了解或掌握一些网络常用命令的含义、用途和操作方法；

2. 掌握`ping`、`ipconfig`、`arp`等命令的功能及一般用法；

3. 能应用上述命令进行网络连通、网络状态、网络配置等；
4. 通过实验熟悉与网络相关的组件的含义和用途；
5. 能够查看网络的状态，对网络进行简单的配置，对常见的故障进行诊断和排除。



# 四、实验原理

## 4.1 ping命令

### 4.1.1 功能

​		ping命令是最常用的命令,特别是在组网中。 ping 命令基于ICMP协议，在源站点执行向目的站点发送ICMP回送请求报文，目的站点在收到报文后向源站点返回ICMP回送主报文，源站点把返回的结果信息显示出来。
​		该命令用来测试站点之间是否可达，若可达，则可进一步判断双方的通信质量，包括稳定性等。
​		需要注意的是，有些主机为了防止通过ping 探测，通过防火墙设置禁止ping 或者在内核参数中设置禁止ping，这样就不能通过ping确定该主机是否处于开启状态或者其他情况。
​		有关ICMP的详细解释参考《计算机网络》(第8版）教材4.4.2节。

### 4.1.2 命令格式

​		Windows系统用户可单击“开始”→“运行”选项，并键入`cmd`，打开命令行程序。在命令提示符后，按如下格式输入:

```bash
ping [-t] [-a] [-n count] [-l size] [-f] [-i TTL] [-v TOS] [-r count] [-s count] [[-j host-list]|[-k host-list]] [-w timeout] [-R] [-s srcaddr] [-4][-6] 目标主机
```

​		其中，目标主机可以是IP地址或者域名。

### 4.1.3 命令参数

略



## 4.2 ifconfig命令

### 4.2.1 功能

​		该命令用于显示、更新和释放网络地址设置，包括IP地址、子网掩码、网关地址和DNS服务器设置等。

### 4.2.2 命令格式

​		命令格式如下所示:

```bash
ipconfig [/allcompartments] [/? | /all |
/renew [adapter] | /release [adapter] | /renew6 [adapter] | /release6 [adapter] | /flushdns | /displaydns | /registerdns | /showclassid adapter | /setclassid adapter [classid] | /showclassid6 adapter | /setclassid6 adapter [classid] ]
```

​		其中，adapter为连接名称，允许使用通配符`*`和`?`。

### 4.2.3 命令参数

```
/? 显示帮助消息。
/all 显示完整配置信息。
/release 释放指定适配器的IPv4地址。
/release6 释放指定适配器的IPv6地址。
/renew 更新指定适配器的IPv4地址。
/renew6 更新指定适配器的IPv6地址。
/flushdns 清除DNS解析程序缓存。
/registerdns 刷新所有DHCP租约并重新注册DNS名称。
/displaydns 显示 DNS解析程序缓存的内容。
/showclassid 显示适配器允许的所有IPv4 DHCP类ID。
/setclassid 修改IPv4 DHCP类ID。
/showclassid6 显示适配器允许的所有IPv6 DHCP类ID。
/setclassid6 修改IPv6 DHCP类ID。
```



## 4.3 netstat命令

### 4.3.1 功能

​		netstat是Windows系统提供的用于查看与TCP、IP、UDP和ICMP协议相关统计网络工具，能检验本机各端口的网络连接情况。

### 4.3.2 命令格式

​		命令格式如下所示:

```bash
NETSTAT [-a] [-b] [-e][-f] [-n] [-o] [-p proto] [-r] [-s] [-t] [interval]
```

### 4.3.3 命令参数

```
-a 显示所有连接和侦听端口。
-b 显示在创建每个连接或侦听端口时所涉及的可执行程序。在某些情况下，已知可执行程序承载多个独立的组件显示创建连接或侦听端口时所涉及的组件序列。在此情况下，可执行程序的名称位于底部[]中，它调用的组件位于顶部，直至达到TCP/IP。注意：运行此参数很耗时，并且当你没有足够权限时不能使用。
-e 显示以太网统计。此选项可以与-s选项结合使用。
-f 显示外部地址的完全限定域名(FQDN)。
-n 以数字形式显示地址和端口号。
-o 显示拥有的与每个连接关联的进程ID。
-p proto显示proto指定的协议的连接; proto可以是下列任何一个;TCP,uDP,TCPv6或UDPv6。
-r 显示路由表。
-s 显示每个协议的统计数据。
-p 用于指定默认的子网。
-t 显示当前连接卸载状态。interval重新显示选定的统计数据、各个显示间暂停的间隔秒数。按“ctrl+C"组合键停止重新显示统计数据。如果省略，则netstat将打印当前的配置信息一次。
```



## 4.4 arp命令

### 4.4.1 功能

​		arp命令用来显示和修改IP地址与物理地址之间的映射关系，即IP地址到物理地址转换表，该转换表保存在本地arp缓存中。

### 4.4.2 命令格式

​		命令格式如下所示:

```bash
arp -s inet_addr eth_addr [if_addr]
arp -d inet_addr [if_addr]
arp -a [inet_addr] [-N if_addr] [-v]
```

### 4.4.3 命令参数

```
-a 通过询问当前协议数据，显示当前arp项。
-g与-a相同。
-v 在详细模式下显示当前arp项。所有无效项和环回接口上的项都将显示。
inet_addr 指定Internet地址。
-N if_addr 显示if_addr指定的网络接口的arp项。
-d 删除inet_addr指定的主机。inet_addr可以是通配符*,以删除所有主机。
-s 添加主机并且将Internet地址inet_addr与物理地址eth_addr相关联。物理地址是用连字符分隔的6个十六进制字节。该项是永久的。
eth_addr 指定物理地址。
if_addr 如果存在,此项指定地址转换表应修改的接口的Internet地址。如果不存在，则使用第一个适用的接口。
```



## 4.5 tracert命令

### 4.5.1 功能

​		tracert 用于探测源节点到目的节点之间数据报经过的路径。IP 数据报的 TTL 值在每经过一个路由器的转发后减 1，当 TTL=0 时，则向源节点报告 TTL 超时，利用这个特性，可将第一个数据报的 TTL 值置为 1，内部封装无法交付的 UDP 用户数据报，这样，途经的第一个路由器将向源节点报告 TTL 超时，第二个数据报将 TTL 赋值为 2，以此类推，直到到达目的站点或 TTL 达到最大值 255，这样就可以得到沿途的路由器 IP 地址。
### 4.5.2 命令格式

​		命令格式如下所示:

```bash
tracert [-d] [-h maximum_hops] [-j host-1ist] [-w timeout] [-R] [-S srcaddr] [-4] [-6] target_name
```

### 4.5.3 命令参数

```
-d 不将地址解析成主机名。
-h maximum_hops 搜索目标的最大跃点数。
-j host-list 与主机列表一起的松散源路由(仅适用于IPv4)。
-w timeout 等待每个回复的超时时间(以毫秒为单位)。
-R 跟踪往返行程路径(仅适用于IPv6)。
-s srcaddr 要使用的源地址(仅适用于IPv6)。
-4 强制使用IPv4。
-6 强制使用IPv6。
```



## 4.6 route命令

### 4.6.1 功能

​		用来增加、删除或显示本地路由表。

### 4.6.2 命令格式

​		命令格式如下所示:

```bash
route [-f] [-p][-4/-6] command [destination] [MA.SK netmask] [gateway][METRICmetric][IF inte]
```

### 4.6.3 命令参数

```
-f 清除所有网关项的路由表。如果与某个命令结合使用，在运行该命令前，应清除路由表。
-p 与add命令结合使用时,将路由设置为在系统引导期间保持不变。默认情况下，重启不保存路由。忽略所有其他命令，这始终会影响相应的永久路由。Windows95不支持此选项。
-4 强制使用IPv4。
-6 强制使用IPv6。
command 其中之一:
		print打印路由;
		add添加路由;
		delete删除路由;
		change修改现有路由。
destination 指定主机。
MASK 指定下一个参数为网络掩码值。
netmask 指定此路由项的子网掩码值。如果未指定，其默认设置为255.255.255.255,
gateway 指定网关。
inte 指定路由的接口号码。
METRIC 指定跃点数，例如目标的成本
```





# 五、实验内容

## 5.1 ping命令常见用法实验

```bash
ping www.163.com  
#可以看到，ping命令没有带任何参数，返回4个响应。每个响应中，TTL值指明该IP分组可以经过的最大路由器数量。由统计信息可以看出:发送4个请求，收到4个响应，丢失率为0%;最长、最短及平均往返时延，时延越短，说明连通越好。根据这些信息可初步判断本机和目标主机的连通状态。
ping 127.0.0.1
#可经常通过ping 127.0.0.1来检测本地主机是否正确地安装和配置了TCP/IP。
ping -n 20 www.163.com
#通过这个命令可以自己定义发送的回送请求个数，对衡量网络速度很有帮助。比如,命令可以测试发送20个数据包的情况，通过查看返回的平均时间、最长时间、最短时间来衡量网络连通状态。
ping -t www.163.com
#该命令会一直进行下去，直到按“Ctrl+C”组合键停止。若要查看统计信息并继续操作，可以按“Ctr1+Break”组合键。
ping -l 5600 -n 2 www.163.com
#在默认的情况下，Windows 中 ping 发送的数据包大小为32字节，该命令设置回送的请求个数为2，数据包的大小为5600字节，但需要注意该值最大为65500字节。
ping -i 3 www.163.com
#该命令设置ICMP请求报文中的TTL值为3，这个值在每经过一个路由器时会被减1.当被减小到1时，路由器会将该分组丢弃，造成超时。所以，当TTL值太小时，可能会出现本来网络是通的，但由于TTL值耗尽而导致的超时现象，对此要合理判断。
ping -n 1 -r 7 www.163.com
#该命令设置发送Ⅰ个请求分组，最多记录7个路由节点。其中，路由节点的数量最大置为9，若需要查看更多路由节点，可使用tracert命令（后面会介绍)。
#如果多运行几次该命令，可以发现其经过的路由节点不是完全一样的，这是因为每个IP分组都是独立路由的结果。
```



## 5.2 ipconfig命令常见用法实验

```bash
ipconfig
#默认情况下，仅显示绑定到TCP/IP适配器的P地址、子网掩码和默认网关。
ipconfig /all
#显示接口网络详细信息（以无线网卡接口为例)。
ipconfig /release
#释放所有适配器的IP地址
ipconfig /renew
#更新所有适配器，重新获得IP地址。
ipconfig /flushdns
#清空本机DNS缓存
ipconfig /allcompartments /all
#显示有关所有接口的详细信息。
```



## 5.3 netstat命令常见用法实验

```bash
netstat -a
#该命令显示所有连接和监听端口。
netstat -n
#本选项用于以数字形式显示地址和端口号.在测试命令前，也可以先访问一些Web站点,紧接着运行本命令,再观察其中的活动。
netstat -e
#本选项用于显示关于以太网的统计数据。它列出的项目包括传送的数据报的总字节错误数、删除数，以及数据报的数量和广播的数量。这些统计数据既有发送的数据报数也有接收的数据报数量。
#这个参数选项可以用来统计一些基本的网络流量。
netstat -s
#本选项能够按照各个协议分别显示其统计数据，在默认情况下，显示IP、IPv6、ICMP、ICMPv6、TCP、TCPv6、UDP和UDPv6的统计数据。如果应用程序（如Web浏览器）运行速度比较慢，或者不能显示Web页之类的数据，那么就可以用本选项来查看一下所显示的信息，仔细查看统计数据的各行，找到出错的关键字，进而确定问题所在。
netstat -r
#本选项可以显示关于路由表的信息，除了显示有效路由，还显示当前有效的连接。
netstat -p tcp
#显示TCP协议的连接。-p后面的参数也可以是下列任何一个:UDP、TCPv6或UDPv6。
netstat -s -p tcp
#该命令可显示当前TCP连接，并对TCP协议进行统计。
```



## 5.4 arp命令常见用法实验

```bash
arp -a
#显示arp缓存中的IP地址和硬件地址的对应关系。如果不止一个网络接口使用arp，则显示每个接口的arp项。
arp -s 167.56.85.112 00-1a-00-62-c6-08
#该命令将在arp缓存中添加一条静态arp条目。运行该命令后，请查看添加效果。
arp -d 167.56.86.112
#该命令将删除刚刚添加的arp条目，请自行验证。
#另外，在一些Windows系统（如Windows 7)中，当运行arp命令添加静态记录某记录时，有时会被提示“请求的操作需要提升”，这需要使用管理员身份运行命令行。在“开始”处搜到命令行程序后，单击鼠标右键并选择“以管理员身份运行”命令即可。
```



## 5.5 tracert命令常见用法实验

```bash
tracert www.163.com
#tracert后面可跟域名或IP地址，默认的TTL值为30。命令结果清晰地显示了去往目的地所经过的路由，[]前面是IP对应的主机名。从命令执行结果可以看到，封装同一TTL值的数据报被发送三次。
tracert -h 5 60.222.11.27
#该命令设置TTL值为5
```



## 5.6 route命令常见用法实验

```bash
route print
#该命令效果同netstat -r完全一致。
route add 10.0.0.0 mask 255.0.0.0 192.168.182.1 if 19
#该命令将增加一条目的地址为10.0.0.0、掩码为255.0.0.0的路由条目。命令运行后，可使用route print命令查看，可以看到该条目已经被添加到本地路由表中。
route delete 10.0.0.0 mask 255.0.0.0
#运行本命令后，刚刚添加的路由条目被删除。

#需要注意的是，route后面添加命令参数需要以管理员身份运行命令行处理程序
```



# 六、实验结果

## 6.1. ping命令

1.`ping www.163.com` 、`ping 127.0.0.1`

![image-20230309090536777](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230309090536777.png)

2.`ping -n 20 www.163.com`

![image-20230311212109933](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311212109933.png)

3.`ping -t www.163.com`

![image-20230311212252432](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311212252432.png)

4.`ping -l 5600 -n 2 www.163.com`

![image-20230311213226933](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311213226933.png)

5.`ping -i 3 www.163.com`

![image-20230311213331633](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311213331633.png)

6.`ping -n 1 -r 7 www.163.com`



## 6.2 ipconfig命令

1.`ipconfig`

![image-20230311213717971](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311213717971.png)

![image-20230311213726923](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311213726923.png)

2.`ipconfig /all`

![image-20230311213748363](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311213748363.png)

![image-20230311213756474](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311213756474.png)

![image-20230311213804868](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311213804868.png)

![image-20230311213812550](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311213812550.png)

![image-20230311213824398](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311213824398.png)

3.`ipconfig /release`

![image-20230311213849581](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311213849581.png)![image-20230311213849706](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311213849706.png)

4.`ipconfig /renew`

![image-20230311214031276](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311214031276.png)

5.`ipconfig /flushdns`

![image-20230311214127286](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311214127286.png)

6.`ipconfig /allcompartments /all`

![image-20230311214156882](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311214156882.png)

![image-20230311214208913](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311214208913.png)

![image-20230311214218407](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311214218407.png)

![image-20230311214227112](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311214227112.png)

![image-20230311214239161](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311214239161.png)



## 6.3 netstat命令

1.`netstat -a`

![image-20230311214306101](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311214306101.png)

![image-20230311214333083](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311214333083.png)

![image-20230311215020385](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311215020385.png)

![image-20230311215027455](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311215027455.png)

2.`netstat -n`

![image-20230311215050452](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311215050452.png)

![image-20230311215100949](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311215100949-16785426619711.png)

3.`netstat -e`

![image-20230311215123749](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311215123749.png)

4.`netstat -s`

![image-20230311215152716](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311215152716.png)

![image-20230311215206624](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311215206624.png)

![image-20230311215212930](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311215212930.png)

![image-20230311215219326](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311215219326.png)

![image-20230311215224821](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311215224821.png)

5.`netstat -r`

![image-20230311215245494](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311215245494.png)

![image-20230311215253045](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311215253045.png)

6.`netstat -p tcp`

![image-20230311220234410](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311220234410.png)

![image-20230311220241415](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311220241415.png)

7.`netstat -s -p tcp`

![image-20230311220306698](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311220306698.png)

![image-20230311221157744](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311221157744.png)



## 6.4 arp命令

1.`arp -a`

![image-20230311221211750](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311221211750.png)

![image-20230311221220293](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311221220293.png)

2.`arp -s 167.56.85.112 00-1a-00-62-c6-08`

![image-20230311221551124](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311221551124.png)

![image-20230311221557355](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311221557355.png)

3.`arp -d 167.56.85.112`

![image-20230311221647496](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311221647496.png)

![image-20230311221654096](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311221654096.png)



## 6.5 tracert命令

1.`tracert www.163.com`

![image-20230311221811739](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311221811739.png)

2.`tracert -h 5 60.222.11.27`

![image-20230311221928540](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311221928540.png)



## 6.6 route命令

1.`route print`

![image-20230311221946149](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311221946149.png)

![image-20230311222006284](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311222006284.png)

2.`route add 10.0.0.0 mask 255.0.0.0 192.168.182.1 if 17`

![image-20230311222335427](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311222335427.png)

![image-20230311222449711](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311222449711.png)

![image-20230311222505726](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311222505726.png)

3.`route delete 10.0.0.0 mask 255.0.0.0`

![image-20230311222527794](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311222527794.png)

![image-20230311222544921](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311222544921.png)

![image-20230311222550677](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\01 Windows 和Linux操作系统的网络常用命令使用.assets\image-20230311222550677.png)