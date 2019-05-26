#include <stdio.h>
#include <stdlib.h>
#define MAX_PATH 260
#define DELIM "."
#include <string.h>


int main(int argc, char const *argv[]) {
    //char *paths = malloc(sizeof(char) * MAX_PATH*4);
    char delim='+';
    char paths[]={"smb://192.168.1.1/test+http://mysrv.com/Windows/+http://192.500.1.1/test+ftp://my.ru/m/n/k.txt"};
    //input(&delim);//, paths);
    int error= procces(delim,paths);;


    return 0;
}
