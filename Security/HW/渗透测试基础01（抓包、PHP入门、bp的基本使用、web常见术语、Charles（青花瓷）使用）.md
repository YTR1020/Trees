# 渗透测试基础01

# 网络安全行业以及周边介绍（抓包、PHP入门、bp的基本使用、web常见术语、Charles（青花瓷）使用）

>注意：
>1. 不要用学的技术乱来
>2. 不要在一切国内平台发表不当言论
>3. 不要用使用的技术入侵国内任何机构
>4. 利用提供的训练方式
>5. 安装好虚拟机

## 抓包

### 安装

jre-8u261-windows-x64.rar

该工具是一个java的环境

检验安装成功与否：

打开cmd命令行输入java，有东西显示，即表示java环境安装成功。


burpsuite

该工具是一个抓包工具——神器.

如果不带java环境，打不开jar主程序，没有bat文件，需要新建一个文件比如open.bat

右键编辑：

```
java -jar （复制要打开的jar文件名）.jar
```

保存，退出即可，双击就可以打开了。

 
Firefox火狐浏览器（改装过后）

后期使用firefox+burp一起进行抓包



### 了解burpsuite

![image-20211213220359361](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211213220359361.png)

**作用**：

代理【proxy】：默认开启（Intercept is open）关闭后是（Intercept is off）



### 了解火狐浏览器+burp搭配使用（添加代理）

在burpsuite→proxy→intercept→options→确定interface的127.0.0.1:8080是running的

![image-20211213221340582](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211213221340582.png)

![image-20211213221440749](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211213221440749.png)

当然，前提是需要保证电脑的internet选项的局域网设置是正常的

![image-20211213221533143](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211213221533143.png)

然后点解火狐的工具栏→选项→高级→网络→设置

修改为如下：

![image-20211213222017174](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211213222017174.png)

**这样火狐浏览器的流量就会通过brupsuite来进行上网**。


**然后正常情况下这样操作后是没办法访问https的网页如百度，那么如何解决呢**：

在火狐的URL栏里输入：

```
http://burp/
```

然后进入显示如下：

![image-20211213222444945](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211213222444945.png)

点击CA Certificate下载证书

![image-20211213222802395](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211213222802395.png)

然后我们需要在火狐里导入此证书：

工具→选项→高级→证书→查看证书→证书机构→导入→选择刚刚下载的证书文件→确定

![image-20211213223121405](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211213223121405.png)

![image-20211213223055514](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211213223055514.png)

ok解决。



### 尝试抓包百度的数据包

![image-20211213223329126](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211213223329126.png)

burpsuite拦截了数据包



**发现出现乱码**→打开burpsuite的user options→display→字体可以改成宋体 13pt→character sets选use a specific character set→选择GBK或UTF-8

![image-20211213223637167](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211213223637167.png)

![image-20211213223657895](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211213223657895.png)



**理解拦截数据包的内容**

`GET`：百度地址的**提交方式**是GET请求

/sugrec?prod=pc_his&from=pc_web&json=1&sid=35104_31660_34584_35329_35324_26350&hisdata=%5B%7B%22time%22%3A1562517002%2C%22kw%22%3A%22cms%E8%AF%86%E5%88%AB%22%7D%2C%7B%22time%22%3A1562517275%2C%22kw%22%3A%22fikker%200day%22%7D%2C%7B%22time%22%3A1562901914%2C%22kw%22%3A%22xss%E5%B9%B3%E5%8F%B0%22%7D%5D&_t=1639406379664&req=2&sc=eb&csor=0：请求的**数据**

`Host: www.baidu.com`：**地址名**

`User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; rv:52.0) Gecko/20100101 Firefox/52.0`：访问百度时，提交访问浏览器类别、浏览主机**型号**

`Accept-Language: zh-CN,zh;q=0.8,en-US;q=0.5,en;q=0.3`：表示浏览者是中**国**人

`Referer: https://www.baidu.com/`：访问**来路**，就是表示用户在哪里进行的访问。通过`referer`可以识别你是来自哪个平台来进行访问的（比如每个直播app的referer值都是不一样的，从而可供商家统计从哪个直播平台引流的人多）

