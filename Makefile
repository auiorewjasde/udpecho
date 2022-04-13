all : server client
server : server.c conf.h
	gcc server.c -o server
client : client.c conf.h
	gcc client.c -o client
