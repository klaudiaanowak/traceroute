#ifndef __ICMP_H
#define __ICMP_H

#define ICMP_HEADER_LEN 8

short compute_icmp_checksum( u_int16_t *addr, register int len, u_int16_t csum);

#endif