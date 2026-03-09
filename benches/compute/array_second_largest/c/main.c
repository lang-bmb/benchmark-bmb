// Array Second Largest — find second largest element in single pass
// Measures: branch prediction, conditional tracking
// Workload: N=1000000, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 5000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed;
        }

        int64_t first = arr[0], second = arr[1];
        if (second > first) {
            int64_t t = first; first = second; second = t;
        }
        for (int64_t i = 2; i < N; i++) {
            if (arr[i] > first) {
                second = first;
                first = arr[i];
            } else if (arr[i] > second) {
                second = arr[i];
            }
        }
        checksum += second;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
