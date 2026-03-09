// Array Min Platforms — minimum platforms needed for overlapping intervals
// Measures: counting sort, sweep line, register carry (cur_platforms, max_platforms)
// Workload: N=100000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 100000;
    int64_t ITERS = 500;
    int64_t RANGE = 10000;  // time range 0..9999
    int64_t* arrivals = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* departures = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* timeline = (int64_t*)malloc((RANGE + 1) * sizeof(int64_t));

    // Generate events: arrival in [0, RANGE-1000), duration in [1, 1000]
    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        arrivals[i] = seed % (RANGE - 1000);
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t dur = (seed % 1000) + 1;
        departures[i] = arrivals[i] + dur;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Clear timeline
        for (int64_t t = 0; t <= RANGE; t++) timeline[t] = 0;

        // Mark arrivals (+1) and departures (-1)
        for (int64_t i = 0; i < N; i++) {
            timeline[arrivals[i]]++;
            if (departures[i] <= RANGE) {
                timeline[departures[i]]--;
            }
        }

        // Sweep to find max concurrent
        int64_t cur_platforms = 0;
        int64_t max_platforms = 0;
        for (int64_t t = 0; t <= RANGE; t++) {
            cur_platforms += timeline[t];
            if (cur_platforms > max_platforms) max_platforms = cur_platforms;
        }
        checksum += max_platforms;
    }

    printf("%lld\n", (long long)checksum);
    free(arrivals);
    free(departures);
    free(timeline);
    return 0;
}
