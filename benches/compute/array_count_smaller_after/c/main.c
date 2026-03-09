// Array Count Smaller After — for each element, count how many smaller elements follow
// Measures: O(n^2) brute force, register carry (count per element)
// Workload: N=10000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 10000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        arr[i] = seed % 100000;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t total = 0;
        for (int64_t i = 0; i < N; i++) {
            int64_t count = 0;
            for (int64_t j = i + 1; j < N; j++) {
                if (arr[j] < arr[i]) count++;
            }
            total += count;
        }
        checksum += total;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
