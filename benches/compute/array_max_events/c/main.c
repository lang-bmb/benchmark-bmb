// Array Max Events — maximum non-overlapping events (greedy by end time)
// Measures: sort + greedy sweep, register carry (last_end)
// Workload: N=100000, 500 iterations
// Uses counting sort on end times for O(n+R) sort

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 100000;
    int64_t ITERS = 500;
    int64_t RANGE = 100000;  // end times in [1, RANGE]
    int64_t* starts = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* ends = (int64_t*)malloc(N * sizeof(int64_t));
    // For counting sort by end time
    int64_t* count = (int64_t*)malloc((RANGE + 1) * sizeof(int64_t));
    int64_t* sorted_starts = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* sorted_ends = (int64_t*)malloc(N * sizeof(int64_t));

    // Generate events: start in [0, RANGE-1000), duration in [1, 1000]
    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        starts[i] = seed % (RANGE - 1000);
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t dur = (seed % 1000) + 1;
        ends[i] = starts[i] + dur;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Counting sort by end time
        for (int64_t t = 0; t <= RANGE; t++) count[t] = 0;
        for (int64_t i = 0; i < N; i++) count[ends[i]]++;
        // Prefix sum
        for (int64_t t = 1; t <= RANGE; t++) count[t] += count[t - 1];
        // Place in sorted order (stable, reverse scan)
        for (int64_t i = N - 1; i >= 0; i--) {
            int64_t pos = --count[ends[i]];
            sorted_starts[pos] = starts[i];
            sorted_ends[pos] = ends[i];
        }

        // Greedy: pick events sorted by end time
        int64_t last_end = -1;
        int64_t selected = 0;
        for (int64_t i = 0; i < N; i++) {
            if (sorted_starts[i] >= last_end) {
                selected++;
                last_end = sorted_ends[i];
            }
        }
        checksum += selected;
    }

    printf("%lld\n", (long long)checksum);
    free(starts);
    free(ends);
    free(count);
    free(sorted_starts);
    free(sorted_ends);
    return 0;
}
