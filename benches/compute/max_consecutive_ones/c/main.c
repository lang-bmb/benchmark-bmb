// Max Consecutive Ones — track current/max run length
// Measures: register carry (cur_count, max_count), sequential scan
// Workload: N=2000000, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 1000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 2;
        }

        int64_t max_count = 0;
        int64_t cur_count = 0;

        for (int64_t i = 0; i < N; i++) {
            if (arr[i] == 1) {
                cur_count++;
            } else {
                if (cur_count > max_count) max_count = cur_count;
                cur_count = 0;
            }
        }
        if (cur_count > max_count) max_count = cur_count;
        checksum += max_count;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
