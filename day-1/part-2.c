#include <stdio.h>
#include <stdlib.h>

#define ARRAY_BUFFER 100000

int main()
{
    FILE* filePointer;
    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    size_t delta = 0;

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

    for(int i = 0;  i < rowIndex; i++) {
        for(int j = 0; j < rowIndex; j++) {
            if (left[i] == right[j]) {
                delta += left[i];
            }
        }
    }

    if (line) {
        free(line);
    }

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}
