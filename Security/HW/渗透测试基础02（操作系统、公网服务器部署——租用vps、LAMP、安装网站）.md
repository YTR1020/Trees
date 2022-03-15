# 渗透测试基础02

# 操作系统以及公网服务器部署（操作系统、公网服务器部署——租用vps、LAMP、安装网站、文件权限）

## 操作系统

**unix**（开源、最安全）（C语言）

**Linux**（目前大多数使用）

**DOS**（当时是7.0）（比尔盖茨）

【当时以上无图形界面】

**macOS**（闭源）（基于unix、linux）

**DOS--Windows**（比尔盖茨）（闭源）

**Linux--Android**（java虚拟机在上面跑程序）

**macOS--iOS**（挂起）（推送机制）

【“深度定制”——硬件的缺陷不能用软件来弥补：

游戏机（流畅）和电脑跑游戏机模拟器（卡）速度区别】



**闭源**：黑盒测试（推断程序员会在哪个地方偷懒）

**开源**：白盒测试（**代码审计**--对代码漏洞进行审查）



## 在公网上部署一个服务器—之—租vps

### **背景**：

你有一个idea →需要用程序写出来 →然后放到互联网上（公网上大家都能看到） →需要怎么做？

**租vps**（虚拟服务器）

最开始的时候，一台服务器推荐只安装一个角色（service）

【防止黑客入侵使整台服务器崩掉】----【所以现在发展出了：虚拟化、云计算等】

**虚拟化**：

![220104](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/220104.png)

**云计算**：

![220104-2](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/220104-2.png)



### 租vps：

**vultr.com**

（可以在vultr上租一台vps然后部署相关协议访问国外）



products →＋→cloud compute→可以选择日韩等中国使用来较快→64 bit OS →55GB SSD →centOS →安装



然后会分配给我们一个ip地址

我们需要连接这台服务器：

Windows，需要远程桌面连接（默认情况下用户名administrator）

linux，ssh连接（用户名root）

个人建议使用bitvise连接。



使用bitvise ssh client工具里的bvssh.exe点开。

![image-20220104184959423](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104184959423.png)

把租到的服务器的IP、用户名、密码输入到其中

![image-20220104185054212](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104185054212.png)

点击login，然后就可以使用公网的一个linux的服务器了

![image-20220104185158233](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104185158233.png)


## 在公网上部署一个服务器—LAMP环境

**linux上的操作**：

```
ifconfig  # 查看ip

whoami			# 查看当前登录的用户

# 安装一个网站管理系统——宝塔面板bt.cn
yum install -y wget && wget -O install.sh http://download.bt.cn/install/install_6.0.sh && sh install.sh

# 安装完成后需要复制：
外网面板地址：...
username：...
password：...

# 然后就可以关闭服务器了，可以选择保存or不保存。
```

**然后通过访问刚刚保存的外网面板地址登录宝塔面板的后台，输入用户名和密码。**


然后如下操作**安装LAMP组合**：

![image-20220104191219280](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104191219280.png)



然后还需要**注册一个域名**，使域名指向你服务器的ip地址。

注册域名推荐网站：www.namecheap.com

搜索想要注册的域名 →选择相对便宜的后缀 →注册购买 →注册好后选择管理 

![image-20220104192616534](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104192616534.png)

勾选上，然后进入advanced DNS，将原有的type删除

![image-20220104192713205](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104192713205.png)

然后add new record，比如用www、@解析我们宝塔上得到的外网面板地址：

![image-20220104192841246](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104192841246.png)

![image-20220104192956407](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104192956407.png)

然后进入安装好LAMP的宝塔面板：

进入网站 →添加站点 →输入注册好的域名 →数据库选择MySQL →**记录下数据库的用户名和密码**

![image-20220104193356328](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104193356328.png)

```
数据库用户名：【】
数据库密码：【】
```



**http---->https**

宝塔面板里面给自己的网站安装一个ssl，这样网站会变成https



大多数人是租阿里云的vps去赚钱等。



## 在公网上部署一个服务器—之—安装一个网站

首先需要确保能`ping`到这个网站：

cmd →ping [注册好的域名]

然后在宝塔面板的文件里进行相关操作布置一些网站。

宝塔面板的文件目录 即相当于本地PHPstudy为例的www文件目录

宝塔面板的数据库也是在LAMP安装过程中已安装好的，在phpmyadmin面板。



### 以下是本地演示：

使用phpstudy →Apache 、MySQL →文件根目录即www文件目录 →数据库面板也是使用PHPmyadmin，通过访问127.0.0.1/phpmyadmin/，然后登录root，root。



### 从公网上安装一个网站：

因为搭建网站都是从php上搭建，所以可以搜索php源码，找到想搭建的网站的源代码，下载后down在我们的网站根目录下，然后再访问域名就会出现下载的网站的安装首页。



**关于可读可写权限**：

```
也可以进入www目录下
cd /www
ls
cd wwwroot
chmod 777 -R 刚刚注册的域名

# 每个文件的属性由左边第一部分的 10 个字符来确定
421-rwx 
# 修改文件的权限为777 
[root@localhost ~]# chmod 777 file 
# 修改文件夹以及文件夹内部文件的权限为777
[root@localhost ~]# chmod 777 -R file
```

| 文件类型    |    属主权限 |   属组权限     |   其他用户权限     |
| :---        |    :----:   |     :----:   |               ---: |
| d      | rwx       | r-x   | r-x   |
| 目录文件   | 读 写 执行        | 读 - 执行      | 读 - 执行      |
755

![image-20220104195718738](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104195718738.png)

**本地PHPstudy**：用户名和密码都是root，网站的数据库名需要在PHPmyadmin里新建一个文件名为数据库名。

**宝塔**：记录下来的用户名和密码，数据库名改为宝塔里的数据库名。

然后安装网站完成后，即可登录进入网站前台or后台。



over

**注**：学会安装网站后，学会一些更改前端的操作，然后就可以进行一些网站建设。（猪八戒zbj.com上接单）



如果需要搭建梯子：

租一个vps

搜索trojan节点搭建



## 关于vps

比如**阿里云的vps**：

云服务器ecs

比如企业级的计算型，用于做游戏私服等



**选择vps的时候**：

有些vps厂商会让你选择线路

CN2中国下一代承载网，支持qos（服务质量），让重要数据包先走，比传统的163线路（中国第一代承载网）强。【一些中国人在国外常使用】

CN2GT，便宜，网络拥堵

CN2GIA，贵，质量好

BGP多线机房，自动识别运营商，不同网络自动切换

GCP谷歌公司的线路，贵，质量超级好

AWS亚马逊线路，流量太少

Azure微软线路，慢，中规中矩

PCCW香港线路，贵，网络发达

IPLC国际私有租用线路（专线），极贵，带宽小流量低，不用翻墙直接墙外，不会通过GFW审查
