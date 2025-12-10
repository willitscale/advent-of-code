#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/include.h"
#include "shared.h"

int main()
{
    FILE* filePointer;
    char* line = NULL;
    size_t length = 0;
    ssize_t delta = 0;
    ssize_t read;
    char g[GRID_SIZE][GRID_SIZE] = {0};
    size_t w = 0, h = 0;

    filePointer = fopen("input2.txt", "r");

    if (NULL == filePointer) {
        return EXIT_FAILURE;
    }

    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }
        w = length;
        strncpy(g[h++], line, length);
    }

    size_t r;
    do {
        LinkedList *ll = initLinkedList(), *s = ll;
    
        for(int i = 0 ; i < h; i++) {
            for(int j = 0 ; j < w; j++) {
                if ('@' == g[i][j] && countSurrounding(g, w, h, i, j, '@') < 4) {
                    delta += 1;
                    Point *p = calloc(sizeof(Point), 1);
                    p->x = i;
                    p->y = j;
                    ll = addToLinkedList(ll, p);
                }
            }
        }
        
        r = 0;
        for(LinkedList *i = s; i != NULL && i->data != NULL; i = i->next) {
            Point *p = (Point *)i->data;
            g[p->x][p->y] = '.';
            r++;
            free(p);
        }

        free(ll);
    } while (r > 0);

    fclose(filePointer);

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}
