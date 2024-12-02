#include <stdio.h>
#include <stdlib.h>
#include "../lib/linkedlist.h"

int compareUnordedLong(void* a, void* b) {
    return (*(size_t*)a >= *(size_t*)b);
}

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

    LinkedList *leftHead = initLinkedList(), 
        *rightHead = initLinkedList();

    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }

        size_t *left = calloc(1, sizeof(size_t)), 
            *right = calloc(1, sizeof(size_t));

        sscanf(line, "%lu %lu", left, right);

        addOrderedLinkedList(leftHead, left, compareUnordedLong);
        addOrderedLinkedList(rightHead, right, compareUnordedLong);
    }

    LinkedList *left = leftHead, *right = rightHead;
    while(NULL != left) {
        while(NULL != right && compareUnordedLong(left->data, right->data)) {
            if (*(size_t*)left->data == *(size_t*)right->data) {
                delta += *(size_t*)left->data;
            }
            right = right->next;
        }
        left = left->next;
    }

    fclose(filePointer);
    free(line);
    freeLinkedList(leftHead);
    freeLinkedList(rightHead);

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}
