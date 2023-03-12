# 一、实验名称

上机任务2：Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信



# 二、实验者、实验时间

实验者：信息安全2102尹若彤（3201603102）

实验时间：2023年3月9日



# 三、实验目的

1. 熟练并掌握Packet Tracer常用功能及使用方法。
2. 掌握通过Console端口对交换机进行配置的方法。
3. 理解并掌握交换机初始配置。
4. 掌握在局域网内如何把两台计算机利用对等网方式进行连接。



# 四、实验原理

## 4.1 Packet Tracer常用功能及使用方法

### 4.1.1 基本界面

![image-20230311215532224](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230311215532224.png)

>图中所标示区域解释如下：
>
>（1）菜单栏。此栏中有文件、选项和帮助选项，我们在此可以找到一些基本的命令，如打开、保存、打印和选项设置等。
>
>（2）主工具栏。此栏提供了菜单栏中命令的快捷方式。
>
>（3）逻辑/物理导航栏。我们可以通过此栏中的按钮完成逻辑工作区和物理工作区之间的转换。
>
>（4）工作区。中间的空白处为工作区，在此区域中我们可以创建网络拓扑、监控模拟过程、查看各种信息和统计数据。
>
>（5）通用工具栏。此栏提供了常用的工作区工具，包括：选择、整体移动、备注、删除、查看、添加简单数据包和添加复杂数据包等。
>
>（6）设备类型选择栏。此栏包含不同类型的设备，如路由器、交换机、HUB、无线设备、连线、终端设备和网云等。
>
>（7）具体设备选择栏。此栏包含不同设备类型中不同型号的设备，它随着设备类型选择栏中的选择级联显示。
>
>（8）实时/模拟导航栏。我们可以通过此栏中的按钮完成实时模式和模拟模式之间的转换。

### 4.1.2 选择并添加设备

在设备类型选择栏中选择上面的网络设备，下面会级联显示出各种网络设备。选择路由器，这时旁边的具体设备选择栏中会显示各种型号的路由器，用鼠标单击想添加的路由器，松开鼠标移到工作区单击，即可将该路由器添加到工作区中。当然，也可以通过按住Ctrl键再单击来连续添加设备，提高效率。

### 4.1.3 连接设备

选取合适的线型将设备连接起来。可以根据设备间的不同接口选择特定的线型来连接，选择合适的线型后，在设备上单击，会出现端口选择弹出式菜单，选择想连接的端口，然后在另一台设备上做同样的操作，就可以将两台设备连接起来了。当然，如果只是想快速地建立网络拓扑而不考虑线型选择，可以选择自动连线（但并不推荐这么做），这时系统将自动选择端口连接。当鼠标移到所选择的线型上方时，会对该线型有简单提示，下面做一些说明。

各种类型的线，依次为自动选线、控制线、直通线、交叉双绞线、光纤、电话线、同轴电缆、DCE、DTE、一拖八控制线、物联网电缆线、USB线。其中DCE和DTE是用于路由器之间的连线，在实际应用中，你需要把DCE和一台路由器相连，DTE和另一台路由器相连。在软件中，你只需选一根就可以，若选了DCE线，则和这根线相连的路由器为DCE，配置该路由器时需配置时钟频率。常见的双绞线连接中，路由器和计算机相连用交叉双绞线，交换机和交换机相连也会用交叉双绞线。

连接完成后，可以看到各线缆两端有不同颜色的圆点，它们表示的含义如表所示：

![image-20230311215857998](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230311215857998.png)

### 4.1.4 配置设备

在工作区中单击路由器，打开设备配置对话框。

（1）切换到Physical选项卡，如图所示。Physical 选项卡用于添加端口模块，每选择一个模块，下方会显示出该模块的说明信息。在实物面板视图上可以看到空槽，首先单击面板上的电源按钮，关闭电源，其次用鼠标左键单击并按住该模块，将其拖到空槽上，即可添加模块，最后打开电源按钮（路由器上常用的串口模块有WIC-1T、WIC-2T等）。

