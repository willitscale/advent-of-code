#include "../lib/include.h"

#define BUFFER 100000

typedef struct bl
{
    int start, len, id;
} Block;

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

    LinkedList *unique = initLinkedList(), 
                *freeBlksHead = initLinkedList(), 
                *dataBlksHead = initLinkedList(),
                *freeBlks = freeBlksHead;

    while(-1 != (read = getline(&line, &length, filePointer))) {
        if (0 >= length) {
            continue;
        }

        char* eol = strstr(line, "\n");
        size_t len = (eol > line)?eol-line-1:strlen(line);
        m[i] = calloc(sizeof(char), len);
        strncat(m[i], line, len);

        for(int j = 0; j < strlen(m[i]); j+=2) {
            
            Block * dataBlk = calloc(sizeof(Block), 1);
            Block * freeBlk = calloc(sizeof(Block), 1);

            dataBlksHead = prefixLinkedList(dataBlksHead, dataBlk);
            freeBlks = addToLinkedList(freeBlks, freeBlk);

            dataBlk->start = n;
            dataBlk->len = m[i][j] - 48;
            dataBlk->id = (j/2);

            for(int x = 0; x < dataBlk->len; x++) {
                b[n++] = dataBlk->id;
            }
            
            freeBlk->start = n;
            freeBlk->len = (j+1 >= strlen(m[i])) ? 0 : m[i][j+1] - 48;
            freeBlk->id = dataBlk->id;

            for(int x = 0; x < freeBlk->len; x++) {
                b[n++] = -1;
            }

        }
        i++;
    }

    LinkedList *dataBlks = dataBlksHead;
    while(NULL != dataBlks && NULL != dataBlks->data && NULL != dataBlks->next) {
        Block * dataBlk = (Block*)dataBlks->data;

        freeBlks = freeBlksHead;
        char moved = 0;
        while(!moved && NULL != freeBlks && NULL != freeBlks->data && NULL != freeBlks->next) {
            Block * freeBlk = (Block*)freeBlks->data;
            if (dataBlk->start < freeBlk->start) {
                break;
            }
            if (dataBlk->len <= freeBlk->len) {
                
                for(int h = freeBlk->start; h < freeBlk->start+dataBlk->len; h++) {
                    b[h] = dataBlk->id;
                }
                
                freeBlk->len -= dataBlk->len;
                freeBlk->start += dataBlk->len;
                moved = 1;
            }
            freeBlks = freeBlks->next;
        }

        freeBlks = freeBlksHead;
        while(moved && NULL != freeBlks && NULL != freeBlks->data && NULL != freeBlks->next) {
            Block * freeBlk = (Block*)freeBlks->data;
            if (dataBlk->id == freeBlk->id) {

                for(int h = dataBlk->start; h < dataBlk->start+dataBlk->len; h++) {
                    b[h] = -1;
                }

                freeBlk->len += dataBlk->len;
                freeBlk->start -= dataBlk->len;
                moved = 0;
            }
            freeBlks = freeBlks->next;
        }

        dataBlks = dataBlks->next;
    }
    
    for (int z = 0; z < n; z++) {
        delta += (-1 != b[z]) ? (b[z]*z) : 0;
    }

    fclose(filePointer);

    if (line) {
        free(line);
    }

    printf("Delta is %llu\n", delta);

    return EXIT_SUCCESS;
}
