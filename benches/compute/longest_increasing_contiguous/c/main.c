// Longest Increasing Contiguous — length of longest strictly increasing contiguous subarray
// Measures: sequential scan, register carry (prev, cur_len, max_len)
// Workload: N=2000000 array, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t longest_inc_contig(int64_t* arr, int64_t n) {
    if (n <= 1) return n;
    int64_t max_len = 1;
    int64_t cur_len = 1;
    int64_t prev = arr[0];
    for (int64_t i = 1; i < n; i++) {
        int64_t cur = arr[i];
        if (cur > prev) {
            cur_len++;
            if (cur_len > max_len) max_len = cur_len;
        } else {
            cur_len = 1;
        }
        prev = cur;
    }
    return max_len;
}

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 1000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 100;
        }
        checksum += longest_inc_contig(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
