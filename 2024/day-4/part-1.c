#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_BUFFER 100000

char match(char a, char b, char c, char d);

int main()
{
    FILE* filePointer;
    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    size_t delta = 0;

    char* matrix[ARRAY_BUFFER];

    filePointer = fopen("input.txt", "r");

    if (NULL == filePointer) {
        return EXIT_FAILURE;
    }

    int rowIndex = 0;
    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }

        char* eol = strstr(line, "\n");
        size_t len = (eol > line)?eol-line:strlen(line);
        matrix[rowIndex] = calloc(sizeof(char), len);
        strncat(matrix[rowIndex++], line, len);
    }

    fclose(filePointer);

    for(int i = 0; i < rowIndex; i++) {
       for(int j = 0; j < strlen(matrix[i]); j++) {
            if ('X' != matrix[i][j]) {
                continue;
            }

            delta += (i+3<rowIndex && match(matrix[i][j],matrix[i+1][j],matrix[i+2][j],matrix[i+3][j])) ? 1 : 0;
            delta += (j+3<strlen(matrix[i]) && match(matrix[i][j],matrix[i][j+1],matrix[i][j+2],matrix[i][j+3])) ? 1 : 0;

            delta += (i>=3 && match(matrix[i][j],matrix[i-1][j],matrix[i-2][j],matrix[i-3][j])) ? 1 : 0;
            delta += (j>=3 && match(matrix[i][j],matrix[i][j-1],matrix[i][j-2],matrix[i][j-3])) ? 1 : 0;

            delta += (i+3<rowIndex && j+3<strlen(matrix[i]) && match(matrix[i][j],matrix[i+1][j+1],matrix[i+2][j+2],matrix[i+3][j+3])) ? 1 : 0;
            delta += (i>=3 && j>=3 && match(matrix[i][j],matrix[i-1][j-1],matrix[i-2][j-2],matrix[i-3][j-3])) ? 1 : 0;

            delta += (i+3<rowIndex && j>=3 && match(matrix[i][j],matrix[i+1][j-1],matrix[i+2][j-2],matrix[i+3][j-3])) ? 1 : 0;
            delta += (i>=3 && j+3<strlen(matrix[i]) && match(matrix[i][j],matrix[i-1][j+1],matrix[i-2][j+2],matrix[i-3][j+3])) ? 1 : 0;
       }
    }

    if (line) {
        free(line);
    }

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}

char match(char a, char b, char c, char d) {
    const char SEARCH[4] = {a,b,c,d};
    return (0 == strcmp("XMAS", SEARCH));
}
