#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main() {
    int64_t N = 2000000, ITERS = 500, K = 16;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0, seed = 42;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) { seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF; arr[i] = seed % 100000; }
        int64_t total = 0;
        for (int64_t i = 0; i <= N - K; i++) {
            int64_t mn = arr[i], mx = arr[i];
            for (int64_t j = 1; j < K; j++) {
                int64_t v = arr[i+j];
                if (v < mn) mn = v;
                if (v > mx) mx = v;
            }
            total += mx - mn;
        }
        checksum += total % 1000000007;
    }
    printf("%lld\n", (long long)checksum);
    free(arr); return 0;
}
