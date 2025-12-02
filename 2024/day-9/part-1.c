#include "../lib/include.h"

#define BUFFER 100000

int main()
{
    FILE* filePointer;
    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    long long delta = 0;

    filePointer = fopen("input.txt", "r");

    if (NULL == filePointer) {
        return EXIT_FAILURE;
    }

    char* m[BUFFER];
    int b[BUFFER];
    int i = 0, n = 0;

    LinkedList *unique = initLinkedList();

    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }

        char* eol = strstr(line, "\n");
        size_t len = (eol > line)?eol-line-1:strlen(line);
        m[i] = calloc(sizeof(char), len);
        strncat(m[i], line, len);

        for(int j = 0; j < strlen(m[i]); j++) {
            int v = m[i][j] - 48;
            for(int x = 0; x < v; x++) {
                b[n++] = (0 == j % 2) ? (j/2): -1;
            }
        }
        i++;
    }

    int first = 0, last = n-1;
    while(last > first) {
        while(b[first] != -1) {
            first++;
        }
        
        while(b[last] == -1) {
            last--;
        }

        if (last < first) {
            continue;
        }

        int tmp = b[first];
        b[first] = b[last];
        b[last] = tmp;
    }
    
    for (int z = 0; -1 != b[z]; z++) {
        delta += (b[z]*z);
    }

    fclose(filePointer);

    if (line) {
        free(line);
    }

    printf("Delta is %llu\n", delta);

    return EXIT_SUCCESS;
}
