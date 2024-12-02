#pragma once

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
