#include <arpa/inet.h>

struct icmp{
    u_int8_t icmp_type;
    u_int8_t icmp_code; 
    };
struct ip*   ip_header   = (struct ip*) buffer;
u_int8_t*icmp_packet = buffer + 4 * ip_header->ip_hl;
struct icmp* icmp_header = (struct icmp*) icmp_packet