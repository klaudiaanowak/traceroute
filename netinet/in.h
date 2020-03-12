#include <arpa/inet.h>

struct sockaddr_in {
    sa_family_t     sin_family;
    in_port_t sin_port;
    struct in_addr  sin_addr;
    // tutaj zera
    }

charsender_ip_str[20]; 
inet_ntop (  
    AF_INET,   
    &(sender.sin_addr), 
    sender_ip_str,   
    sizeof(sender_ip_str));