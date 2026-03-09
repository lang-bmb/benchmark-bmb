// Array Remove Dups Sorted — remove duplicates from sorted array in-place
// Measures: sequential scan, conditional writes
// Workload: N=500000, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 500000;
    int64_t ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate sorted array with duplicates
        int64_t val = 0;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            val += seed % 3;  // Small increments = many duplicates
            arr[i] = val;
        }

        // Remove duplicates in-place
        int64_t k = 1;
        for (int64_t i = 1; i < N; i++) {
            if (arr[i] != arr[k - 1]) {
                arr[k] = arr[i];
                k++;
            }
        }
        checksum += k + arr[0] + arr[k - 1];
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
