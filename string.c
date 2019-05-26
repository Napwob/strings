#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DELIM "."
#define MAX_PATH 260

void op(char *paths)
{
    printf("new paths: %s\n", paths);
}

char *sstr(char *string1, const char *string2)
{
	char *strptr = string1;
	int j = 0,i;
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

char* mystrchr(const char* s, const char c)
{
    while (*s && *s != c)
        ++s;
    return (*s) ? (char*)s : NULL;
}


int slen(char *str)
{
	int count = 0,i;
	for (i = 0; str[i] != '\0'; i++) {
		count++;
	}
	return count++;
}

int sspn(char *str, const char *substr)
{
	int count = 0,i,j;
	for (i = 0; str[i] != 0; i++) {
		for (j = 0; substr[j]; j++) {
			if (str[i] == substr[j]) {
				count++;
			}
		}
	}
	return count;
}

int scmp(const char *str, const char *strc)
{
	int ncount = 0, pcount = 0,i;
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

char *scpy(char *des, const char *src)
{
	int i;
	for (i = 0; src[i] != 0; i++) {
		des[i] = src[i];
	}
	des[i] = 0;
	return des;
}

char* stok(char* str, const char* delim)
{
    static char* next;

    if (str) {
        next = str;
        while (*next && mystrchr(delim, *next))
            *next++ = '\0';
    }

    if (!*next)
        return NULL;

    str = next;

    while (*next && !mystrchr(delim, *next))
        ++next;
    while (*next && mystrchr(delim, *next))
        *next++ = '\0';

    return str;
}

void input(char *delim){//, char *paths) {
    char temp[2];
    fputs("delim: ", stdout);
    fgets(temp, 2, stdin);
    *delim = temp[0];
    //fputs("paths: ", stdout);
    //fgets(temp, 2, stdin);
    //fgets(paths, MAX_PATH * 4 + 4, stdin);
}

void procces(char delim,char* paths)
{
    char piece[MAX_PATH]="";
    char path[MAX_PATH]="";
    char newpaths[MAX_PATH*4]="";
    int ipi,ipa,en=0,oldipa=0,i,j,stand=0,hj;
    while(en==0)
    {
        for(ipi=0,ipa=oldipa;(paths[ipa]!=delim);++ipi,++ipa)
        {
            piece[ipi] = paths[ipa];
            if(paths[ipa]=='\0') en++;
        }
        oldipa=ipa+1;
	    hj=check(piece);
        if(hj == 0)
        {
            int ns=0;
            ns = chs(piece);

            for(i=0,j=ns;piece[i]!='\0';++i,++j)
            {
                path[i]=piece[j];
                if(path[i]=='/') path[i]='\\';
            }

            for(i=0,j=stand;path[i]!='\0';++i,++j)
            {
                newpaths[j]=path[i];
            }
            stand=j;
            newpaths[stand]='+';
            stand++;
        }
    }
    newpaths[stand-1]=' ';
    op(newpaths);
}

int check(char* paths)
{
    int n;
    n=csim(paths)
    if(n==1)
    {
        return 1;
    }
    n=chs(paths);
    if(n==1)
    {
        return 1;
    }
    int n1;
	n1=cip(paths);
	n=cdom(paths);
    if((n1==1) && (n==1))
    {
        return 1;
    }
    return 0;
}

int cdom(char* paths)
{
    char a[]=".ru";
    char a1[]=".com";
    char *i;
    i=sstr(paths,a);
    i=sstr(paths,a1);
    if(i!=NULL) return 0; else return 1;
}

int csim(char *paths)
{
    int i,j;
    char reject[7] = {'\\', '*', '?', '\"', '<', '>', '|'};
    for(i=0;paths[i]!='\0';++i){
        for(j=0;reject[j]!='\0';++j){
            if(paths[i]==reject[j]) return 1;
        }
    }
    return 0;
}

int chs(char *paths)
{
    int right=0;
    int i;
    char a[]="smb:";
    char a1[]="http:";

    for(i=0;paths[i]!='/';++i)
    {
        if(a[i]==paths[i]) right++;
    }
    if(right == 4) return right;
    right = 0;

    for(i=0;paths[i]!='/';++i)
    {
        if(a1[i]==paths[i]) right++;
    }
    if(right == 5) return right;
    return 1;
}

int cip(char* paths)
{
    char ip[20]="";
    int ns = chs(paths)+2,i,j,n;
    for(i=ns,j=0; paths[i]!='/';++i,++j)
        ip[j]=paths[i];
	n=is_valid_ip(ip)
    return n;
}

int valid_digit(char* ip_str)
{
    while (*ip_str) {
        if (*ip_str >= '0' && *ip_str <= '9')
            ++ip_str;
        else
            return 0;
    }
    return 1;
}

int is_valid_ip(char* ip_str)
{
    int num, dots = 0;
    char* ptr;

    if (ip_str == NULL)
        return 1;


    ptr = stok(ip_str, DELIM);

    if (ptr == NULL)
        return 1;

    while (ptr) {

        if (!valid_digit(ptr))
            return 1;

        num = atoi(ptr);

        if (num >= 0 && num <= 255) {
            /* parse remaining string */
            ptr = stok(NULL, DELIM);
            if (ptr != NULL)
                ++dots;
        }
        else
            return 1;
    }

    if (dots != 3)
        return 1;
    return 0;
}


