#include <stdio.h>
#include <stdlib.h>

#define ARRAY_BUFFER 100000

int compare(const void *a, const void* b) {
    return (*(size_t*)a - *(size_t*)b);
}

int main()
{
    FILE* filePointer;
    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    size_t diff = 0;

    size_t left[ARRAY_BUFFER];
    size_t right[ARRAY_BUFFER];
    int rowIndex = 0;

    filePointer = fopen("input.txt", "r");

    if (NULL == filePointer) {
        return EXIT_FAILURE;
    }

    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }
        
        sscanf(line, "%lu %lu", &left[rowIndex], &right[rowIndex]);
        rowIndex++;
    }

    fclose(filePointer);

    qsort(left, rowIndex, sizeof(size_t), compare);
    qsort(right, rowIndex, sizeof(size_t), compare);

    for(int i = 0;  i < rowIndex; i++) {
        diff += abs(left[i] - right[i]);
    }

    if (line) {
        free(line);
    }

    printf("Diff is %lu\n", diff);

    return EXIT_SUCCESS;
}
