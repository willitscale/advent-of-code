#pragma once

#define INT_LENGTH 11

typedef struct ll
{
  void* data;
  struct ll *next;
} LinkedList;

LinkedList *addToLinkedList(LinkedList *, void *);
LinkedList *initLinkedList();
void freeLinkedList(LinkedList *);

LinkedList *initLinkedList()
{
  return calloc(1, sizeof(LinkedList));
}

LinkedList *addToLinkedList(LinkedList *linkedList, void *data)
{
  LinkedList *next = initLinkedList();
  linkedList->data = data;
  linkedList->next = next;
  return next;
}

void freeLinkedList(LinkedList *linkedList)
{
  while (NULL != linkedList)
  {
    free(linkedList->data);
    LinkedList *tmp = linkedList;
    linkedList = linkedList->next;
    free(tmp);
  }
}

void addOrderedLinkedList(LinkedList *linkedList, void *data, int (*comparison)(void *,void *))
{
  if (NULL == linkedList->data) {
    linkedList->data = data;
    return;
  }

  LinkedList *newRow = initLinkedList();
  newRow->data = data;
  LinkedList *current = linkedList;

  while(NULL != current->next && comparison(data, current->data)) {
    current = current->next;
  }
  
  newRow->next = current->next;
  current->next = newRow;

  if (!comparison(data, current->data)) {
    newRow->data = current->data;
    current->data = data;
  }
}

LinkedList* explodeNumbers(const char *delimiter, char *string, int *parts) {
    char *start = string, *end = strstr(string, delimiter);

    if (NULL == end) {
        return NULL;
    }

    size_t length = strlen(string);
    LinkedList *data = initLinkedList(), *head = data;

    while (end > string) {
        int *page = calloc(sizeof(int), 1);
        char buf[INT_LENGTH];
        strncpy(buf, start, end-start > INT_LENGTH ? INT_LENGTH:end-start);
        *page = atoi(buf);
        data = addToLinkedList(data, page);
        (*parts)++;

        if (end == start + length) {
            break;
        }

        start = end+1;
        end = strstr(end+1, delimiter);
            
        if (NULL == end) {
            end = start + length;
        }
    }

    return head;
}