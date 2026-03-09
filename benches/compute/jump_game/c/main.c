// Jump Game — greedy max reach
// Measures: register tracking (max_reach), sequential scan
// Workload: N=2000000, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 1000;
    int64_t* nums = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            nums[i] = seed % 5;
        }

        // Greedy: track max reachable index
        int64_t max_reach = 0;
        int64_t can_reach = 1;
        for (int64_t i = 0; i < N; i++) {
            if (i > max_reach) {
                can_reach = 0;
                break;
            }
            int64_t reach = i + nums[i];
            if (reach > max_reach) max_reach = reach;
            if (max_reach >= N - 1) break;
        }
        checksum += can_reach + max_reach;
    }
    printf("%lld\n", (long long)checksum);
    free(nums);
    return 0;
}
