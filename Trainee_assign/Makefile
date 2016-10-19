

all: client.o server.o
	gcc -o client client.o
	gcc -o server server.o -lpthread

client.o: client.c
	gcc -c client.c

server.o: server.c
	gcc -c server.c

clean:
	rm -rf *.o 
