#ifndef __ICMP_H
#define __ICMP_H

#define ICMP_HEADER_LEN 8

short compute_icmp_checksum(const u_int16_t *buff, int length);

#endif