// Longest Run — find longest consecutive run of same value
// Measures: sequential scan, branch prediction
// Workload: N=1000000, 3000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 3000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 5;  // Small alphabet for longer runs
        }

        int64_t max_run = 1;
        int64_t cur_run = 1;
        for (int64_t i = 1; i < N; i++) {
            if (arr[i] == arr[i - 1]) {
                cur_run++;
                if (cur_run > max_run) max_run = cur_run;
            } else {
                cur_run = 1;
            }
        }
        checksum += max_run;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
