.PHONY:all
CC = gсс -std=c99 
CFLAGS = -Wall
EXECUTABLE = strings

$(EXECUTABLE): main.o string.o
	$(CC) $(CFLAGS) -o $(EXECUTABLE) main.o string.o
main.o: main.c
	$(CC) $(CFLAGS) -o main.o main.c

