#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_LENGTH 3 // 0,0
#define MAX_LENGTH 7 // 999,999

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

    while(0 == feof(filePointer) && -1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }

        char *ptr = line, *end = line + strlen(line), *eof = NULL, *tmp;
        while(ptr < end) {
            // Regex is for filthy causals
            ptr = strstr(ptr, "mul(")+4;
            if (line > ptr) {
                ptr = end;
                goto fail;
            }
            
            eof = strstr(ptr, ")");

            char length = eof-ptr;

            if (MIN_LENGTH > length || MAX_LENGTH < length) {
                goto fail;
            }

            char containsComma = 0;
            for(char i = 0; i < length; i++) {
                if (0 != i && i != length-1 && 0 == containsComma && ptr[i] == ',') {
                    containsComma = 1;
                    continue;
                }
                if (ptr[i] < '0' || ptr[i] > '9') {
                    goto fail;
                }
            }

            if (!containsComma) {
                goto fail;
            }

            tmp = calloc(sizeof(char), length+1);
            strncpy(tmp, ptr, length);
            int a, b;
            sscanf(tmp, "%d,%d", &a, &b);
            free(tmp);

            delta += a * b;
            fail:;
        }
    }

    fclose(filePointer);

    if (line) {
        free(line);
    }

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}
