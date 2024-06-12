#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <netinet/in.h>

SEC("xdp_redirect")
int xdp_redirect_func(struct xdp_md *ctx) {
    void *data_end = (void *)(long)ctx->data_end;
    void *data = (void *)(long)ctx->data;

    struct ethhdr *eth = data;
    if ((void *)eth + sizeof(*eth) > data_end)
        return XDP_PASS;

    if (eth->h_proto != htons(ETH_P_IP))
        return XDP_PASS;

    struct iphdr *ip = data + sizeof(*eth);
    if ((void *)ip + sizeof(*ip) > data_end)
        return XDP_PASS;

    if (ip->protocol != IPPROTO_UDP)
        return XDP_PASS;

    struct udphdr *udp = (void *)ip + sizeof(*ip);
    if ((void *)udp + sizeof(*udp) > data_end)
        return XDP_PASS;

    // Change the destination IP address and port
    ip->daddr = htonl(129 << 24 | 23 << 16 | 12 << 8 | 62);
    udp->dest = htons(9009);

    // Update the IP and UDP checksums
    ip->check = 0;
    ip->check = bpf_csum_diff(0, 0, (__be32 *)ip, ip->ihl * 4, 0);

    udp->check = 0;
    udp->check = bpf_csum_diff(0, 0, (__be32 *)udp, sizeof(*udp), 0);

    return XDP_TX;
}

char _license[] SEC("license") = "GPL";
