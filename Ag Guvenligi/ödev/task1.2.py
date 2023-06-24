#!/usr/bin/env python3
# Task 1.2 ----------------------------------------------------
from scapy.all import *
a = IP()
a.dst = '1.2.3.4'
b = ICMP()
p = a/b

ls(a)
send(p,iface='br-b42f0ee147e9')
