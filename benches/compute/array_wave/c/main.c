// Array Wave — arrange array in wave form (a[0]>=a[1]<=a[2]>=a[3]...)
// Measures: swap operations, sequential access
// Workload: N=500000, 3000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 500000;
    int64_t ITERS = 3000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 1000000;
        }

        // Wave sort: at even indices, element should be >= neighbors
        for (int64_t i = 0; i < N; i += 2) {
            if (i > 0 && arr[i] < arr[i - 1]) {
                int64_t t = arr[i]; arr[i] = arr[i - 1]; arr[i - 1] = t;
            }
            if (i < N - 1 && arr[i] < arr[i + 1]) {
                int64_t t = arr[i]; arr[i] = arr[i + 1]; arr[i + 1] = t;
            }
        }

        checksum += arr[0] + arr[N / 2] + arr[N - 1];
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
