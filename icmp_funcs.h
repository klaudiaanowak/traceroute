#include <assert.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

u_int16_t compute_icmp_checksum (const void *buff, int length);

