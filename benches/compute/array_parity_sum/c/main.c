// Parity Sum — sum odd-indexed elements minus even-indexed with carry
// Measures: register-carry (running sum, parity), sequential scan
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
            arr[i] = seed % 10000;
        }
        int64_t even_sum = 0, odd_sum = 0;
        int64_t max_diff = 0;
        for (int64_t i = 0; i < N; i++) {
            if (i % 2 == 0) even_sum += arr[i];
            else odd_sum += arr[i];
            int64_t diff = even_sum - odd_sum;
            if (diff < 0) diff = -diff;
            if (diff > max_diff) max_diff = diff;
        }
        checksum += max_diff;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
