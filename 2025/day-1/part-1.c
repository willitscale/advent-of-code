#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* filePointer;
    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    ssize_t i = 50, x;
    ssize_t delta = 0;

    filePointer = fopen("input2.txt", "r");

    if (NULL == filePointer) {
        return EXIT_FAILURE;
    }

    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }

        x = strtol(&line[1], NULL, 0) % 100;
        if ('L' == line[0]) {
            i = (i - x + 100);
        } else if ('R' == line[0]) {
            i = (i + x);
        } else {
            continue;
        }

        delta += (i % 100 == 0) ? 1 : 0;

        line = NULL;
    }

    fclose(filePointer);

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}
