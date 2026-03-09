// Bucket sort benchmark — sort uniform distribution with bucket + insertion sort
// Measures: scatter/gather patterns, insertion sort, memory access
// Workload: N=500000, values 0..999999, 1000 buckets, 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Each bucket: count at offset 0, then elements starting at offset 1
// bucket_base + bucket_id * bucket_stride * 8
// bucket_stride = max_per_bucket + 1 (1 for count)

static void bucket_sort(int64_t* arr, int64_t n, int64_t* buckets,
                         int64_t num_buckets, int64_t max_val, int64_t bucket_stride) {
    // Clear bucket counts
    for (int64_t b = 0; b < num_buckets; b++) {
        buckets[b * bucket_stride] = 0;  // count = 0
    }

    // Distribute into buckets
    for (int64_t i = 0; i < n; i++) {
        int64_t b = arr[i] * num_buckets / max_val;
        if (b >= num_buckets) b = num_buckets - 1;
        int64_t cnt = buckets[b * bucket_stride];
        buckets[b * bucket_stride + 1 + cnt] = arr[i];
        buckets[b * bucket_stride] = cnt + 1;
    }

    // Insertion sort within each bucket, then gather
    int64_t pos = 0;
    for (int64_t b = 0; b < num_buckets; b++) {
        int64_t cnt = buckets[b * bucket_stride];
        int64_t base = b * bucket_stride + 1;

        // Insertion sort
        for (int64_t i = 1; i < cnt; i++) {
            int64_t key = buckets[base + i];
            int64_t j = i - 1;
            while (j >= 0 && buckets[base + j] > key) {
                buckets[base + j + 1] = buckets[base + j];
                j--;
            }
            buckets[base + j + 1] = key;
        }

        // Gather back
        for (int64_t i = 0; i < cnt; i++) {
            arr[pos] = buckets[base + i];
            pos++;
        }
    }
}

int main() {
    int64_t N = 500000;
    int64_t MAX_VAL = 1000000;
    int64_t NUM_BUCKETS = 1000;
    int64_t ITERS = 100;
    // Max per bucket: N/NUM_BUCKETS * 4 (safety margin)
    int64_t MAX_PER_BUCKET = (N / NUM_BUCKETS) * 4;
    int64_t BUCKET_STRIDE = MAX_PER_BUCKET + 1;

    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* buckets = (int64_t*)malloc(NUM_BUCKETS * BUCKET_STRIDE * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % MAX_VAL;
        }

        bucket_sort(arr, N, buckets, NUM_BUCKETS, MAX_VAL, BUCKET_STRIDE);

        checksum += arr[0] + arr[N / 2] + arr[N - 1];
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    free(buckets);
    return 0;
}
