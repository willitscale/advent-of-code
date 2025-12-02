#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* filePointer;
    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    ssize_t i = 50;
    ssize_t delta = 0;

    filePointer = fopen("input2.txt", "r");

    if (NULL == filePointer) {
        return EXIT_FAILURE;
    }

    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }

        char direction = line[0];
        long int x = strtol(&line[1], NULL, 0) % 100;
        if (76 == direction) {
            i = (i - x + 100);
        } else if (82 == direction) {
            i = (i + x);
        } else {
            continue;
        }

        i %= 100;

        if (i == 0) {
            delta++;
        }

        line = NULL;
    }

    fclose(filePointer);

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}
