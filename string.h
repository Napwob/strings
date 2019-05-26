#ifndef STRING_H
#define STRING_H
#include <stdio.h>
#include <stdlib.h>

char *sstr(char *string1, const char *string2);
char* mystrchr(const char* s, const char c);
int slen(char *str);
int sspn(char *str, const char *substr);
int scmp(const char *str, const char *strc);
char *scpy(char *des, const char *src);
char* stok(char* str, const char* delim);
int is_valid_ip(char* ip_str);
int valid_digit(char* ip_str);
int cip(char* paths);
int chs(char *paths);
int csim(char *paths);
int cdom(char* paths);
int check(char* paths);
int procces(char delim,char* paths);
void input(char *delim);
void op(char *paths);


#endif
