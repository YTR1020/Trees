# Tools

信息收集工具的使用

## Windows本地信息搜集：

1. 查看自己的身份

```
whoami
```

2. 获取当前域的信息

```
whoami /all
```

3. 查看详细ip信息

```
ipconfig /all
```

4. 查看arp表

```
arp -a     
```

5. 查看操作系统信息

```
systeminfo
```

6. 查看cpu型号

```
echo %PROCESSOR_ARCHITECTURE%
```

7. 查看安装软件和版本信息

```
wmic product get name,version
```

8. 查看补丁列表


wmic qfe get Caption,Description,HotFixID,InstalledOn  #查看补丁列表

net user  #查看本地用户

net session  #显示本地和远程的会话

wmic process list brief   #查看进程

net view   #查看内网的共享
