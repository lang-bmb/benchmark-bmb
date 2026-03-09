// Max Product Subarray — track min/max products
// Measures: register tracking (min/max/prev), conditional updates
// Workload: N=1000000, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 1000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = (seed % 21) - 10; // range [-10, 10]
        }

        int64_t max_prod = arr[0];
        int64_t cur_max = arr[0];
        int64_t cur_min = arr[0];

        for (int64_t i = 1; i < N; i++) {
            int64_t val = arr[i];
            int64_t a = cur_max * val;
            int64_t b = cur_min * val;

            // new cur_max = max(val, a, b)
            int64_t new_max = val;
            if (a > new_max) new_max = a;
            if (b > new_max) new_max = b;

            // new cur_min = min(val, a, b)
            int64_t new_min = val;
            if (a < new_min) new_min = a;
            if (b < new_min) new_min = b;

            cur_max = new_max;
            cur_min = new_min;

            if (cur_max > max_prod) max_prod = cur_max;
        }
        checksum += max_prod;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
