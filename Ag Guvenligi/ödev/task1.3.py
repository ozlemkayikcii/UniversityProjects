#!/usr/bin/env python3
from scapy.all import *
import sys

# Task 1.3 

a = IP()
a.dst = '8.8.4.4'
a.ttl = int(sys.argv[1])
b = ICMP()
#send(a/b)
a=sr1(a/b)
print("source = " , a.src)
