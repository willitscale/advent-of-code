#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* filePointer;
    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    ssize_t j = 50, i = 50, x, r;
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
        x = strtol(&line[1], NULL, 0);
        r = x / 100;
        
        x %= 100;

        if (76 == direction) {
            i = (i - x + 100) % 100;
            r += (i > j && j != 0 || i == 0) ? 1 : 0;
        } else if (82 == direction) {
            i = (i + x) % 100;
            r += (i < j && j != 0 || i == 0) ? 1 : 0;
        } else {
            continue;
        }

        delta+= r;

        j = i;

        line = NULL;
    }

    fclose(filePointer);

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}
