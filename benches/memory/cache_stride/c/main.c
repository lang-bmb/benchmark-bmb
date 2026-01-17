// Memory Benchmark: Cache Stride (C baseline)
// Goal: Measure cache line access pattern performance
//
// Tests sequential vs strided access to measure cache efficiency

#include <stdio.h>
#include <stdint.h>

#define SIZE 64
#define ITERATIONS 10000

// Sequential sum - cache-friendly (stride 1)
int64_t sum_sequential(int64_t* arr) {
    int64_t acc = 0;
    for (int i = 0; i < SIZE; i++) {
        acc += arr[i];
    }
    return acc;
}

// Strided sum - cache-unfriendly (stride 8)
int64_t sum_strided(int64_t* arr) {
    int64_t acc = 0;
    for (int i = 0; i < SIZE; i += 8) {
        acc += arr[i];
    }
    return acc;
}

int main() {
    int64_t arr[SIZE];
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }

    int64_t seq_total = 0;
    int64_t strided_total = 0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        seq_total += sum_sequential(arr);
        strided_total += sum_strided(arr);
    }

    printf("Sequential: %lld, Strided: %lld\n",
           (long long)seq_total, (long long)strided_total);
    return 0;
}
