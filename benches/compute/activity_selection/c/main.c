// Activity Selection benchmark — greedy algorithm
// Measures: sorting, greedy selection, array access patterns
// Workload: N=10000 activities, 500 iterations
// Sort by end time (quicksort), greedily select non-overlapping activities

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t generate_activities(int64_t* starts, int64_t* ends, int64_t n, int64_t seed_in) {
    int64_t seed = seed_in;
    for (int64_t i = 0; i < n; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t s = seed % 100000;
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t duration = (seed % 1000) + 1;
        starts[i] = s;
        ends[i] = s + duration;
    }
    return seed;
}

static void swap_pair(int64_t* starts, int64_t* ends, int64_t i, int64_t j) {
    int64_t tmp_s = starts[i];
    int64_t tmp_e = ends[i];
    starts[i] = starts[j];
    ends[i] = ends[j];
    starts[j] = tmp_s;
    ends[j] = tmp_e;
}

static int64_t qs_partition(int64_t* starts, int64_t* ends, int64_t lo, int64_t hi) {
    int64_t pivot = ends[hi];
    int64_t i = lo;
    for (int64_t j = lo; j < hi; j++) {
        if (ends[j] <= pivot) {
            swap_pair(starts, ends, i, j);
            i++;
        }
    }
    swap_pair(starts, ends, i, hi);
    return i;
}

static void quicksort(int64_t* starts, int64_t* ends, int64_t lo, int64_t hi) {
    if (lo < hi) {
        int64_t p = qs_partition(starts, ends, lo, hi);
        if (p > lo) quicksort(starts, ends, lo, p - 1);
        quicksort(starts, ends, p + 1, hi);
    }
}

static int64_t greedy_select(int64_t* starts, int64_t* ends, int64_t n) {
    int64_t count = 1;
    int64_t last_end = ends[0];
    for (int64_t i = 1; i < n; i++) {
        if (starts[i] >= last_end) {
            count++;
            last_end = ends[i];
        }
    }
    return count;
}

int main() {
    int64_t n = 10000;
    int64_t iters = 500;
    int64_t* starts = (int64_t*)malloc(n * sizeof(int64_t));
    int64_t* ends = (int64_t*)malloc(n * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        generate_activities(starts, ends, n, 12345 + iter * 3);
        quicksort(starts, ends, 0, n - 1);
        int64_t selected = greedy_select(starts, ends, n);
        checksum += selected;
    }

    printf("%lld\n", (long long)checksum);
    free(starts);
    free(ends);
    return 0;
}
