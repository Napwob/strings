#include <stdio.h>
#include <stdlib.h>
#define MAX_PATH 260
#define DELIM "+"


void op(char* paths) { printf("new paths: %s\n", paths); }

char* sstr(char* string1, char* string2) {
	char* strptr = string1;
	int j = 0, i;
	for (i = 0; string1[i] != 0; i++) {
		if (string2[j] == 0) {
			return strptr;
		}
		if (string1[i] != string2[j]) {
			j = 0;
			continue;
		}
		if (string1[i] == string2[j]) {
			if (j == 0) {
				strptr = string1 + i;
			}
			j++;
		}
	}
	if (string2[j] == 0) {
		return strptr;
	} else {
		return NULL;
	}
}

char* mystrchr(char* s, char c) {
	while (*s && *s != c) ++s;
	return (*s) ? (char*)s : NULL;
}

int slen(char* str) {
	int count = 0, i;
	for (i = 0; str[i] != '\0'; i++) {
		count++;
	}
	return count++;
}

int sspn(char* str, char* substr) {
	int count = 0, i, j;
	for (i = 0; str[i] != 0; i++) {
		for (j = 0; substr[j]; j++) {
			if (str[i] == substr[j]) {
				count++;
			}
		}
	}
	return count;
}

int scmp(char* str, char* strc) {
	int ncount = 0, pcount = 0, i;
	for (i = 0; str[i] != 0; i++) {
		if (str[i] < strc[i]) {
			ncount++;
		} else if (str[i] > strc[i]) {
			pcount++;
		}
	}
	if (ncount < pcount) {
		return pcount;
	} else if (ncount > pcount) {
		return -ncount;
	}
	return 0;
}

char* scpy(char* des, char* src) {
	int i;
	for (i = 0; src[i] != 0; i++) {
		des[i] = src[i];
	}
	des[i] = 0;
	return des;
}

char* stok(char* str, char* delim) {
	static char* next;

	if (str) {
		next = str;
		while (*next && mystrchr(delim, *next)) *next++ = '\0';
	}

	if (!*next) return NULL;

	str = next;

	while (*next && !mystrchr(delim, *next)) ++next;
	while (*next && mystrchr(delim, *next)) *next++ = '\0';

	return str;
}

void input(char* delim) {  //, char *paths) {
	char temp[2];
	fputs("delim: ", stdout);
	fgets(temp, 2, stdin);
	*delim = temp[0];
	// fputs("paths: ", stdout);
	// fgets(temp, 2, stdin);
	// fgets(paths, MAX_PATH * 4 + 4, stdin);
}

void procces(char delim, char* paths) {
	char newpaths[MAX_PATH * 4] = "";
	char path[260];
	int ipi, ipa = 0, en = 0, oldipa = 0, i, j, stand = 0, hj;
	char *piece=stok(paths, DELIM);
	while (piece != NULL) {
        scpy(path,piece);
        printf("%s\n",path);
		piece = stok(NULL, "+");
	}
	op(newpaths);
}

void cont(char* paths)
{
    int i;
    for(i=0;i<slen(paths);++i)
        if(paths[i]=='/') paths[i]='\\';
}

int check(char *paths) {
	if (csim(paths) == 1) {
		return 1;
	}
	if (chtsm(paths) == 1) {
		return 1;
	}
	if ((cip(paths) == 1)&& (cdom(paths) == 1)) {
		return 1;
	}
	return 0;
}

int chtsm(char* paths) {
	char a[] = "smb:";
	char a1[] = "http:";
	if (sstr(paths,a)!=0) return 4;
    if (sstr(paths,a1)!=0) return 5;
    return 1;
}

int cdom(char* paths) {
	char a[] = ".ru";
	char a1[] = ".com";
	char* i;
	i = sstr(paths, a);
	i = sstr(paths, a1);
	if (i != NULL)
		return 0;
	else
		return 1;
}

int csim(char* paths) {
	int i, j;
	char reject[7] = {'\\', '*', '?', '\"', '<', '>', '|'};
	for (i = 0; paths[i] != '\0'; ++i) {
		for (j = 0; reject[j] != '\0'; ++j) {
			if (paths[i] == reject[j]) return 1;
		}
	}
	return 0;
}

void chs(char* paths) {
	char a[] = "smb:";
	char a1[] = "http:";
	char cpaths[260]="";
    int t,h=0,i;
	if (sstr(paths,a)!=0) t=4;
    if (sstr(paths,a1)!=0) t=5;
    for(i=t;i<slen(paths);++i){
        cpaths[h]=paths[i];
        h++;
    }
    scpy(paths,cpaths);
}

int cip(char* paths) {
	char ip[20] = "";
	int ns = chtsm(paths) + 2, i, j;
	for (i = ns, j = 0; paths[i] != '/'; ++i, ++j) ip[j] = paths[i];
	return is_valid_ip(ip);
}

int valid_digit(char* ip_str) {
	while (*ip_str) {
		if (*ip_str >= '0' && *ip_str <= '9')
			++ip_str;
		else
			return 0;
	}
	return 1;
}

int ati(char* s) {
	int n = 0;
	while (*s >= '0' && *s <= '9') {
		n *= 10;
		n += *s++;
		n -= '0';
	}
	return n;
}

int is_valid_ip(char* ip_str) {
	int num, dots = 0;
	char* ptr;

	if (ip_str == NULL) return 1;

	ptr = stok(ip_str, DELIM);

	if (ptr == NULL) return 1;

	while (ptr) {
		if (!valid_digit(ptr)) return 1;

		num = ati(ptr);

		if (num >= 0 && num <= 255) {
			/* parse remaining string */
			ptr = stok(NULL, DELIM);
			if (ptr != NULL) ++dots;
		} else
			return 1;
	}

	if (dots != 3) return 1;
	return 0;
}

int main(int argc, char* argv[]) {
	// char *paths = malloc(sizeof(char) * MAX_PATH*4);
	char delim = '+';
	char paths[] = "smb://192.168.1.1/test+http://mysrv.com/Windows/+http://192.500.1.1/test+ftp://my.ru/m/n/k.txt";
	// input(&delim);//, paths);
	procces(delim, paths);

	return 0;
}
