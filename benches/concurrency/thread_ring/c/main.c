// Thread-Ring - Context switching benchmark
// Reference: Computer Language Benchmarks Game
//
// This is a simplified single-threaded simulation
// Full benchmark uses pthreads

#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 503
#define DEFAULT_PASSES 50000000

typedef struct Thread {
    int id;
    struct Thread *next;
} Thread;

Thread* create_ring(int n) {
    Thread *threads = malloc(n * sizeof(Thread));
    if (!threads) return NULL;

    for (int i = 0; i < n; i++) {
        threads[i].id = i + 1;  // 1-based ID
        threads[i].next = &threads[(i + 1) % n];
    }

    return threads;
}

int pass_token(Thread *ring, long passes) {
    long token = passes;
    Thread *current = ring;

    while (token > 0) {
        token--;
        if (token == 0) {
            return current->id;
        }
        current = current->next;
    }

    return current->id;
}

int main(int argc, char *argv[]) {
    long passes = DEFAULT_PASSES;
    if (argc > 1) {
        passes = atol(argv[1]);
    }

    Thread *ring = create_ring(NUM_THREADS);
    if (!ring) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }

    int winner = pass_token(ring, passes);
    printf("%d\n", winner);

    free(ring);
    return 0;
}
