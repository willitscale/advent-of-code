#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_BUFFER 100000

char match(char a, char b, char c);

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
            if ('A' != matrix[i][j]) {
                continue;
            }

            delta += (i>=1 && j>=1 && j+1<strlen(matrix[i]) && i+1<rowIndex && 
                    match(matrix[i+1][j+1],matrix[i][j],matrix[i-1][j-1]) && 
                    match(matrix[i+1][j-1],matrix[i][j],matrix[i-1][j+1])) ? 1 : 0;
       }

       printf("\n");
    }

    if (line) {
        free(line);
    }

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}

char match(char a, char b, char c) {
    const char SEARCH[3] = {a,b,c};
    return (0 == strcmp("MAS", SEARCH) || 0 == strcmp("SAM", SEARCH)) ? 1 : 0;
}
