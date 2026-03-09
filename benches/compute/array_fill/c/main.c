// Array Fill — fill array with computed values
// Measures: sequential write, simple computation
// Workload: N=1000000, 10000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 10000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            arr[i] = i * 3 + 7;
        }
        checksum += arr[0] + arr[N - 1];
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
