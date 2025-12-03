#include <stdio.h>
#include <stdlib.h>
#include "../../lib/include.h"

int main()
{
    FILE* filePointer;
    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    ssize_t delta = 0, r1 = 0, r2 = 0;
    char * s, * e, * n1, * n2, * r, * o, * d;

    filePointer = fopen("input2.txt", "r");

    if (NULL == filePointer) {
        return EXIT_FAILURE;
    }

    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }
        
        size_t l = strlen(line);
        s = line;

        do {
            e = strstr(s, ",");
            o = (e ? e : s+length);

            r = calloc(sizeof(char), o - s + 1);
            strncpy(r, s, o - s);
            
            d = strstr(s, "-");

            n1 = calloc(sizeof(char), d - s + 1);
            n2 = calloc(sizeof(char), o - d + 1);

            strncpy(n1, s, d - s);
            strncpy(n2, d + 1, o - d - 1);

            r1 = strtol(n1, NULL, 10);
            r2 = strtol(n2, NULL, 10);

            for (r1; r1 <= r2; r1++) {
                char i[255];
                sprintf(i, "%lu", r1);
                if (strlen(i) % 2 != 0) {
                    continue;
                }
                size_t d = strlen(i) / 2;
                char firstHalf[128];
                char secondHalf[128];
                strncpy(firstHalf, i, d);
                strncpy(secondHalf, i + d, d);
                firstHalf[d] = '\0';
                secondHalf[d] = '\0';
                if (strcmp(firstHalf, secondHalf) == 0) {
                    delta+= r1;
                }
            }

            free(r);
            s = e + 1;
        } while (e);
    }

    fclose(filePointer);

    printf("Delta is %lu\n", delta);

    return EXIT_SUCCESS;
}
