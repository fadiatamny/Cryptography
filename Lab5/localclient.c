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

struct pz{
    uint64_t data[5];
};

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
	uint64_t n = 0; //rand() % PUZZLENUM ;

	struct pz ps;
	Puzzle p;
	DecPuzzle* d;
	for(uint16_t i = 0 ; i < PUZZLENUM ; ++i)
	{
		printf("%d\n",sizeof(struct pz));
		if ((nrecv = recv(sock, &ps, sizeof(struct pz), 0)) < 0)
		{
			perror("recv");
			printf("%d",nrecv);
			return 1;
		}
		p.data[0] = ps.data[0];
		p.data[1] = ps.data[1];
		p.data[2] = ps.data[2];
		p.data[3] = ps.data[3];
		p.data[4] = ps.data[4];
		
		printf("test");
		printPuzzle(p);
		printf('\n');
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
