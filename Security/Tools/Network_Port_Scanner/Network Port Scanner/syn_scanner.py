# -*- coding: utf-8 -*-
"""
    简单端口扫描程序
    SYN扫描
"""
import logging
import threading
logging.getLogger("scapy.runtime").setLevel(logging.ERROR)
from scapy.layers.inet import IP, TCP, UDP, ICMP
from scapy.all import *
import time

arget = "192.168.83.137"
# target = "192.168.10.35"
def syn_scan(port):
    sport = RandShort()
    pkt = sr1(IP(dst=target) / TCP(sport=sport, dport=port, flags="S"), timeout=1, verbose=0)
    if pkt != None:
        if pkt.haslayer(TCP):
            if pkt[TCP].flags == 18:
                print(f"[+] Port {str(port)} Is Open\n")

def syn_scanner(target,portslist):
    print(f"Scanning {target} for Open TCP_SYN Ports\n")
    for x in portslist:
        run = threading.Thread(target=syn_scan, args=(x,))
        run.start()
        run.join()  # 设置主线程等待子线程结束

def syn_scan_final(dstip,portslist):
    #发送SYN包，并且等待回应##############目的端口可以为元组(lport,hport)##flag为SYN（S）#########
    port_list = []
    for p in portslist:
        source_port = random.randint(1024, 65535)
        pkt = IP(dst=dstip)/TCP(sport=source_port, dport=p,flags="S")
        print(pkt.summary())
        result_raw = sr1(pkt, verbose=False, timeout=0.3)  # 发送三层包，等待接收一个回应
        if result_raw != None:
            if result_raw.getlayer(TCP).fields["flags"] == 18:
                port_list.append(str(p))
                print("TCP " + str(p) + "端口可达,open")
        elif result_raw == None:
            print("TCP " + str(p) + "端口无响应")
    print("%s 开放的TCP端口为:%s\n" % (dstip,port_list))