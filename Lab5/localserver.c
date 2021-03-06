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
#define QUEUE_LEN 20

int main(void)
{
	int listenS = socket(AF_INET, SOCK_STREAM, 0);
	if (listenS < 0)
	{
		perror("socket");
		return 1;
	}
	struct sockaddr_in s = {0};
	s.sin_family = AF_INET;
	s.sin_port = htons(PORT);
	s.sin_addr.s_addr = htonl(IP_ADDR);
	if (bind(listenS, (struct sockaddr*)&s, sizeof(s)) < 0)
	{
		perror("bind");
		return 1;
	}
	if (listen(listenS, QUEUE_LEN) < 0)
	{
		perror("listen");
		return 1;
	}
	struct sockaddr_in clientIn;
	int clientInSize = sizeof clientIn;
	int newfd = accept(listenS, (struct sockaddr*)&clientIn, (socklen_t*)&clientInSize);
	if (newfd < 0)
	{
		perror("accept");
		return 1;
	}
	printf("Sending data to client %d\n", newfd);
	Puzzle* p = genPuzzles();
	printf("1");
	for(uint16_t i = 0; i < PUZZLENUM; ++i)
	{
		printf("1 %d\n",i);
		if (send(newfd, &p[i], sizeof(Puzzle), 0) < 0)
		{
			perror("send");
			return 1;
		}
	}
	uint64_t keys[2] = {0};
	if ((newfd = recv(listenS, keys , sizeof(keys), 0)) < 0)
	{
		perror("recv");
		return 1;
	}

	close(newfd);
	close(listenS);
	return 0;
}
