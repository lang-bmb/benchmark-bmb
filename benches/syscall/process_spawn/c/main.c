// System Call Benchmark: Process Spawn (C baseline)
// Goal: Measure process creation and execution overhead
//
// Uses system() to spawn child processes

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ITERATIONS 100

// Spawn a minimal process
int64_t spawn_process() {
    return (int64_t)system("echo test > nul 2>&1");
}

int main() {
    int64_t total = 0;

    for (int i = 0; i < ITERATIONS; i++) {
        total += spawn_process();
    }

    printf("Total: %lld\n", (long long)total);
    return 0;
}
