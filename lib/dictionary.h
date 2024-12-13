#pragma once

// Setting this too low gives our entropy too low... had a blast with collisions...
#define DICTIONARY_SIZE 100000
#define PRIME_NUMBER 31

// Doing this makes this a singleton
void* hashMap[DICTIONARY_SIZE] = {0};

int hashIndex(char *);
void addDictionary(char *, void *);
void * getDictionary(char *);

void addDictionary(char * key, void * value) {
    hashMap[hashIndex(key)] = value;
}

void * getDictionary(char * key) {
    return hashMap[hashIndex(key)];
}

int hashIndex(char * key) {
    int hash = 0;
    for (int i = 0; i < strlen(key); i++) {
        hash = key[i] + PRIME_NUMBER * hash;
    }
    return hash % DICTIONARY_SIZE;
}
