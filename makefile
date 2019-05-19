string.o: string.c 
	gcc -std=c99 -I thirdparty -I src -c string.c -o string.o

main.o: main.c 
	gcc -std=c99 -Wall -Werror -c main.c -o main.o
	
main: main.o string.o
	gcc -Wall -Werror main.o string.o -lm -o main

