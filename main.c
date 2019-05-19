#include <stdio.h>
#define MAX_PATH 260

unsigned int slen(const char *s) {
    const char *sc = s;
    while (*sc != '\0') {
        ++sc;
    }
    return sc - s;
}

char *stok(char **s, const char *ct) {
    char *sbegin = *s;
    const char *sc1, *sc2;

    if (sbegin == NULL) {
        return NULL;
    }

    for (sc1 = sbegin; *sc1 != '\0'; ++sc1) {
        for (sc2 = ct; *sc2 != '\0'; ++sc2) {
            if (*sc1 == *sc2) {
                return (char *)sc1;
            }
        }
    }

    return sbegin;
}

short int scmp(const char *cs, const char *ct) {
    char c1, c2;

    while (1) {
        c1 = *cs++;
        c2 = *ct++;
        if (c1 != c2) {
            return c1 < c2 ? -1 : 1;
        }
        if (!c1) {
            break;
        }
    }
    return 0;
}

unsigned int sspn(const char *string, const char *reject) {
    const char *p;
    const char *r;
    unsigned int count = 0;

    for (p = string; *p != '\0'; ++p) {
        for (r = reject; *r != '\0'; ++r) {
            if (*p == *r) {
                return count;
            }
        }
        ++count;
    }
    return count;
}

char *scpy(char *destination, const char *src) {
    char *temp = destination;

    while (*src != '\0') {
        *destination++ = *src++;
    }
    return temp;
}

void input(char *delim, char *paths) {
    char temp[2];
    fputs("delim: ", stdout);
    fgets(temp, 2, stdin);
    *delim = temp[0];
    fputs("paths: ", stdout);
    fgets(temp, 2, stdin);
    fgets(paths, MAX_PATH * 4 + 4, stdin);
}
int check(char delim, char *paths, char *reject) {
    const char *sc1, *sc2;
    int pathNum = 1;
    int letter = sspn(paths, reject);
    int length = slen(paths);

    if (delim != ' ' && delim != '+' && delim != ':') {
        printf("incorect delimenator\n");
        return 0;
    }
    if (letter != length) {
        printf("wrong input in letter %d\n", letter);
        return 0;
    }

    if (paths[0] != '/' && paths[0] != '~') {
        printf("Wrong input in path: %d(letter %d =>\"%c\")\n", pathNum, letter,
               paths[0]);
        return 0;
    }

    letter = 1;

    for (sc1 = paths; *sc1 != '\0'; ++sc1) {

        if (*sc1 == delim) {
            pathNum++;
            if (*(sc1 + 1) != '/' && *(sc1 + 1) != '~') {
                printf("Wrong input in path: %d(letter %d =>\"%c\")\n", pathNum,
                       letter, *sc1);
                return 0;
            }
        }

        if (*sc1 == '.' && *(sc1 + 1) == '/' && *(sc1 - 1) != '.' &&
            *(sc1 - 1) != '/') {
            printf("Wrong input in path: %d(letter %d =>\"%c\")\n", pathNum,
                   letter, *sc1);
            return 0;
        }

        if (*sc1 == '/' && *(sc1 + 1) == '/') {
            printf("Wrong input in path: %d(letter %d =>\"%c\")\n", pathNum,
                   letter, *sc1);
            return 0;
        }

        if (*sc1 == '.' && *(sc1 - 1) == '/' && *(sc1 - 2) == delim) {
            printf("Wrong input in path: %d(letter %d =>\"%c\")\n", pathNum,
                   letter, *sc1);
            return 0;
        }

        if (*sc1 == '.' && *(sc1 - 1) != '.' && *(sc1 - 1) != '/') {
            for (sc2 = sc1; *sc2 != '\0' && *sc2 != delim; ++sc2) {
                if (*sc2 == '/') {
                    printf("incorect folder name in path: %d(letter %d "
                           "=>\"%c\")\n",
                           pathNum, letter, *sc1);
                    return 0;
                }
            }
        }
        letter++;
    }
    return 1;
}
void process(char *paths) {
    char *sc;
    int i;
    int count;
    int arrSize = slen(paths);
    int currSize = arrSize;
    for (sc = paths; *sc != '\0'; ++sc) {

        if (*sc == '.' && *(sc - 1) == '/' && *(sc + 1) == '/') {
            scpy((sc - 1), (sc + 1));
            paths[arrSize] = '\0';
            paths[arrSize - 1] = '\0';
            arrSize -= 2;
        } else if (*sc == '.' && *(sc - 1) == '.' && *(sc + 1) == '/') {
            sc -= 3;
            count = 4;
            currSize -= 4;
            while (*sc != '/') {
                --sc;
                ++count;
                --currSize;
            }
            scpy(sc, (sc + count));
            for (i = currSize; i < arrSize; ++i) {
                paths[i] = '\0';
            }
            arrSize = currSize;
        }
    }
}
void output(char *paths) { printf("new paths: %s\n", paths); }

int main(int argc, char const *argv[]) {
    char delim;
    char paths[MAX_PATH * 4 + 4] = {'\0'};
    input(&delim, paths);
    char reject[10] = {'\\', ':', '*', '?', '\"', '<', '>', '|'};
    if (check(delim, paths, reject)) {
        process(paths);
        output(paths);
    }

    return 0;
}