`Cookie: `BAIDUID=82DEF01D6F2DDF09225229E10038AD8C:FG=1; BIDUPSID=82DEF01D6F2DDF09225229E10038AD8C; PSTM=1561992298; BDUSS=DV5cUpRczg1M2ZmUzNQVkVWaU9Kd3Y0b25qeFI3Qkh1dXFCLWNIOEdUblQ0RmhkSVFBQUFBJCQAAAAAAAAAAAEAAADMlYUDQm95T2ZFeAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAANNTMV3TUzFdZ; sugstore=0; BD_UPN=13314752; BA_HECTOR=8504250h8485a085pt1grem8r0q; BD_HOME=1; H_PS_PSSID=35104_31660_34584_35329_35324_26350：

`cookie`相当于用户登录的信息，用于和浏览器进行对应，从而达到登录状态。被黑客拿到即可被登录用户。



**修改数据包的数据**

wd一般指Word



**网络传输**

一般网络传输的是源代码，信息请求一般以十六进制传输，在网络（网线）里是按01传输的

即：01010101110 →转化成→hex(十六进制) →再转化成→人类可读

（前端代码是通过浏览器渲染之后变成我们看到的样子）



## PHP入门

### 基础相关：

利用工具：PHPstudy

phpstudy的www文件是网站根目录，可以通过访问127.0.0.1进行查看里面文件

**默认标准网页首页命名**：

index.xxx

index.php  index.html .jsp .asp .htm

### 基本格式：

```php
<?php

?>
//包裹在上述结构中的内容才会被当做php执行
```

```php
<?php
echo 'haha nihao';
?>

//echo表示输出
```

```php
<?php

$a=123;
$b="haha";

$c=999;
$d=$a+$c;
echo $d;

//单行注释
/*
这是
多行注释
*/

?>

//设置变量使用$，php是弱类型语言，因此会自动识别变量类型
//单行注释用//
//多行注释用/**/
```

```php
<?php

$a = "haha";
$b = "nihao";
$c = $a.$b; //这里的.叫做粘合
echo $c;
    
?>
```


### 建立一个可以和用户互动的网站

#### 请求

GET——可以获取提交信息，多用于取东西。

POST——多用于提交用户名和密码时。

#### 编写一个简单GET请求的index.php

```php
<?php

$a = $_GET['name'];
$b = $_GET['age'];

echo $a."----".$b;

?>
```

##### 访问127.0.0.1的index.php

此时只能看到首页上显示：----

那么我们就需要GET提交name和age：

```
http://127.0.0.1/index.php?name=xiaoming&age=20

//在php文件里提交参数用：?[参数]
//提交多个参数，粘合参数和参数用：&
//php里输入参数不分先后，可以调换name和age的输入顺序
```

得到首页显示：

```
xiaoming----20
```

此时网站就可以和用户互动了。

#### 编写一个简单有功能的GET请求的index.php

```
<?php

$a = $_GET['name'];
$b = $_GET['age'];

if($b>18)
{
	echo 'chengnian '.$a;
}else{
	echo 'wei cheng nian '.$a;
}

?>
```

##### 访问127.0.0.1的index.php

GET提交name和age：

```
http://127.0.0.1/index.php?name=xiaoming&age=20
```

得到首页显示：

```
chengnian xiaoming
```

#### 编写一个简单POST请求的index.php

```
<?php

$a = $_POST['name'];
$b = $_POST['age'];

echo $a."----".$b;

?>
```

此时按照上述GET请求去首页提交参数时，就无法接收。

但是可以在我们现在使用的火狐工具上强行使用post提交；

或者，使用burpsuite抓包后，在数据包上修改提交参数。

![image-20211226164350386](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211226164350386.png)



## brupsuite的其他功能

### Target

#### site map

![image-20211226172219021](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211226172219021.png)

这一栏是自动保存下来的以前浏览过的一些网站记录



![image-20211226172421399](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211226172421399.png)

此处的request是发送的一些请求，response是它回复的信息

**scope栏不常用，此处略过**



### Proxy

单独版面展示抓到的数据包

#### intercept

![image-20211226172732510](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211226172732510.png)

forward放行前一个数据包，drop把全部数据包都丢弃，intercept is on/off，抓包/放行修改后的所有数据包

#### HTTP history

![image-20211226173009502](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211226173009502.png)

抓包过程中可以看这些数据包分别是按什么顺序提交的，并可以查看相应参数

params判断提交的请求是否有带参数

edited判断是否被修改过

