#!/usr/bin/env python3

from scapy.all import *

def print_pkt(pkt):
   pkt.show()
	
#pkt = sniff(iface='br-b42f0ee147e9', filter='icmp', prn=print_pkt)

#TCP -IP -PORT

#pkt = sniff(iface='br-b42f0ee147e9', filter='tcp && src host 10.9.0.5 && dst port 23', prn=print_pkt)

#128.230.0.0/16

pkt = sniff(iface='br-b42f0ee147e9', filter='net 128.230.0.0/16', prn=print_pkt)
