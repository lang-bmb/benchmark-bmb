// Longest Alternating Subsequence — DP with register carry
// Measures: register tracking (up/down), sequential scan
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
            arr[i] = seed % 10000;
        }

        // up[i] = length of longest alternating subseq ending with rise at i
        // down[i] = length ending with fall at i
        int64_t up = 1, down = 1;
        int64_t prev = arr[0];

        for (int64_t i = 1; i < N; i++) {
            int64_t cur = arr[i];
            if (cur > prev) {
                up = down + 1;
            } else if (cur < prev) {
                down = up + 1;
            }
            prev = cur;
        }
        int64_t result = (up > down) ? up : down;
        checksum += result;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
