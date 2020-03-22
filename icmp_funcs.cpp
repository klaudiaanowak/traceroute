#include "icmp_funcs.h"

short compute_icmp_checksum (const short *buff, int length)
{
	long sum;
	const short* ptr = buff;
	assert (length % 2 == 0);
	for (sum = 0; length > 0; length -= 2)
		sum += *ptr++;
	sum = (sum >> 16) + (sum & 0xffff);
	return (short)(~(sum + (sum >> 16)));
}

