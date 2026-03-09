// Max Subarray Product — Kadane variant for products
// Measures: register-carry (max_prod, min_prod), sequential scan
// Workload: N=2000000, 2000 iterations, small values

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
            arr[i] = (seed % 5) - 2; // -2 to 2
        }
        int64_t max_prod = arr[0], min_prod = arr[0], result = arr[0];
        for (int64_t i = 1; i < N; i++) {
            int64_t v = arr[i];
            int64_t a = max_prod * v, b = min_prod * v;
            int64_t new_max = v;
            if (a > new_max) new_max = a;
            if (b > new_max) new_max = b;
            int64_t new_min = v;
            if (a < new_min) new_min = a;
            if (b < new_min) new_min = b;
            max_prod = new_max;
            min_prod = new_min;
            if (max_prod > result) result = max_prod;
        }
        checksum += result;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