![image-20230311215959241](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230311215959241.png)

（2）切换到Config选项卡，如图所示：

![image-20230311220047843](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230311220047843.png)

Config选项卡提供了简单配置路由器的图形化界面，当进行某项配置时下面会显示相应的命令。这是Packet Tracer中的快速配置方式，主要用于简单参数的配置，比如接口的IP地址等，实际设备中没有这样的方式。

图中配置FastEthernet 0/0端口的IP地址和子网掩码为192.168.1.1和255.255.255.0。

对应的CLI选项卡则是在命令行模式下对网络设备进行配置的，这种模式和实际路由器的配置环境相似。

CLI选项卡为命令行界面，我们可以在其中输入配置命令，这也是主要工作。Attributes选项卡用于显示设备的一些参数。

### 4.1.5 实时/模拟导航

默认为实时模式，不显示包轨迹。当需要观察包的运动轨迹时，就需要切换到模拟模式下。此时会出现Event List对话框，该对话框显示当前捕获到的数据包的详细信息，包括持续时间、源设备、目的设备、协议类型和协议详细信息，要进一步了解协议的详细信息，可以单击协议类型信息，也可以单击具体设备上显示出的包，得到很详细的OSI模型信息和各层PDU。

可以编辑过滤特定协议包，并通过单击上一步[插图]、下一步[插图]及播放[插图]按钮等，反复观看，这对学习者是很有好处的，使大家可以更清晰地观察特定协议包的封装及其走向。

图选择只观察ICMP包。另外，Show All/None按钮可以帮助更有效地选择协议。

![image-20230311220204986](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230311220204986.png)

### 4.1.5 Cisco设备基本配置模式

配置设备时，不同模式下可以执行的命令不同，比如要配置一个接口时，须进入接口配置模式，无法在用户模式下对一个接口进行配置。

网络设备的接口，也称为端口，本书不做区别。

以路由器为例，每次进入路由器时，首先进入用户模式。在用户模式下，不能对路由器进行修改，甚至无法查看某些信息。需要对路由器进行其他操作时，只能先进入到特权模式，然后再根据需要进入其他模式进行操作，如图所示。

![image-20230311223147528](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230311223147528.png)

>1.用户模式
>
>交换机启动完成后按 Enter 键，首先进入的就是用户模式，在此模式下用户将受到极大的限制，只能查看一些统计信息。
>
>2.特权模式
>
>在用户模式下输入enable（可简写为en）命令，可以进入特权模式，用户在该模式下可以查看并修改Cisco设备的配置。
>
>3.全局配置模式
>
>在特权模式下输入config terminal（可简写为conf t）命令，可以进入全局配置模式，用户在该模式下可修改交换机的全局配置，如主机名等。
>
>4.接口配置模式
>
>在全局配置模式下输入interface fastethernet 0/1（可简写为int f0/1），可以进入接口配置模式，在这个模式下所做的配置都是针对f0/1接口进行的，如设定IP等。
>
>5.线路配置模式
>
>在全局配置模式下输入line vty 0 5，可以进入设备的线路配置模式，进行虚通道的设置，如远程登录。



## 4.2 交换机的初始配置及其Console端口配置

### 4.2.1 基本概念

交换机初始配置会进行一些初始的参数配置,如密码、管理IP等。启动新买的交换机时,NVRAM为空，会询问是否进行初始配置。也可以后期在特权模式下使用setup命令主动行初始配置。

交换机并不配备专门的输入输出设备，当配置一台新买的交换机时，第一次必须通过Console端口来进行。Console端口是一个串行接口，需要用串行线将其与计算机连接起来再利用超级终端软件对交换机进行配置，计算机相当于是交换机的输入设备。

其他配置方式包括下列几种：

(1)Telnet方式。通过Telnet方式远程登录到设备进行配置，详见应用层Telnet实验。

