#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/linkedlist.h"

#define ARRAY_BUFFER 1000

typedef struct po
{
    int first;
    int second;
} PageOrder;

int main()
{
    FILE* filePointer;
    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    size_t delta = 0;

    LinkedList* pageList[ARRAY_BUFFER];
    int pageLengths[ARRAY_BUFFER];
    int updated[ARRAY_BUFFER];
    int rowIndex = 0;

    filePointer = fopen("input.txt", "r");

    if (NULL == filePointer) {
        return EXIT_FAILURE;
    }

    LinkedList *order = initLinkedList(), *ptr = order;
    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }

        char* eol = strstr(line, "\n");
        char* pageOrderBreak = strstr(line, "|");

        if (pageOrderBreak > line) {
            PageOrder* pageOrder = calloc(1, sizeof(PageOrder));
            sscanf(line, "%d|%d", &pageOrder->first, &pageOrder->second);
            ptr = addToLinkedList(ptr, pageOrder);
            continue;
        }

        int length = 0;
        LinkedList* pages = explodeNumbers(",", line, &length);

        if (NULL != pages) {
            pageList[rowIndex] = pages;
            pageLengths[rowIndex] = length;
            updated[rowIndex] = 0;
            rowIndex++;
        }
    }


    int updates;
    do {
        updates = 0;
        LinkedList *orderIterator = order;
        while(orderIterator != NULL && orderIterator->data != NULL) {
            PageOrder *pageOrder = (PageOrder*)orderIterator->data;
            for(int i = 0; i < rowIndex; i++) {
                LinkedList *a = NULL, *b = NULL, *pageIterator = pageList[i];
                while(pageIterator != NULL && pageIterator->data != NULL) {
                    int page = *(int*)pageIterator->data;
                    if (NULL == a && page == pageOrder->second) {
                        b = pageIterator;
                    }
                    if (page == pageOrder->first) {
                        a = pageIterator;
                    }
                    pageIterator = pageIterator->next;
                }

                if (NULL != b && NULL != a) {
                    void* tmpPtr = b->data;
                    b->data = a->data;
                    a->data = tmpPtr;
                    updated[i] = 1;
                    updates++;
                }
            }
            orderIterator = orderIterator->next;
        }
    } while(updates > 0);

    for(int i = 0; i < rowIndex; i++) {
        if (!updated[i]) {
            continue;
        }
        LinkedList *pageIterator = pageList[i];
        int j = 0;
        while(pageIterator != NULL && pageIterator->data != NULL) {
            int page = *(int*)pageIterator->data;
            if (j == (pageLengths[i]/2)) {
                delta += page;
            }
            pageIterator = pageIterator->next;
            j++;
        }
    }

    fclose(filePointer);

    if (line) {
        free(line);
    }

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}


