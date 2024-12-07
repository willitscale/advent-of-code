#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/linkedlist.h"

#define ARRAY_BUFFER 1000

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

char makeMove(char* matrix[], int* row, int* column, int index, char* direction, size_t * delta);
char moveIndexes(int * row, int * column, char * direction, const char value);

int main()
{
    FILE* filePointer;
    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    size_t delta = 0;

    int row, column;
    char direction = UP;

    char* matrix[ARRAY_BUFFER];

    filePointer = fopen("input.txt", "r");

    if (NULL == filePointer) {
        return EXIT_FAILURE;
    }

    int index = 0;
    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }

        char* eol = strstr(line, "\n");
        size_t len = (eol > line)?eol-line:strlen(line);
        matrix[index] = calloc(sizeof(char), len);
        strncat(matrix[index++], line, len);

        char * start = strstr(line, "^");
        if (NULL == start) {
            continue;
        }

        column = (int)(start-line);
        row = index-1;
    }


    delta++;
    matrix[row][column] = 'X';

    while(1) {
        if (!makeMove(matrix, &row, &column, index, &direction, &delta)) {
            goto end;
        }
    }

    end:;

    fclose(filePointer);

    if (line) {
        free(line);
    }

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}

char makeMove(char* matrix[], int* row, int* column, int index, char* direction, size_t * delta)
{
    moveIndexes(row, column, direction, 1);

    if (*row >= index || 0 > *row || 0 > *column || *column >= strlen(matrix[*row])) {
        return 0;
    }

    if ('.' == matrix[*row][*column]) {
        (*delta)++;
        matrix[*row][*column] = 'X';
    } else if ('#' == matrix[*row][*column]) {
        moveIndexes(row, column, direction, -1);
        *direction = (LEFT == *direction) ? UP : *direction+1;
    }

    return 1;
}

char moveIndexes(int * row, int * column, char * direction, const char value) {
    if (UP == *direction || DOWN == *direction) {
        *row += (DOWN == *direction) ? value : (-1 * value);
    } else {
        *column += (RIGHT == *direction) ? value : (-1 * value);
    }
}


