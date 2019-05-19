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

#endif
