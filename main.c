#include <stdio.h>
#include <stdlib.h>
#define MAX_PATH 260
#define DELIM "."
#include <string.h>

void input(char *delim){//, char *paths) {
    char temp[2];
    fputs("delim: ", stdout);
    fgets(temp, 2, stdin);
    *delim = temp[0];
    //fputs("paths: ", stdout);
    //fgets(temp, 2, stdin);
    //fgets(paths, MAX_PATH * 4 + 4, stdin);
}

int procces(char delim,char* paths)
{
    char piece[MAX_PATH]="";
    char path[MAX_PATH]="";
    char newpaths[MAX_PATH*4]="";
    int ipi,ipa,en=0,oldipa=0,i,j,stand=0;
    while(en==0)
    {
        for(ipi=0,ipa=oldipa;(paths[ipa]!=delim);++ipi,++ipa)
        {
            piece[ipi] = paths[ipa];
            if(paths[ipa]=='\0') en++;
        }
        oldipa=ipa+1;
        if(check(piece) == 0)
        {
            int ns=0;
            ns = checkhs(piece);

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
    output(newpaths);
    return 0;
}

int check(char* paths)
{
    if(checksim(paths)==1)
    {
        return 1;
    }
    if(checkhs(paths)==1)
    {
        return 1;
    }
    if((checkip(paths)==1) && (checkdom(paths)==1))
    {
        return 1;
    }
    return 0;
}

int checkdom(char* paths)
{
    char a[]=".ru";
    char a1[]=".com";
    char *i;
    i=sstr(paths,a);
    i=sstr(paths,a1);
    if(i!=NULL) return 0; else return 1;
}

int checksim(char *paths)
{
    int i,j;
    char reject[6] = {'\\', '*', '?', '\"', '<', '>', '|'};
    for(i=0;paths[i]!='\0';++i){
        for(j=0;reject[j]!='\0';++j){
            if(paths[i]==reject[j]) return 1;
        }
    }
    return 0;
}

int checkhs(char *paths)
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

int checkip(char* paths)
{
    char ip[20]="";
    int ns = checkhs(paths)+2,i,j;
    for(i=ns,j=0; paths[i]!='/';++i,++j)
        ip[j]=paths[i];
    return is_valid_ip(ip);
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


void output(char *paths)
{
    printf("new paths: %s\n", paths);
}

int main(int argc, char const *argv[]) {
    //char *paths = malloc(sizeof(char) * MAX_PATH*4);
    char delim='+';
    char paths[]={"smb://192.168.1.1/test+http://mysrv.com/Windows/+http://192.500.1.1/test+ftp://my.ru/m/n/k.txt"};
    //input(&delim);//, paths);
    int error= procces(delim,paths);;


    return 0;
}
