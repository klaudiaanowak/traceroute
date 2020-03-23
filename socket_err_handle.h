#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>

ssize_t recvfrom_err_handle (int fd, void *ptr, size_t nbytes, int flags, struct sockaddr_in *sa, socklen_t *salenptr);
void sendto_err_handle(int fd, const void *ptr, int nbytes, int flags, const struct sockaddr_in *sa, socklen_t salen);
void setsockopt_err_handle(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
int select_err_handle(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
void bind_err_hanlde(int fd, const struct sockaddr_in *sa, socklen_t salen);

