#include "../lib/include.h"

#define BUFFER 1000
#define MAP_LENGTH 62

char indexShift(const char);
char addPoint(int x, int y);
char setPosRec(char * [], int, int, int, int, int, const char);

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
                    delta += setPosRec(m, p1->x, p1->y, xDelta, yDelta, i, '#') + 
                            setPosRec(m, p2->x, p2->y, -xDelta, -yDelta, i, '#') + 
                            addPoint(p1->x, p1->y) + addPoint(p2->x, p2->y);
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

char addPoint(int x, int y)
{
    char * b = calloc(sizeof(char), 32);
    sprintf(b, "%d-%d", x, y);
    int r = (NULL == getDictionary(b)) ? 1 : 0;
    int * c = calloc(sizeof(int), 1);
    *c = 1;
    addDictionary(b,c);
    return r;
}

char setPosRec(char * m[], int x, int y, int dx, int dy, int h, const char c)
{
    int delta = 0;

    while(x >= 0 && x < h && y >= 0 && y < strlen(m[x])) {
        x += dx;
        y += dy;

        if (x < 0 || y < 0 || x >= h || y >= strlen(m[x]) || '.' != m[x][y]) {
            continue;
        }
        m[x][y] = '#';
        delta++;
    }

    return delta;
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
