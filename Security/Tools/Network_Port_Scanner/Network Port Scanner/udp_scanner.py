# -*- coding: utf-8 -*-
"""
    简单端口扫描程序
    UDP扫描
"""
from scapy.all import *
from scapy.layers.inet import IP, UDP
import threading
import time


def UDP_scan(target,port):
    pkt=IP(dst=target)/UDP(dport=int(port))
    res=sr1(pkt,timeout=2,verbose=0)
    if res==None:
         print(f"[+] Port {str(port)} Is Open\n")
    else:
        print(f"[-] Port {str(port)} Is Close\n")


def udp_scanner(target,portslist):
    print(f"Scanning {target} for Open UDP Ports\n")
    for port in portslist:
        run = threading.Thread(target=UDP_scan,args=(target,port))
        run.start()
        time.sleep(2)
        run.join()  # 设置主线程等待子线程结束


def udp_port_scan(dstip,portslist):
    port_list=[]
    for p in portslist:
        source_port = random.randint(1024, 65535)
        pkt=IP(dst=dstip)/UDP(sport=source_port,dport=p)
        print(pkt.summary())
        result_raw=sr1(pkt,verbose = False,timeout=0.3)#发送三层包，等待接收一个回应
        if result_raw != None:
            if result_raw.haslayer(ICMP):
                icmpfields=result_raw.getlayer(ICMP).fields
                if icmpfields["type"] == 3 and icmpfields["code"] == 3:
                    print("UDP "+str(p)+"端口不可达,close")
                else:
                    print("UDP " + str(p) + "端口被过滤,filtered")
            if result_raw.haslayer(UDP):
                print("UDP " + str(p) + "端口open")
                port_list.append(str(p))
        elif result_raw == None:
            print("UDP "+str(p)+"端口无响应")
    print("%s 开放的UDP端口为:%s\n" % (dstip, port_list))
