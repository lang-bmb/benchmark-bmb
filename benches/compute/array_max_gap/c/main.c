// Maximum Gap — find max difference between consecutive sorted elements
// Measures: bucket sort approach, register tracking
// Workload: N=1000000, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 200;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    // Bucket: [used, min, max] per bucket
    int64_t* bucket_used = (int64_t*)malloc((N + 1) * sizeof(int64_t));
    int64_t* bucket_min = (int64_t*)malloc((N + 1) * sizeof(int64_t));
    int64_t* bucket_max = (int64_t*)malloc((N + 1) * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t lo = 0x7FFFFFFFFFFFFFFF, hi = 0;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed;
            if (arr[i] < lo) lo = arr[i];
            if (arr[i] > hi) hi = arr[i];
        }

        if (hi == lo) { checksum += 0; continue; }

        int64_t num_buckets = N;
        int64_t range = hi - lo;

        memset(bucket_used, 0, num_buckets * sizeof(int64_t));

        for (int64_t i = 0; i < N; i++) {
            int64_t idx = (arr[i] - lo) * (num_buckets - 1) / range;
            if (!bucket_used[idx]) {
                bucket_used[idx] = 1;
                bucket_min[idx] = arr[i];
                bucket_max[idx] = arr[i];
            } else {
                if (arr[i] < bucket_min[idx]) bucket_min[idx] = arr[i];
                if (arr[i] > bucket_max[idx]) bucket_max[idx] = arr[i];
            }
        }

        int64_t max_gap = 0;
        int64_t prev_max = lo;
        for (int64_t i = 0; i < num_buckets; i++) {
            if (bucket_used[i]) {
                int64_t gap = bucket_min[i] - prev_max;
                if (gap > max_gap) max_gap = gap;
                prev_max = bucket_max[i];
            }
        }
        checksum += max_gap;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    free(bucket_used);
    free(bucket_min);
    free(bucket_max);
    return 0;
}
