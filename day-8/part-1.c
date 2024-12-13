#include "../lib/include.h"

#define BUFFER 1000
#define MAP_LENGTH 62

char indexShift(const char);
char setPos(char * [], int, int, int, const char);

int main()
{
    FILE* filePointer;
    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    size_t delta = 0;

    filePointer = fopen("input.txt", "r");

    if (NULL == filePointer) {
        return EXIT_FAILURE;
    }

    char* m[BUFFER];
    LinkedList * map[MAP_LENGTH] = {0};
    int i = 0;

    LinkedList *unique = initLinkedList();

    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }

        char* eol = strstr(line, "\n");
        size_t len = (eol > line)?eol-line-1:strlen(line);
        m[i] = calloc(sizeof(char), len);
        strncat(m[i], line, len);

        for(int j = 0; j < strlen(m[i]); j++) {
            int idx = indexShift(m[i][j]);
            
            if (idx != -1) {
                map[idx] = (NULL == map[idx]) ? initLinkedList() : map[idx];
                Point * p1 = calloc(sizeof(Point), 1);
                p1->x = i;
                p1->y = j;
                appendLinkedList(map[idx], p1);
            }
        }
            
        i++;
    }

    for (int j = 0; j < MAP_LENGTH; j++) {
        LinkedList *points = map[j], *next;
        while(NULL != points && NULL != points->next && NULL != points->data) {
            Point *p1 = points->data;
            next = points;
            while(NULL != next && NULL != next->next && NULL != next->data) {
                Point *p2 = next->data;
                if (p1->x != p2->x || p1->y != p2->y) {
                    int xDelta = p1->x - p2->x, yDelta = p1->y - p2->y;
                    delta += setPos(m, p1->x + xDelta, p1->y + yDelta, i, '#') + 
                            setPos(m, p2->x - xDelta, p2->y - yDelta, i, '#');
                }
                next = next->next;
            }
            points = points->next;
        }
    }

    for (int a = 0; a < i; a++) {
        printf("%s\n", m[a]);
    }

    fclose(filePointer);

    if (line) {
        free(line);
    }

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}

char setPos(char * m[], int x, int y, int h, const char c)
{
    if (0 > x || 0 > y || x >= h || y >= strlen(m[x]) || '#' == m[x][y]) {
        return 0;
    }

    m[x][y] = ('#' != m[x][y]) ? c : m[x][y];
    return 1;
}

char indexShift(const char c) {
    if (c >= 48 && c <= 57) { // 0-9
        return c - 48;
    }

    if (c >= 65 && c <= 90) { // A-Z
        return c - 55;
    }

    if (c >= 97 && c <= 122) { // a-z
        return c - 61;
    }

    return -1;
}
