#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "conf.h"
 
int main(int argc, char** argv){
	int sd, len;
	struct sockaddr_in addr;
	char buf[BUFSIZE+1];

	if((sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot socket");
		return -1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(SERVERIP);

	scanf(SCANFTXT,buf);
	printf("[%s]\n", buf);
	len = strnlen(buf, 16);

	if(sendto(sd, buf, len, 0, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("cannot sendto");
		return -1;
	}
	struct sockaddr_in from_addr;
	socklen_t sin_size;
	if(recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&from_addr, &sin_size) < 0) {
		perror("cannot recvfrom");
		return -1;
	}

	close(sd);

	return 0;
}
