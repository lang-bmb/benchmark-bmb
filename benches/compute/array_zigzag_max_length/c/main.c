// Array Zigzag Max Length — longest zigzag subsequence (alternating diffs)
// Measures: register carry (prev_diff, cur_len, max_len), sequential scan
// Workload: N=2000000 array, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t zigzag_max_length(const int64_t* arr, int64_t n) {
    if (n < 2) return n;
    // prev_sign: 1 = positive, -1 = negative, 0 = zero
    int64_t max_len = 1;
    int64_t cur_len = 1;
    int64_t prev_sign = 0;
    for (int64_t i = 1; i < n; i++) {
        int64_t diff = arr[i] - arr[i - 1];
        int64_t cur_sign;
        if (diff > 0) cur_sign = 1;
        else if (diff < 0) cur_sign = -1;
        else cur_sign = 0;

        if (cur_sign != 0 && cur_sign != prev_sign) {
            cur_len++;
            prev_sign = cur_sign;
        } else if (cur_sign != 0) {
            // Same sign — reset
            cur_len = 2;
            prev_sign = cur_sign;
        }
        if (cur_len > max_len) max_len = cur_len;
    }
    return max_len;
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
            arr[i] = seed % 1000;
        }
        checksum += zigzag_max_length(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
