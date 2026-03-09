// Wiggle Sort — ensure a[0]<=a[1]>=a[2]<=a[3]...
// Measures: conditional swaps, register carry
// Workload: N=2000000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10000;
        }

        for (int64_t i = 0; i < N - 1; i++) {
            if (i % 2 == 0) {
                // even index: should be <=
                if (arr[i] > arr[i+1]) {
                    int64_t t = arr[i]; arr[i] = arr[i+1]; arr[i+1] = t;
                }
            } else {
                // odd index: should be >=
                if (arr[i] < arr[i+1]) {
                    int64_t t = arr[i]; arr[i] = arr[i+1]; arr[i+1] = t;
                }
            }
        }

        checksum += arr[0] + arr[N/2] + arr[N-1];
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
