#include <arpa/inet.h>
#include <cassert>

#define ICMP_HEADER_LEN 8

u_int16_t compute_icmp_checksum(const u_int16_t *buff, int length);
