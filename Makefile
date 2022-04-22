server: server.o card.o
	gcc -Wall server.o card.o -o server

server.o: server.c card.h
	gcc -Wall -c server.c

card.o: card.c  card.h
	gcc -Wall -c card.c

clean:
	rm server
	rm server.o
	rm card.o
