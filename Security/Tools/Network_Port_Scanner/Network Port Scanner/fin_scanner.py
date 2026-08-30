# -*- coding: utf-8 -*-
"""
    简单端口扫描程序
    FIN扫描
"""
from scapy.layers.inet import IP, TCP
from scapy.sendrecv import sr, sr1
import threading
import time

'''
适用于Linux设备
通过设置flags位为'FIN',不回复则表示端口开启，回复并且回复的标志位为RST表示端口关闭
'''

def fin_scan(targetIP,port):
    p = IP(dst=targetIP) / TCP(dport=int(port), flags="F")
    ans = sr1(p, timeout=1, verbose=0)
    if sr1(p, timeout=1, verbose=0) == None:
        print(f"[+] Port {str(port)} Is Open\n")
    elif ans != None and ans[TCP].flags == 'RA':
        # ans.display()
        # print(f"[-] Port {str(port)} Is Close\n")
        pass

def fin_scanner(targetIP,portslist):
    print(f"Scanning {targetIP} for Open TCP_FIN Ports\n")
    for p in portslist:
        run = threading.Thread(target=fin_scan,args=(targetIP,p))
        run.start()
        run.join()  # 设置主线程等待子线程结束


