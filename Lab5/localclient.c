#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include "merkel.h"

#define PORT 0x0da2
#define IP_ADDR 0x7f000001

int main(void)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0), nrecv;
	struct sockaddr_in s = {0};
	s.sin_family = AF_INET;
	s.sin_port = htons(PORT);
	s.sin_addr.s_addr = htonl(IP_ADDR);
	if (connect(sock, (struct sockaddr*)&s, sizeof(s)) < 0)
	{
		perror("connect");
		return 1;
	}
	printf("Successfully connected.\n");
	uint64_t n = rand() % PUZZLENUM ;

	Puzzle p;
	DecPuzzle* d;
			printf("1\n");

	for(uint16_t i = 0 ; i < PUZZLENUM ; ++i)
	{
		if ((nrecv = recv(sock, &p, sizeof(Puzzle), 0)) < 0)
		{
			perror("recv");
			return 1;
		}
		if( n  ==  i)
		{
			printf("1\n");
			d = decPuzzle(p);
		}
	}

	uint64_t keys[] = {d->key1, d->key2};

	if (send(sock, keys , sizeof(keys), 0) < 0)
	{
		perror("send");
		return 1;
	}

	return 0;
}
