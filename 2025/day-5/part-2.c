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

    filePointer = fopen("input2.txt", "r");

    if (NULL == filePointer) {
        return EXIT_FAILURE;
    }

    LinkedList * r = initLinkedList();
    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }

        if (line[0] == 10) {
            break;
        }

        LPoint * p = getRange(line, NULL);
        appendLinkedList(r, p);
    }

    size_t updates;
    do {
        updates = 0;
        for(LinkedList * i = r; i != NULL && i->data != NULL; i = i->next) {
            LPoint * p1 = (LPoint *)i->data;
            LinkedList * prev = i;
            for(LinkedList * j = i->next; j != NULL && j->data != NULL; j = j->next) {
                LPoint * p2 = (LPoint *)j->data;
                if ((p1->x >= p2->x && p1->x <= p2->y) || 
                    (p1->y >= p2->x && p1->y <= p2->y) ||
                    (p2->x >= p1->x && p2->x <= p1->y) ||
                    (p2->y >= p1->x && p2->y <= p1->y)) {
                    p1->x = (p1->x < p2->x ? p1->x : p2->x);
                    p1->y = (p1->y > p2->y ? p1->y : p2->y);
                    prev->next = j->next;
                    updates++;
                } else {
                    prev = j;
                }
            }
        }
    } while (updates > 0);

    for(LinkedList * i = r; i != NULL && i->data != NULL; i = i->next) {
        LPoint * p1 = (LPoint *)i->data;
        delta += p1->y - p1->x + 1;
    }

    freeLinkedList(r);

    fclose(filePointer);

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}
