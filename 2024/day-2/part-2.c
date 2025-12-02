#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEVEL_TOLLERANCE_MIN 1
#define LEVEL_TOLLERANCE_MAX 3
#define FAULT_TOLLERANCE 1

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

        size_t prevNum = -1, curNum;
        char *ptr = NULL, *start = line, *end = start + strlen(line);
        char curDir, prevDir = -1, faults = 1;

        while(ptr != end+1) {
            ptr = strstr(start, " ")+1;
            ptr = (!(ptr-1)) ? end+1 : ptr;

            char * number = calloc(sizeof(char), sizeof(size_t));
            memcpy(number, start, ptr-start-1);
            start = ptr;

            curNum = atol(number);
            free(number);
            curDir = (0 >= (ssize_t)(curNum-prevNum));

            int diff = abs(curNum-prevNum);

            if (((-1 != prevNum && (LEVEL_TOLLERANCE_MIN > diff || LEVEL_TOLLERANCE_MAX < diff) ) || 
                 (-1 != prevDir && curDir != prevDir)) && faults++ > FAULT_TOLLERANCE) {
                goto fail; // YOLO
            }

            if (-1 != prevNum) {
                prevDir = curDir;
            }
            prevNum = curNum;
        }
        
        delta++;
        fail:;
    }

    fclose(filePointer);

    if (line) {
        free(line);
    }

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}
