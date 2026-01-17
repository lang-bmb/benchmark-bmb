// Memory Benchmark: Pointer Chase (C baseline)
// Goal: Measure linked data structure traversal performance
//
// Uses actual pointers for linked list traversal

#include <stdio.h>
#include <stdint.h>

#define SIZE 64
#define ITERATIONS 10000

typedef struct Node {
    int64_t value;
    struct Node* next;
} Node;

// Chase through linked list
int64_t chase_pointers(Node* head) {
    int64_t acc = 0;
    Node* current = head;
    while (current != NULL) {
        acc += current->value;
        current = current->next;
    }
    return acc;
}

int main() {
    // Create nodes on stack
    Node nodes[SIZE];

    // Initialize as linked list
    for (int i = 0; i < SIZE; i++) {
        nodes[i].value = i + 1;
        nodes[i].next = (i < SIZE - 1) ? &nodes[i + 1] : NULL;
    }

    int64_t total = 0;
    for (int iter = 0; iter < ITERATIONS; iter++) {
        total += chase_pointers(&nodes[0]);
    }

    printf("Total: %lld\n", (long long)total);
    return 0;
}
