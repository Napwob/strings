# include <limits.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
#include <dirent.h>
# define NO_OF_CHARS 256

bool match(char *first, char * second)
{
    if (*first == '\0' && *second == '\0')
        return true;

    if (*first == '*' && *(first+1) != '\0' && *second == '\0')
        return false;

    if (*first == '?' || *first == *second)
        return match(first+1, second+1);

    if (*first == '*')
        return match(first+1, second) || match(first, second+1);
    return false;
}

void test(char *first, char *second)
{
    match(first, second)? puts("Yes"): puts("No");
}

int max (int a, int b)
{
    return (a > b)? a: b;
}

void badCharHeuristic(char *str, int size, int badchar[NO_OF_CHARS])
{
    int i;
    for (i = 0; i < NO_OF_CHARS; i++)
         badchar[i] = -1;
    for (i = 0; i < size; i++)
         badchar[(int) str[i]] = i;
}

void search(char *txt,  char *pat)
{
    int m = strlen(pat); //Длина подстроки
    int n = strlen(txt); //Длина строки

    int badchar[NO_OF_CHARS];//Массив на 256 символов

    badCharHeuristic(pat, m, badchar);
    int s = 0;

    while(s <= (n - m))
    {
        int j = m-1;

        while(j >= 0 && pat[j] == txt[s+j])
            j--;

        if (j < 0) // если j меньше 0
        {
            printf("\n pattern occurs at shift = %d", s);
            s += (s+m < n)? m-badchar[txt[s+m]] : 1;
        }
        else
            s += max(1, j - badchar[txt[s+j]]);
    }
}

int main(int *pat[], char *direct[])
{
    DIR *d;
    struct dirent *dir;
    d = opendir(direct);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            FILE *txt=fopen (dir->d_name,"r");
            char pat[] = "A";
            search(txt, pat);
        }
        closedir(d);
    }
    return 0;
}
