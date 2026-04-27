all : server client
CFLAGS = -Wall -Wextra -O2
server : server.c conf.h
	gcc $(CFLAGS) server.c -o server
client : client.c conf.h
	gcc $(CFLAGS) client.c -o client
