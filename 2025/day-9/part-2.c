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

    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }
    }

    fclose(filePointer);

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}
