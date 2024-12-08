#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 500

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3



int main()
{
    FILE* filePointer;
    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    size_t delta = 0;

    filePointer = fopen("test.txt", "r");

    if (NULL == filePointer) {
        return EXIT_FAILURE;
    }

    int i = 0;
    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }

        char* eol = strstr(line, "\n");
        size_t len = (eol > line)?eol-line-1:strlen(line);
        m[i] = calloc(sizeof(char), len);
        strncat(m[i++], line, len);

        int total;

        sscanf(line, "%d", &total);

        printf("Total %d\n", total);

    }

    fclose(filePointer);

    if (line) {
        free(line);
    }

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}
