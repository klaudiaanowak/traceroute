#include <arpa/inet.h>

struct ip{
    unsigned int ip_hl:4;  
    u_int32_t saddr;
    u_int32_t daddr;
    };
struct ip*ip_header   = (struct ip*) buffer;
u_int8_t*  icmp_packet = buffer + 4 * ip_header->ip_hl;