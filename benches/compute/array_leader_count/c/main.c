// Leader Count — count elements greater than all following elements
// Measures: reverse scan with register-carry (suffix max)
// Workload: N=2000000, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000, ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0, seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 100000;
        }
        int64_t count = 1;
        int64_t suffix_max = arr[N-1];
        for (int64_t i = N - 2; i >= 0; i--) {
            if (arr[i] > suffix_max) {
                count++;
                suffix_max = arr[i];
            }
        }
        checksum += count;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
