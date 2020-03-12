#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include "icmp_funcs.h"
using namespace std;

void print_as_bytes (unsigned char* buff, ssize_t length)
{
	for (ssize_t i = 0; i < length; i++, buff++)
		printf ("%.2x ", *buff);	
}


int main()
{
	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

	for (;;) {
		
		struct sockaddr_in 	sender;	
		socklen_t 			sender_len = sizeof(sender);
		u_int8_t 			buffer[IP_MAXPACKET];

		ssize_t packet_len = recvfrom (sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
		if (packet_len < 0) {
			fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
			return EXIT_FAILURE;
		}

		char sender_ip_str[20]; 
		inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));
		printf ("Received IP packet with ICMP content from: %s\n", sender_ip_str);

		struct ip* 			ip_header = (struct ip*) buffer;
		ssize_t				ip_header_len = 4 * ip_header->ip_hl;

		printf ("IP header: "); 
		print_as_bytes (buffer, ip_header_len);
		printf("\n");

		printf ("IP data:   ");
		print_as_bytes (buffer + ip_header_len, packet_len - ip_header_len);
		printf("\n\n");
	}

	return EXIT_SUCCESS;
}


// struct sockaddr_in recipient;
// bzero (&recipient, sizeof(recipient));
// recipient.sin_family = AF_INET;
// inet_pton(AF_INET, "adres_ip", &recipient.sin_addr);

void send(sockaddr_in &recipient, int sockfd, int ttl){
 icmp header;
header.icmp_type = ICMP_ECHO;
header.icmp_code = 0;
header.icmp_hun.ih_idseq.icd_id = pid;
header.icmp_hun.ih_idseq.icd_seq = ttl;
header.icmp_cksum = 0;
header.icmp_cksum = compute_icmp_checksum ((u_int16_t*)&header, sizeof(header));

setsockopt (sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));
ssize_t bytes_sent = sendto (  
    sockfd,  &header,   sizeof(header),  0,   (struct sockaddr*)&recipient,   sizeof(recipient));
}