// Gas Station — circular tour greedy
// Measures: register tracking (tank, start), sequential scan
// Workload: N=2000000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 500;
    int64_t* gas = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* cost = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            gas[i] = seed % 100;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            cost[i] = seed % 100;
        }

        int64_t total_tank = 0;
        int64_t curr_tank = 0;
        int64_t start = 0;

        for (int64_t i = 0; i < N; i++) {
            int64_t diff = gas[i] - cost[i];
            total_tank += diff;
            curr_tank += diff;
            if (curr_tank < 0) {
                start = i + 1;
                curr_tank = 0;
            }
        }
        int64_t result = (total_tank >= 0) ? start : -1;
        checksum += result;
    }
    printf("%lld\n", (long long)checksum);
    free(gas);
    free(cost);
    return 0;
}
