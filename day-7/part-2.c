#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/linkedlist.h"

long long exec(long long, long long, LinkedList *);
long long concatenate(long long a, long long b);

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

    int i = 0;
    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }

        long long t, n;
        LinkedList * ns = explodeLongLong(" ", strstr(line, ":") + 2, &n), * i = ns;
        sscanf(line, "%lld", &t);
        delta += exec(t, *(long long*)i->data, i->next);
    }

    fclose(filePointer);

    if (line) {
        free(line);
    }

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}

long long exec(long long sum, long long value, LinkedList * i) {
    if (NULL == i || NULL == i->data) {
        return value;
    }
    
    return (sum == exec(sum, value + *(long long*)i->data, i->next) || 
            sum == exec(sum, value * *(long long*)i->data, i->next) ||
            sum == exec(sum, concatenate(value, *(long long*)i->data), i->next)) ? sum : 0;
}

long long concatenate(long long a, long long b) {
    char buffer[256] = {0};
    sprintf(buffer, "%lld%lld", a, b);
    return atoll(buffer);
}