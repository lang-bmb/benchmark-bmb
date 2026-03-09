// array_circular_max — Max subarray sum in circular array
// Measures: register-carried Kadane max+min in single pass (4 accumulators)
// Workload: N=2000000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t circular_max(const int64_t* arr, int64_t n) {
    int64_t total = 0;
    int64_t max_sum = arr[0], cur_max = arr[0];
    int64_t min_sum = arr[0], cur_min = arr[0];
    for (int64_t i = 0; i < n; i++) {
        int64_t v = arr[i];
        total += v;
        if (i > 0) {
            cur_max = v + ((cur_max > 0) ? cur_max : 0);
            if (cur_max > max_sum) max_sum = cur_max;
            cur_min = v + ((cur_min < 0) ? cur_min : 0);
            if (cur_min < min_sum) min_sum = cur_min;
        }
    }
    int64_t wrap_sum = total - min_sum;
    // If all negative, wrap_sum would be 0, use max_sum
    if (wrap_sum > max_sum && wrap_sum != 0) return wrap_sum;
    return max_sum;
}

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = (seed % 201) - 100;
        }
        checksum += circular_max(arr, N);
        seed = (seed + iter) & 0x7FFFFFFF;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
