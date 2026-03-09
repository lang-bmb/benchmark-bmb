// Array Search Linear — linear search through unsorted array
// Measures: sequential scan, branch prediction, early exit
// Workload: N=10000 array, 5000 searches, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 10000;
    int64_t SEARCHES = 5000;
    int64_t ITERS = 200;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        arr[i] = seed;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        for (int64_t s = 0; s < SEARCHES; s++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t target = seed;
            int64_t found = -1;
            for (int64_t j = 0; j < N; j++) {
                if (arr[j] == target) {
                    found = j;
                    break;
                }
            }
            checksum += found;
        }
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
