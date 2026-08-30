import subprocess
import locale
from scapy.all import *
import ipaddress

def ping(target_ip, count=4, interval=1, ttl=64, packet_size=56):
    try:
        # 获取系统默认编码
        default_encoding = locale.getpreferredencoding()

        # 拼接Windows ping命令
        command = ["ping", target_ip, "-n", str(count), "-w", str(int(interval * 1000)), "-i", str(ttl), "-l", str(packet_size)]
        result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        # 打印输出结果
        print(result.stdout.decode(default_encoding, errors='ignore'))
    except Exception as e:
        print(f"Error: {e}")



def host_scan(net):
    net = ipaddress.ip_network(net)
    ip_list = []
    for ip in net.hosts():  # 迭代可用的主机地址
        id_no = random.randint(1, 65535)
        pkt = IP(dst=str(ip))/ICMP(id=id_no,seq=1)
        #print(pkt.summary())
        result_raw=sr1(pkt,timeout=0.2, verbose=False)
        if result_raw == None:
            print(str(ip)+"不在线")
        elif result_raw != None:
            ip_list.append(str(ip))# ip默认类型未IPv4adress，需转换为str类型
            print(str(ip)+"在线")
    print("在线主机如下：\n%s"%ip_list)
