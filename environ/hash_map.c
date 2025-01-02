#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TABLE_SIZE 101

typedef struct Entry {
    int key;
    int value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry *table[TABLE_SIZE];
} HashTable;

unsigned int hash_function(int key) {
    return abs(key) % TABLE_SIZE;
}

HashTable *create_hash_table() {
    HashTable *ht = (HashTable *)calloc(1, sizeof(HashTable));
    if (ht == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    return ht;
}

void insert(HashTable *ht, int key, int value) {
    if (ht == NULL) return;

    unsigned int index = hash_function(key);
    Entry *new_node = malloc(sizeof(Entry));
    if (new_node == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    new_node->key = key;
    new_node->value = value;
    new_node->next = ht->table[index];
    ht->table[index] = new_node;
}

int search(HashTable *ht, int key) {
    if (ht == NULL) return -1;

    unsigned int index = hash_function(key);
    Entry *current = ht->table[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void free_hash_table(HashTable *ht) {
    if (ht == NULL) return;

    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *current = ht->table[i];
        while (current != NULL) {
            Entry *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht);
}

int cmpfunc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}
