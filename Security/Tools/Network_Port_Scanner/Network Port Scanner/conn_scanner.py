# -*- coding: utf-8 -*-
"""
    简单端口扫描程序
    connect扫描
"""
import socket
import time
import threading


def conn_scan(ip,port):
    scansocket=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    try:
        status=scansocket.connect_ex((ip,port))
        if status==0:
            print(f"[+] Port {str(port)} Is Open\n")
    except:
        print("error")
    scansocket.close()

def conn_scanner(targetIP,portslist):
    print(f"Scanning {targetIP} for Open TCP_CONN Ports\n")
    for i in portslist:
        run=threading.Thread(target=conn_scan,args=(targetIP,i))
        run.start()
        run.join()

