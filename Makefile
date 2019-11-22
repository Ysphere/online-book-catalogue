CC = gcc

all: server client

server: src/server.c
	$(CC) -g -Iinclude -pthread -o server src/server.c src/list.c 

client: src/client.c
	$(CC) -g -o client src/client.c

clean:
	rm -f *.o server client

zip:
	zip -r cis3210_ass1_Yuhang.zip *