(2)Web页面配置。通过一些网管软件或Web方式对交换机进行远程配置，这样使用方便，但是有的命令无法在 Web页面中执行。

(3）通过TFTP服务器实现对配置文件的保存、下载和恢复等操作，简单方便。在Packet Tracer中，可以直接在CLI选项卡中进行配置。



## 4.3 双机直连通信

### 4.3.1 基本概念

双机直连通信即：经常需要在两台计算机之间传输和共享资料，可采用双绞线直接插入网卡的方式将两台计算机连接起来，以达到资源共享的目的。

网卡是计算机局域网中最重要的连接设备，计算机主要通过网卡连接网络。在网络中，网卡的工作是双重的：一方面它负责接收网络上传过来的数据包，解包后，将数据通过主板上的总线传输给本地计算机；另一方面它将本地计算机上的数据打包后送入网络。网卡与网络进行连接,必须有一个接口使网线通过它与其它计算机网络设备连接起来，常见的接口主要有以太网的RJ45接口等。

网卡的物理地址（MAC地址)：为了标识局域网中的主机，需要给每台主机上的网卡分配一个唯一的通信地址，即物理地址，也称为硬件地址或MAC地址。要在计算机上查看网卡的MAC地址，可在命令提示符下输入“ipconfig/all”命令。

以太网卡的MAC地址由48位二进制（6字节）组成。其中，前3字节（前24位）为IEEE分配给网络设备生产厂家的厂商代码，后3字节（后24位）为厂商分配给网卡的编号。MAC地址通常用12个十六进制数来表示，每两个十六进制数之间用冒号或横线隔开，格式如“48:5D:60:78:52:0C”或“48-5D-60-78-52-OC”。MAC地址具有全球唯一性，网卡在出厂前，其MAC地址已被烧录到ROM中，所以一般无法更改。



# 五、实验内容

## 5.1 交换机的初始配置及其Console端口配置

### 5.1.1 实验内容

使用PC机通过交换机console口对交换机进行初始配置。

### 5.1.2 实验流程

![image-20230311220741590](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230311220741590.png)



## 5.2 双机直连通信

### 5.2.1 实验内容

将两台 PC 直接连接构成一个网络。注意：直接连接需使用交叉线。

### 5.2.2 实验流程

总体分为以下几个步骤：选择设备-->连交叉线-->配置IP-->ping测试。



# 六、实验结果

## 6.1 交换机的初始配置及其Console端口配置

### 6.1.1 布置拓扑，将计算机和交换机通过串行线连接起来。

![image-20230312134018117](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312134018117.png)

准备一台PC机，一台以太网二层交换机，Console线（这里选择控制台连线-配置线）

![image-20230312134036151](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312134036151.png)

选择端口时PC中选择的是RS 232接口，Switch中选择console接口。



### 6.1.2 通过Console端口对交换机进行配置。

![image-20230312134051258](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312134051258.png)

如图所示，单击主机，点开主机的Desktop选项卡，点击终端Terminal。

![image-20230312134120500](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312134120500.png)

点击OK按钮。

![image-20230312134203837](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312134203837.png)

进入终端命令行后按回车按键后开始。



输入enable进入特权模式，此处由于没有设置密码，所以直接进入。之后可以用`configure terminal` 、`interface f0/1`、`exit`等命令在交换机的几种操作模式间切换，使用`end`命令可以直接退回到特权模式。

![image-20230312135026474](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312135026474.png)



### 6.1.2 对交换机进行初始配置

在特权模式下输入 `setup` 命令进行初始配置。

![image-20230312135216739](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312135216739.png)

这里配置交换机管理端口为 VLAN 1、IP地址为192.168.1.1/24、交换机名称为jiaoxue_1、一般用户密码为cisco1、特权用户密码为cisco2、远程登录密码为ciscovir。

![image-20230312135250130](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312135250130.png)

![image-20230312135317670](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312135317670.png)

配置交换机名称为`jiaoxue_1`

![image-20230312135405988](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312135405988.png)

