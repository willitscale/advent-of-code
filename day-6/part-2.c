#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/linkedlist.h"

#define ARRAY_BUFFER 1000

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

typedef struct c {
    int x, y;
} Corner;

typedef struct l {
    Corner *start, *end;
    char direction;
} Line;

void moveIndexes(int * row, int * column, char * direction, const char value);
char loopCheck(char * matrix[], int, LinkedList* lines, int x, int y, char direction);
Corner * createCorner(int x, int y);

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

    LinkedList *linesHead = initLinkedList(), *lines = linesHead;

    Line *lineNode = calloc(1, sizeof(Line));
    Corner *corner = calloc(1, sizeof(Corner));
    char lineStart = 1;

    while(1) {
        if (lineStart) {
            lineNode->start = createCorner(row, column);
            lineNode->end = createCorner(row, column);
            lines = addToLinkedList(lines, lineNode);
            lineStart = 0;
        }

        moveIndexes(&row, &column, &direction, 1);
        
        lineNode->end->x = row;
        lineNode->end->y = column;
        lineNode->direction = direction;

        if (row >= index || 0 > row || 0 > column || column >= strlen(matrix[row])) {
            break;
        }

        if ('#' != matrix[row][column] && loopCheck(matrix, index, linesHead, row, column, direction)) {
            delta++;
            moveIndexes(&row, &column, &direction, 1);
            matrix[row][column] = 'O';
            moveIndexes(&row, &column, &direction, -1);
        }

        if ('.' == matrix[row][column]) {
            matrix[row][column] = (direction == UP || direction == DOWN) ? '|' : '-';
        } else if ('#' == matrix[row][column]) {
            moveIndexes(&row, &column, &direction, -1);
            if ('O' != matrix[row][column]) {
                matrix[row][column] = '+';
            }

            lineNode->end->x = row;
            lineNode->end->y = column;
            lineNode->direction = direction;
            lineNode = calloc(1, sizeof(Line));
            lineStart = 1;
            
            direction = (LEFT == direction) ? UP : direction+1;
        }
    }

    for(int i = 0; i < index; i++) {
        printf("%s", matrix[i]);
        printf("\n");
    }

    fclose(filePointer);

    if (line) {
        free(line);
    }

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}

void moveIndexes(int * row, int * column, char * direction, const char value) {
    if (UP == *direction || DOWN == *direction) {
        *row += (DOWN == *direction) ? value : (-1 * value);
    } else {
        *column += (RIGHT == *direction) ? value : (-1 * value);
    }
}

char loopCheck(char * matrix[], int index, LinkedList* lines, int x, int y, char direction) {
    direction = (LEFT == direction) ? UP : direction+1;
    while('#' != matrix[x][y]) {
        moveIndexes(&x, &y, &direction, 1);

        if (x >= index || 0 > x || 0 > y || y >= strlen(matrix[x])) {
            return 0;
        }

        LinkedList *iterator = lines;
        while(NULL != iterator && NULL != iterator->data) {
            Line* lineNode = iterator->data;
            Corner * start = lineNode->start, * end = lineNode->end;
            if ((direction == lineNode->direction) &&
                ((x == start->x && y == start->y) ||
                (((x >= start->x && x <= end->x) || (x <= start->x && x >= end->x)) && y == start->y && y == end->y) ||
                (((y >= start->y && y <= end->y) || (y <= start->y && y >= end->y)) && x == start->x && x == end->x))) {
                return 1;
            }
            iterator = iterator->next;
        }
    }

    return 0;
}

/**
 * Need some GC for the corners as they won't get cleaned up
 */
Corner * createCorner(int x, int y)
{
    Corner *corner = calloc(sizeof(Corner),1);
    corner->x = x;
    corner->y = y;
    return corner;
}
