# 渗透测试基础03

# 踪迹隐藏以及加密通信了解（CDN加密通信、个人信息泄露问题、硬盘存储原理、Gpg加密、EFS加密、软件加壳）



如何保护我们的真实ip

**CDN**



## 个人防护 加密通信

**CDN**

**cloudflare.com——免费cdn**

功能：防止真实ip被人发现、流量缓存。

举个栗子：百度服务器要连接到ISP运营商，运营商下有各省来连接，各省下又有各市......这时需要在每省处有一个CDN服务器，向百度公司发送请求，让百度将流量（包括更新的内容）进行下发到各个CDN服务器，并将百度的一些缓存放在CDN服务器里。这样效率高且使百度本尊安全。



### 个人信息泄露问题：

**网络方面**：
大部分人都会暴露自己的公网ip
暴露ip就会暴露通信内容
加密（vpn）--虚拟专用网络--企业间用于通信

**个人软件方面**：
IM
qq,wx
某些软件后台自动上传你电脑的文件到服务器
某些杀毒软件：可以名正言顺对你电脑进行扫描，搜集信息
某些国产浏览器
(chrome firefox safari)
【记得退出的时候清理痕迹】
输入法

**个人电脑方面**：
你自己的操作系统（盗版）
邮件客户端 outlook exchange foxmail.....
（多用虚拟机！！！！！）

**网络通信**：
SMS短信--->2G = 不加密（3-5G加密）
伪基站
【Tor洋葱路由器】



## 硬盘存储原理：

硬盘里有磁盘，芯片等。


机械硬盘理论上覆盖3次才能彻底忘记。

覆盖才是真正的忘记。

![image-20220104212801246](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104192841246.png)

![image-20220104212907896](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104212907896.png)

清空回收站：

![image-20220104213013099](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104213013099.png)

固态硬盘直接覆盖就没了。



## 加密：Gpg加密

开源

https://www.gnupg.org/download/index.html

**下载**

![image-20220104213231696](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104213231696.png)



并发送给**虚拟机**。

在虚拟机和本机上**安装**：

![image-20220104213616507](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104213616507.png)

**打开GTA**:

![image-20220104213812398](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104213812398.png)

![image-20220104213832119](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104213832119.png)

然后输入一个密码：

![image-20220104213851847](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104213851847.png)



**公钥(public key)**加密，**私钥(private key)**解密
公钥可以随便在互联网上传输
（私钥一定不能泄露）

export keys**导出本机和虚拟机的公钥**：

![image-20220104214350446](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104214350446.png)

![image-20220104214443521](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104214443521.png)



把**本机的公钥传输到虚拟机上**：

![image-20220104214601386](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104214601386.png)

然后在虚拟机上**import导入**本机的公钥：

![image-20220104214741879](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104214741879.png)

然后虚拟机就可以给本机发送消息并选择**用本机的公钥进行加密**：

![image-20220104214827417](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104214827417.png)

![image-20220104214901152](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104214901152.png)

然后得到：

![image-20220104214921104](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104214921104.png)

此时虚拟机无法自己解密（因为没有本机的公钥）

复制内容后在本机上输入本机私钥密码后进行解密：

![image-20220104215113301](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104215113301.png)

![image-20220104215154863](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104215154863.png)

同理，把虚拟机的公钥导入给主机后，主机也可以给虚拟机发送加密信息并由虚拟机解密。



**如果pc2想发送一条只有pc1才可以看的文字，那么pc2需要导入pc1的公钥。**

**如果要pc1和pc2双向通信，必须两边都拥有对方的公钥。**



**文件加密**：

![image-20220104215418113](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104215418113.png)

open打开文件：

![image-20220104215449190](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104215449190.png)

encrypt加密：

![image-20220104215526337](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104215526337.png)

得到：![image-20220104215539358](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104215539358.png)

发送到有私钥的虚拟机上，然后解密使用。类似于压缩包使用。



## EFS文件加密：

只能windows使用

**证书加密**（也非常安全）

你的磁盘必须为**NTFS格式**才可以使用EFS文件加密

![image-20220104215927596](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104215927596.png)



开始 →mmc →控制台

![image-20220104220034487](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104220034487.png)

![image-20220104220101183](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104220101183.png)

![image-20220104220113397](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104220113397.png)

然后对某文件进行证书加密然后应用：

![image-20220104220215151](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104220215151.png)

![image-20220104220228843](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104220228843.png)

然后到个人证书里刷新可见：

![image-20220104220404627](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104220404627.png)

密钥备份：

![image-20220104220519510](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104220519510.png)

![image-20220104220530896](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104220530896.png)

一直下一步。

然后删除证书：

![image-20220104220606935](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104220606935.png)

然后注销后重新登录，原文件就无法打开。

除非将私钥公钥证书都重新导入回去，才可打开。



## **软件加壳**

壳可以加密流量？no

通信流量的加密必须两边都认同加密方法才可以实现。



kali要运行在vmware上。

![image-20220104222731059](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220104222731059.png)手机版本 kali

**注**：我们所有实验都在虚拟机完成，不要和本机有任何来往，这是不好的习惯
