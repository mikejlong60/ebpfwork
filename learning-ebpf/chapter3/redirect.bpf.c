#include <linux/bpf.h>
#include "bpf_helpers.h"
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>

#define REDIRECT_IP 0x81170C3E // 129.23.12.62 in hex
#define REDIRECT_PORT 9009

SEC("prog")
int redirect_packets(struct __sk_buff *skb) {
    void *data = (void *)(long)skb->data;
    void *data_end = (void *)(long)skb->data_end;

    struct ethhdr *eth = data;
    if ((void *)(eth + 1) > data_end)
        return BPF_DROP;

    if (eth->h_proto != bpf_htons(ETH_P_IP))
        return BPF_PASS;

    struct iphdr *ip = data + sizeof(*eth);
    if ((void *)(ip + 1) > data_end)
        return BPF_DROP;

    if (ip->protocol != IPPROTO_TCP)
        return BPF_PASS;

    struct tcphdr *tcp = (void *)ip + sizeof(*ip);
    if ((void *)(tcp + 1) > data_end)
        return BPF_DROP;

    // Modify the destination IP and port
    ip->daddr = bpf_htonl(REDIRECT_IP);
    tcp->dest = bpf_htons(REDIRECT_PORT);

    // Recalculate checksums
    ip->check = 0;
    ip->check = bpf_csum_diff(0, 0, (__be32 *)ip, ip->ihl * 4, 0);
    tcp->check = 0;
    tcp->check = bpf_csum_diff(0, 0, (__be32 *)tcp, sizeof(*tcp), 0);

    return BPF_OK;
}

char __license[] SEC("license") = "GPL";

