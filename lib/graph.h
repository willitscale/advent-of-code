#pragma once

typedef struct n {
    LinkedList *edges;
    void * value;
} Node;

typedef struct e {
    Node *node;
    void * value;
} Edge;