status是http的一个响应：200是正常的，404是没有找到页面

length是该网页大小

MIME type显示类型：html、text（查询时出现的一些联想文本等）、script（特效比如颜色等用js编写的）等

extension后缀名：js、html、php等

**Websockets history略过不用看**

#### options

查看需要通过什么地址才可以让浏览器去使用brupsuite

如果不用火狐浏览器，想要电脑浏览器通过brupsuite，则需要作如下修改：

![image-20211226173852953](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211226173852953.png)



### Spider

爬虫——收集用户信息

可以爬取该网站上的所有信息

![image-20211226173951751](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211226173951751.png)

![image-20211226174005995](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211226174005995.png)

**Scanner没什么用，略过**



### Intruder

暴力破解

![image-20211226174147954](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211226174147954.png)



### Repeater

模拟提交

![image-20211226174226279](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211226174226279.png)

### Decoder

转换编码等，快速加密、解密等

![image-20211226174314897](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20211226174314897.png)

### comparer

对比两个文本的区别



### User options

用户选择的一些默认字体、编码等。



### 也可以抓手机的数据包

比如iPhone：

WiFi → 设置代理 → HTTP代理 → 手动 → 服务器 写使用的电脑的ip地址比如192.168.1.252 → 端口 8080 → 存储即可

一般来说无法抓取https的数据包，brupsuite的证书也是不一样的。



## web常见术语

**刷新**：刷新当前页面

**跳转**：跳到陌生的一个地方

“当用户刷新后，其后台会跳转到一个新的页面”

**GET**：通过地址栏从服务器拿东西。在GET里刷新和跳转没区别。

**POST**：提交表单，送给服务器东西。按下回车键，服务器会以GET方式读取一下当前地址，刷新会再次（重复）提交数据到当前页面

**刷新**：从浏览器取网页的新内容来更新本地缓存，更新的同时保留一些本地变量。

**跳转**：在地址栏输入新的地址，不会更新本地的缓存和变量。



**www**：world wide web万维网（由**web客户端**和**服务器**组成）

**web客户端**：浏览器 web browser

**浏览器**：可以访问网页服务器的web系统，查看html文件（例如IE edge、chrome、Firefox、Opera、Safari）



**request**：向服务器发送一个请求，服务器会返回一个结果给客户端。

**forward**：服务器内部发生重定向。（服务器内部自己发生变化，比如小黄网跳转、发送验证码等）

**redirect**：服务器收到请求后发送一个状态给客户，客户会再次请求，此时url发生了改变。（公司更改网址等）

**url**：统一资源定位器（比如：http://www.baidu.com/index.php 协议+域名+文件）(https://www.baidu.com/s?ie=utf-8&f=8&rsv bp=1&rsv idx=1&tn=baidu&wd=12306 s=文件 ?=get请求 ie=参数名 utf-8=参数值 &=连接符 )



**http**：超文本传输协议

**https**：安全的超文本传输协议

所有的www文件都支持这个标准。http是基于tcp/ip【本身是有漏洞的】传输的。

**web服务器（中间件）**：比如phpstudy的中间件是apache、iis、nginx、tomcat......配合前端和后端的一个协商者

“目标为某个web服务器”：web服务器接收到一个请求，会向客户发送响应消息

**需要掌握**：

1 http是**无连接**的！！！限制每一次的连接请求，每一次一个请求，服务器收到请求之后完成应答，断开连接，节省传输时间。

2 http是**媒体独立**的：只要客户端，服务器都知道这个 数据是干嘛用的，就可以使用http传输。（比如下载东西可以直接用抓包下载）

3 http是**无状态**的：无状态就是没有记忆能力，如果中途中断了，就需要重传。



**http状态码**：在brupsuite可以在status栏里看到——

200 成功访问

301 网页被永久转向了其他的url

404 请求的资源不存在

500 服务器内部错误

"100" : Continue 客户必须继续发出请求

"101" : witching Protocols 客户要求服务器根据请求转换HTTP协议版本

"200" : OK 交易成功

"201" : Created 提示知道新文件的URL

"202" : Accepted 接受和处理，但处理未完成

"203" : Non-Authoritative Information 返回信息不确定或不完整

"204" : No Content 请求收到，但返回信息为空

"205" : Reset Content 服务器完成了请求，用户代理必须复位当前已经浏览过的文件

