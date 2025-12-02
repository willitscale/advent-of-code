#include "../lib/include.h"

#define BUFFER 1000

char path(char *[], int, int, int, int);

int main()
{
    FILE* filePointer;
    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    long long delta = 0;

    filePointer = fopen("input.txt", "r");

    if (NULL == filePointer) {
        return EXIT_FAILURE;
    }

    char* m[BUFFER];
    int i = 0;

    LinkedList *heads = initLinkedList(), 
                *headsPtr = heads;

    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }

        char* eol = strstr(line, "\n");
        size_t len = (eol > line)?eol-line-1:strlen(line);
        m[i] = calloc(sizeof(char), len);
        strncat(m[i], line, len);

        for(int j = 0; j < len; j++) {
            if ('0' == m[i][j]) {
                Point *p = calloc(sizeof(Point), 1);
                p->x = i;
                p->y = j;
                headsPtr = addToLinkedList(headsPtr, p);
            }
        }

        i++;
    }

    headsPtr = heads;
    while(NULL != headsPtr && NULL != headsPtr->next && NULL != headsPtr->data) {
        Point *p = (Point*)headsPtr->data;
        delta += path(m, i, p->x, p->y, '0');
        headsPtr = headsPtr->next;
    }

    fclose(filePointer);

    if (line) {
        free(line);
    }

    printf("Delta is %llu\n", delta);

    return EXIT_SUCCESS;
}

char path(char * m[], int h, int x, int y, int e) {
    if (x < 0 || x >= h || y < 0 || y >= strlen(m[x]) || e++ != m[x][y]) {
        return 0;
    }

    if ('9' == m[x][y]) {
        return 1;
    }

    return path(m, h, x+1, y, e) + 
           path(m, h, x-1, y, e) + 
           path(m, h, x, y+1, e) + 
           path(m, h, x, y-1, e);
}