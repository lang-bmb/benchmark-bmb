// Longest Plateau — find longest consecutive equal-value run
// Measures: sequential scan, comparison, simple bookkeeping
// Workload: N=200000 array, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t longest_plateau(const int64_t* arr, int64_t n) {
    if (n == 0) return 0;
    int64_t max_len = 1, cur_len = 1;
    for (int64_t i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1]) {
            cur_len++;
            if (cur_len > max_len) max_len = cur_len;
        } else {
            cur_len = 1;
        }
    }
    return max_len;
}

int main() {
    int64_t N = 200000;
    int64_t ITERS = 5000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 50;  // small range → longer plateaus
        }
        checksum += longest_plateau(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