"206" : Partial Content 服务器已经完成了部分用户的GET请求

"300" : Multiple Choices 请求的资源可在多处得到

"301" : Moved permanently 删除请求数据 

"302" : Found 在其他地址发现了请求数据 

"303" : See Other 建议客户访问其他URL或访问方式 

"304" : Not Modified 客户端已经执行了GET，但文件未变化

"305" : Use Proxy 请求的资源必须从服务器指定的地址得到

"306" : 前一版本HTTP中使用的代码，现行版本中不再使用

"307" : Temporary Redirect 申明请求的资源临时性删除

"400" : Bad Request 错误请求，如语法错误

"401" : Unauthorized 请求授权失败

"402" : Payment Required 保留有效ChargeTo头响应 

"403" : Forbidden 请求不答应

"404" : Not Found 没有发现文件、查询或URl 

"405" : Method Not Allowed 用户在Request-Line字段定义的方法不答应

"406" : Not Acceptable 根据用户发送的Accept拖，请求资源不可访问

"407" : Proxy Authentication Required 类似401，用户必须首先在代理服务器上得到授权 

"408" : Request Time-out 客户端没有在用户指定的饿时间内完成请求

"409" : Conflict 对当前资源状态，请求不能完成

"410" : Gone 服务器上不再有此资源且无进一步的参考地址

"411" : Length Required 服务器拒绝用户定义的Content-Length属性请求

"412" : precondition Failed 一个或多个请求头字段在当前请求中错误 

"413" : Request Entity Too Large 请求的资源大于服务器答应的大小

"414" : Request-URI Too Large 请求的资源URL长于服务器答应的长度

"415" : unsupported Media Type 请求资源不支持请求项目格式

"416" : Requested range not satisfiable请求中包含Range请求头字段，在当前请求资源范围内没有range指示值，请求也不包含If-Range请求头字段

"417" : Expectation Failed 服务器不满足请求Expect头字段指定的期望值

"500" : Internal Server Error 服务器产生内部错误

"501" : Not Implemented 服务器不支持请求的函数

"502" : Bad Gateway 服务器暂时不可用，有时是为了防止发生系统过载

"503" : Service Unavailable 服务器过载或暂停维修

"504" : Gateway Time-out 关口过载，服务器使用另一个关口或服务来响应用户，等待时间设定值较长

"505" : HTTP Version not supported 服务器不支持或拒绝支请求头中指定的HTTP版本


**http数据包解析**：

**请求头Request**：

`GET`：请求类型

`Host`：目标

`user-agent`：用户信息，浏览器是什么等

`accept-language`：国家

`referer`：表示从什么地方来的信息

**响应头Response类型**：

`HTTP/1.1 200 OK`：协议类型

`Content-Type`：文档类型

`Content-Length`：传过来的内容长度（多少个字节）

`Expires`：什么时候文档过期，不再缓存它

`Last-Modified`：最后修改时间

`refresh`：浏览器多长时间后刷新该文档。

`server`：服务器名字

`set-cookie`：是否需要cookie支持



## Charles（青花瓷）使用

抓包软件——更适合手机抓包，也可用于电脑抓包，但相比于brupsuite它不能把数据包停下来。适合分析手机、电脑app。

![image-20220101163140958](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220101163140958.png)

使用8888端口

![image-20220101164618445](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220101164618445.png)

对本地局域网代理服务器改一下。

![image-20220101163234680](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220101163234680.png)

安装后即可进行抓包。但并不能抓到https的数据包。

![image-20220101163513380](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220101163513380.png)

设置为所有的ssl代理都要去抓包

如果需要在远程浏览器或者手机浏览器上安装，需要输入以下地址：

![image-20220101164258603](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220101164258603.png)

然后浏览上述网页去进行安装。



![image-20220101165045084](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220101165045084.png)

![image-20220101165237798](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220101165237798.png)

然后就可以抓包https的数据包。

与brupsuite的区别：以树状图呈现抓包数据，功能如下：

![image-20220101165614843](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220101165614843.png)

![image-20220101165642661](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220101165642661.png)

标黄的网址表示正在传输数据的

**最适合用于在手机上抓包**：

![image-20220101165839345](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220101165839345.png)



需要把socks代理打开

![image-20220101165924608](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220101165924608.png)

socks代理：拦截socks请求。【Python】




