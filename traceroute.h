#include "icmp_funcs.h"
#include "socket_err_handle.h"
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <sys/time.h>

void run_traceroute(struct sockaddr_in *recipient, int sockfd);