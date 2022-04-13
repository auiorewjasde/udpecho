#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "conf.h"
 
int main(int argc, char** argv)
{
	int sd, len, i;
	struct sockaddr_in addr;

	socklen_t sin_size;
	struct sockaddr_in from_addr;

	char buf[2048];

	if((sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		return -1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		return -1;
	}

	memset(buf, 0, sizeof(buf));

	sin_size = sizeof(from_addr);
	if(recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *) &from_addr, &sin_size) < 0) {
		perror("recvfrom");
		return -1;
	}
	printf("port%d addr%x\n", from_addr.sin_port, from_addr.sin_addr);
	printf("sin_size=%d\n", sin_size);
	printf("%s\n", buf);
	for(i=0; i<len/2; i++){
		char t = buf[i];
		buf[i] = buf[len-1-i];
		buf[len-1-i] = t;
	}
	if(sendto(sd, buf, len, 0, (struct sockaddr *)&from_addr, sizeof(from_addr)) < 0) {
		perror("sendto");
		return -1;
	}

	close(sd);

	return 0;
}
/*
inet_ntop(AF_INET, &senderinfo.sin_addr, senderstr, sizeof(senderstr));
printf("recvfrom : %s, port=%d\n", senderstr, ntohs(senderinfo.sin_port));
sendto(sock, buf, n, 0, (struct sockaddr *)&senderinfo, addrlen);

 */
