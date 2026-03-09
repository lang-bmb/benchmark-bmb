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
        int64_t max_grad = 0;
        for (int64_t i = 1; i < N; i++) {
            int64_t diff = arr[i] - arr[i-1];
            if (diff < 0) diff = -diff;
            if (diff > max_grad) max_grad = diff;
        }
        checksum += max_grad;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
