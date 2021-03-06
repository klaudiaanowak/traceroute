#include "traceroute.h"

const int ICMP_HEADER_LEN = 8;
int pid;
const int maxttl = 30;
unsigned char buffer[IP_MAXPACKET + 1];
unsigned char *buffer_ptr;
int packets[maxttl];
double packets_times[maxttl];

void send_packet(sockaddr_in &recipient, int sockfd, int ttl);
void receive_packet(int id, char *all_ips, char *new_address, timeval *timers, int i);

void run_traceroute(sockaddr_in *recipient, int sockfd)
{
    for (int i = 0; i < maxttl; i++)
    {
        packets[i] = 0;
        packets_times[i] = 0;
    }

    pid = getpid();
    int ttl = 1;
    while (ttl < maxttl)
    {
        timeval timers[3];
        for (int i = 0; i < 3; ++i)
        {
            timeval tim;
            send_packet(*recipient, sockfd, ttl);
            gettimeofday(&tim, NULL);
            timers[i] = tim;
        }
        int i = 0;
        char packets_ip[100] = {};

        for (;;)
        {

            sockaddr_in receiver_address;
            socklen_t len = sizeof(receiver_address);

            fd_set descriptors;
            FD_ZERO(&descriptors);
            FD_SET(sockfd, &descriptors);
            struct timeval tv;
            tv.tv_sec = 1;
            tv.tv_usec = 0;

            int ready = select_err_handle(sockfd + 1, &descriptors, NULL, NULL, &tv);
            if (ready)
            {
                ssize_t packet_len = recvfrom_err_handle(sockfd, buffer, IP_MAXPACKET + 1, 0, &receiver_address, &len);
                if (packet_len == 0)
                    break;
                buffer_ptr = buffer;
                char ip_address[20];

                ip *ip_packet = (ip *)buffer_ptr;
                buffer_ptr += ip_packet->ip_hl * 4;

                icmp *icmp_packet = (icmp *)buffer_ptr;
                buffer_ptr += ICMP_HEADER_LEN;

                if (icmp_packet->icmp_type == ICMP_TIME_EXCEEDED &&
                    icmp_packet->icmp_code == ICMP_EXC_TTL)
                {
                    ip *packet_orig = (ip *)buffer_ptr;
                    buffer_ptr += packet_orig->ip_hl * 4;
                    icmp_packet = (icmp *)buffer_ptr;
                    inet_ntop(AF_INET, &receiver_address.sin_addr, ip_address, sizeof(ip_address));

                    if (icmp_packet->icmp_id == pid)
                    {
                        if (ttl == icmp_packet->icmp_seq)
                        {
                            receive_packet(icmp_packet->icmp_seq, packets_ip, ip_address, timers, i);
                            if (packets[icmp_packet->icmp_seq] == 3)
                            {
                                printf("%d. %s %4.0lfms\n", icmp_packet->icmp_seq, packets_ip, packets_times[icmp_packet->icmp_seq] / 3);
                                break;
                            }
                        }
                        else if (i == 3)
                        {
                            printf("%d. %s ???\n", icmp_packet->icmp_seq, ip_address);
                        }
                        i++;
                    }
                    else
                    {
                        continue;
                    }
                }
                else if (icmp_packet->icmp_type == ICMP_ECHOREPLY && icmp_packet->icmp_id == pid)
                {
                    inet_ntop(AF_INET, &receiver_address.sin_addr, ip_address, sizeof(ip_address));
                    ip *packet_orig = (ip *)buffer_ptr;
                    buffer_ptr += packet_orig->ip_hl * 4;
                    receive_packet(icmp_packet->icmp_seq, packets_ip, ip_address, timers, i);
                    if (packets[icmp_packet->icmp_seq] == 3)
                    {
                        printf("%d. %s %4.0lfms\n", icmp_packet->icmp_seq, ip_address, packets_times[icmp_packet->icmp_seq] / 3);
                        exit(0);
                    }
                    i++;
                }
            }
            else
            {
                printf("%d. *\n", ttl);
                break;
            }
        }
        ttl++;
    }
}

// function to sending header of packet to recipient
void send_packet(sockaddr_in &recipient, int sockfd, int ttl)
{
    icmphdr header;
    header.type = ICMP_ECHO;
    header.code = 0;
    header.un.echo.id = pid;
    header.un.echo.sequence = ttl;
    header.checksum = 0;
    header.checksum = compute_icmp_checksum((short *)&header, sizeof(header));

    setsockopt_err_handle(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));
    sendto_err_handle(
        sockfd, &header, sizeof(header), 0, &recipient, sizeof(recipient));
}

// function to receive and process packet
void receive_packet(int id, char *all_ips, char *new_address, timeval *timers, int i)
{
    packets[id] += 1;
    timeval tim;
    gettimeofday(&tim, NULL);
    double elapsedTime = (tim.tv_sec - timers[i].tv_sec) * 1000.0;
    elapsedTime += (tim.tv_usec - timers[i].tv_usec) / 1000.0;

    packets_times[id] += elapsedTime;
    if (strlen(all_ips) == 0)
    {
        strcat(all_ips, new_address);
    }
    else if (!strstr(all_ips, new_address))
    {
        strcat(all_ips, " ");
        strcat(all_ips, new_address);
    }
}
