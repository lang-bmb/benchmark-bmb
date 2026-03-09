// Integral — running integral (cumulative sum) with max tracking
// Measures: accumulator, sequential scan
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
            arr[i] = seed % 1000 - 500;
        }
        int64_t integral = 0;
        int64_t max_int = 0;
        int64_t min_int = 0;
        for (int64_t i = 0; i < N; i++) {
            integral += arr[i];
            if (integral > max_int) max_int = integral;
            if (integral < min_int) min_int = integral;
        }
        checksum += max_int - min_int;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
