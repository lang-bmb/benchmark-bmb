// Memory Benchmark: Memory Copy (C baseline)
// Goal: Measure memcpy performance
//
// C uses explicit memcpy for array copying

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SIZE 32
#define ITERATIONS 10000

// Copy array using memcpy
void copy_array(int64_t* dst, int64_t* src) {
    memcpy(dst, src, SIZE * sizeof(int64_t));
}

// Sum array elements
int64_t sum_array(int64_t* arr) {
    int64_t acc = 0;
    for (int i = 0; i < SIZE; i++) {
        acc += arr[i];
    }
    return acc;
}

int main() {
    int64_t arr[SIZE];
    int64_t copied[SIZE];

    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }

    int64_t total = 0;
    for (int iter = 0; iter < ITERATIONS; iter++) {
        copy_array(copied, arr);
        total += sum_array(copied);
    }

    printf("Total: %lld\n", (long long)total);
    return 0;
}
