# -*- coding: utf-8 -*-
"""
    简单端口扫描程序
    主程序
"""
from conn_scanner import conn_scanner
from syn_scanner import syn_scanner
from fin_scanner import fin_scanner
from udp_scanner import udp_scanner, udp_port_scan
from ping import ping, host_scan


def menu():
    print('''
    ----菜单

    --------1. TCP_CONN扫描
    --------2. TCP_SYN扫描
    --------3. TCP_FIN扫描
    --------4. UDP扫描
    --------5. ping
    --------6. 显示菜单
    --------7. 退出
    ''')


def main():
    targetIP = input("请输入目标IP：")
    portslist = [21, 22, 23, 80, 123, 135, 139, 443, 445, 8080]
    menu()
    while True:
        try:
            options = int(input("请输入扫描方式："))
        except:
            continue
        if options == 1:
            conn_scanner(targetIP, portslist)
        elif options == 2:
            syn_scanner(targetIP, portslist)
        elif options == 3:
            fin_scanner(targetIP, portslist)
        elif options == 4:
            udp_port_scan(targetIP, portslist)
        elif options == 5:
            net = input("Net/mask>>>")
            host_scan(net)
        elif options == 6:
            menu()
        elif options == 7:
            break
        else:
            continue


main()
