#include "traceroute.h"
#include "socket_err_handle.h"

// Klaudia Nowak 297936

int main(int argc, char **argv)
{
	// check input
	if (argc != 2)
	{
		printf("Invalid input. You can use only one IP address \n");
		return EXIT_FAILURE;
	}
	struct sockaddr_in recipient;
	bzero(&recipient, sizeof(recipient));
	recipient.sin_family = AF_INET;
	if (inet_pton(AF_INET, argv[1], &recipient.sin_addr) != 1)
	{
		printf("Incorrect IP address\n");
		return EXIT_FAILURE;
	}

	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0)
	{
		fprintf(stderr, "socket error: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	run_traceroute(&recipient, sockfd);
	return EXIT_SUCCESS;
}