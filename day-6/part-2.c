#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 500

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

void move(int*, int*, char, const char);
char isLoop(char * [], int, int, int, int, int);

int main()
{
    FILE* filePointer;
    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    size_t delta = 0;

    int x, y, sx, sy;
    char d = UP;

    char* m[BUFFER];

    filePointer = fopen("input.txt", "r");

    if (NULL == filePointer) {
        return EXIT_FAILURE;
    }

    int i = 0;
    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }

        char* eol = strstr(line, "\n");
        size_t len = (eol > line)?eol-line-1:strlen(line);
        m[i] = calloc(sizeof(char), len);
        strncat(m[i++], line, len);

        char * start = strstr(line, "^");
        if (NULL != start) {
            sx = x = i-1;
            sy = y = (int)(start-line);
        }

    }

    char o[BUFFER][BUFFER] = {{0}};
    while(1) {
        move(&x, &y, d, 1);
        
        if (x >= i || 0 > x || 0 > y || y >= strlen(m[x])) {
            break;
        }

        if ('#' != m[x][y] && !o[x][y] && isLoop(m, i, sx, sy, x, y)) {
            o[x][y] = 1;
            delta++;
        } else if ('#' == m[x][y]) {
            move(&x, &y, d, -1);
            d = (LEFT == d) ? UP : d+1;
        }
    }

    fclose(filePointer);

    if (line) {
        free(line);
    }

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}

void move(int * x, int * y, char d, const char v)
{
    if (d % 2 == 0) {
        *x += (DOWN == d) ? v : (-1 * v);
    } else {
        *y += (RIGHT == d) ? v : (-1 * v);
    }
}


char isLoop(char * m[], int i, int x, int y, int ox, int oy)
{
    if (x == ox && y == oy) {
        return 0;
    }
    char p = (8 == ox && 1 == oy);

    char d = UP;
    char s[4][BUFFER][BUFFER] = {{{0}}};
    while(1) {
        move(&x, &y, d, 1);

        if (x >= i || 0 > x || 0 > y || y >= strlen(m[x])) {
            return 0;
        }

        if ('#' == m[x][y] || (ox == x && oy == y)) {
            move(&x, &y, d, -1);
            d = (LEFT == d) ? UP : d+1;
        }

        if (1 == s[d][x][y]) {
            return 1;
        }
        
        s[d][x][y] = 1;
    }

    return 0;
}