配置特权用户密码`cisco2`，该密码将被加密

![image-20230312135558429](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312135558429.png)

配置一般用户密码`cisco1`，改密码不加密，用在一些老版本中

![image-20230312135644957](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312135644957.png)

配置虚拟终端密码`ciscovir`，用于远程登录

![image-20230312135809800](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312135809800.png)

配置端口，二层交换机默认所有端口为VLAN 1，这里配置为`VLAN 1`

![image-20230312135838338](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312135838338.png)

![image-20230312135853918](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312135853918.png)

给VLAN 1配置一个IP地址`192.168.1.1`，可通过这个地址对交换机进行登录管理

![image-20230312140020165](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312140020165.png)

按默认配置，直接回车

![image-20230312140125851](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312140125851.png)



可以看到以下参数

![image-20230312140224812](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312140224812.png)

（secret密码是加密显示的，password密码不加密）

![image-20230312140308734](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312140308734.png)

意思是选择默认`[2]`（保存退出），直接回车即可

![image-20230312140406284](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312140406284.png)

已保存配置信息。

之后如果`reload`重启交换机，输入`enable`进入特权用户模式时，会提示输入密码，输入之前设置好的密码即可进入特权用户模式；`show startup-config`可以查看当前的配置信息；输入`erase`命令可以清除交换机配置信息，并回车`confirm`确定。

最后我们点开Switch交换机可以看到，PC上配置交换机，配置信息会同步到交换机上。当我们第一次配置交换机的时候，需要用控制台来配置。

![image-20230312140943745](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312140943745.png)

![image-20230312141101676](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312141101676.png)



>题外话：
>
>交换机初始配置会进行一些初始的参数配置，如密码、管理P等。启动新买的交换机时，NVRAM为空,会询问是否进行初始配置。也可以后期在特权模式下使用setup命令主动进行初始配置。
>
>交换机并不配备专门的输入输出设备,当配置一台新买的交换机时，第一次必须通过Console端口来进行。Console端口是一个串行接口,需要用串行线将其与计算机连接起来，再利用超级终端软件对交换机进行配置，计算机相当于是交换机的输入设备。



## 6.2 双机直连通信

### 6.2.1 选择设备

选择两个终端设备

![image-20230312142543987](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312142543987.png)



### 6.2.2 连交叉线

PC与PC直接连接需要用交叉线，在设备中选择线缆，在型号选择里面选择交叉线（黑色的虚线）。交叉线连接时，对两台PC来说需要选择FastEthernet0接口。

![image-20230312142802106](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312142802106.png)



### 6.2.3 配置IP

点击PC0，会弹出PC0的设置界面，点击配置Config选项卡

![image-20230312142921026](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312142921026.png)

左侧点击FastEthernet0

![image-20230312142936347](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312142936347.png)

在IP配置的填写下面两项，IP地址填`192.168.0.1`，子网掩码填`255.255.255.0`

![image-20230312143050166](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312143050166.png)

对PC1也这样配置，不过IP地址填`192.168.0.2`，子网掩码填`255.255.255.0`。填完可以点关闭，是自动保存的
![image-20230312143127955](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312143127955.png)



### 6.2.4 ping测试

点击PC0，会弹出PC0的设置界面，点击桌面Desktop选项卡，点击command prompt命令提示符，出现命令提示符之后，输入`ping 192.168.0.1`回车

![image-20230312143257158](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312143257158.png)

![image-20230312143519496](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312143519496.png)

结果如上表示本机IP配置正常。

然后测试与PC1通信是否正常。输入`ping 192.168.0.2`回车。

![image-20230312143639611](D:\A-Study\Write\Typora\Typora\Typora\Notes\typoraNote\计算机网络与安全实验\02 Packet Tracer常用功能及使用方法，交换机的初始配置及其Console端口配置；双机直连通信.assets\image-20230312143639611.png)

结果如上表示与PC1通信正常。

同样的方法也可以测试PC1。

以上，配置完毕。
