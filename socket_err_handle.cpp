#include "socket_err_handle.h"

int socket_err_handle(int family, int type, int protocol)
{
	int res;
	if ((res = socket(family, type, protocol)) < 0)
	{
		fprintf(stderr, "socket error: %s\n", strerror(errno));
	}
	return res;
}

ssize_t recvfrom_err_handle(int fd, void *ptr, size_t nbytes, int flags, struct sockaddr_in *sa, socklen_t *salenptr)
{
	int res;
	if ((res = recvfrom(fd, ptr, nbytes, flags, (struct sockaddr *)sa, salenptr)) < 0)
	{
		fprintf(stderr, "recvfrom error: %s\n", strerror(errno));
	}
	return res;
}

void sendto_err_handle(int fd, const void *ptr, int nbytes, int flags, const struct sockaddr_in *sa, socklen_t salen)
{
	if (sendto(fd, ptr, nbytes, flags, (struct sockaddr *)sa, salen) != nbytes)
		fprintf(stderr, "sendto error: %s\n", strerror(errno));
}
void setsockopt_err_handle(int sockfd, int level, int optname, const void *optval, socklen_t optlen)
{
	if (setsockopt(sockfd, level, optname, optval, optlen) < 0)
		fprintf(stderr, "socketopt error: %s\n", strerror(errno));
}

int select_err_handle(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
	int res;
	if ((res = select(nfds, readfds, writefds, exceptfds, timeout)) < 0)
	{
		fprintf(stderr, "select error: %s\n", strerror(errno));
	}
	return res;
}
void bind_err_hanlde(int fd, const struct sockaddr_in *sa, socklen_t salen)
{
	if (bind(fd, (struct sockaddr*)sa, salen) < 0)
		fprintf(stderr, "bind error: %s\n", strerror(errno));
}