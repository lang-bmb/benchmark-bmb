// Max Circular Subarray Sum — Kadane's + circular trick
// Measures: register tracking (cur_max, cur_min, total)
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
            arr[i] = (seed % 201) - 100; // range [-100, 100]
        }

        int64_t total = 0;
        int64_t max_ending = 0, max_sum = arr[0];
        int64_t min_ending = 0, min_sum = arr[0];

        for (int64_t i = 0; i < N; i++) {
            int64_t val = arr[i];
            total += val;

            max_ending += val;
            if (max_ending > max_sum) max_sum = max_ending;
            if (max_ending < 0) max_ending = 0;

            min_ending += val;
            if (min_ending < min_sum) min_sum = min_ending;
            if (min_ending > 0) min_ending = 0;
        }

        int64_t circular = total - min_sum;
        int64_t result;
        if (total == min_sum) {
            result = max_sum; // all negative
        } else {
            result = (max_sum > circular) ? max_sum : circular;
        }
        checksum += result;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
