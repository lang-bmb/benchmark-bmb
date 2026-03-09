// Interval Merge — sort + merge overlapping intervals
// Measures: sorting, linear scan, conditional merging
// Workload: N=3000 intervals, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void insertion_sort(int64_t n, int64_t* starts, int64_t* ends) {
    for (int64_t i = 1; i < n; i++) {
        int64_t ks = starts[i];
        int64_t ke = ends[i];
        int64_t j = i - 1;
        while (j >= 0 && starts[j] > ks) {
            starts[j + 1] = starts[j];
            ends[j + 1] = ends[j];
            j--;
        }
        starts[j + 1] = ks;
        ends[j + 1] = ke;
    }
}

static int64_t merge_intervals(int64_t n, int64_t* starts, int64_t* ends) {
    if (n == 0) return 0;
    int64_t merged = 0;
    int64_t cur_start = starts[0];
    int64_t cur_end = ends[0];
    for (int64_t i = 1; i < n; i++) {
        if (starts[i] <= cur_end) {
            if (ends[i] > cur_end) cur_end = ends[i];
            merged++;
        } else {
            cur_start = starts[i];
            cur_end = ends[i];
        }
    }
    return merged;
}

int main() {
    int64_t N = 3000;
    int64_t ITERS = 200;

    int64_t* starts = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* ends = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t s = seed % 100000;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t e = s + (seed % 1000) + 1;
            starts[i] = s;
            ends[i] = e;
        }
        insertion_sort(N, starts, ends);
        checksum += merge_intervals(N, starts, ends);
    }

    printf("%lld\n", (long long)checksum);
    free(starts);
    free(ends);
    return 0;
}
