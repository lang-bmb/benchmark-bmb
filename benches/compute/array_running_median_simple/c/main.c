// Array Running Median Simple — running median via insertion into small sorted buffer (window=21)
// Measures: small-buffer insertion sort, register carry, sequential scan
// Workload: N=500000, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void insert_sorted(int64_t* buf, int64_t size, int64_t val) {
    int64_t j = size - 1;
    while (j >= 0 && buf[j] > val) {
        buf[j + 1] = buf[j];
        j--;
    }
    buf[j + 1] = val;
}

static void remove_from(int64_t* buf, int64_t size, int64_t val) {
    int64_t j = 0;
    while (j < size && buf[j] != val) j++;
    for (; j < size - 1; j++) {
        buf[j] = buf[j + 1];
    }
}

static int64_t running_median(int64_t* arr, int64_t n, int64_t w) {
    int64_t* buf = (int64_t*)malloc(w * sizeof(int64_t));
    int64_t half = w / 2;
    int64_t median_sum = 0;

    // Initialize buffer with first window, insertion sort
    for (int64_t i = 0; i < w; i++) {
        insert_sorted(buf, i, arr[i]);
    }
    median_sum += buf[half];

    // Slide window
    for (int64_t i = w; i < n; i++) {
        int64_t old_val = arr[i - w];
        int64_t new_val = arr[i];
        remove_from(buf, w, old_val);
        insert_sorted(buf, w - 1, new_val);
        median_sum += buf[half];
    }

    free(buf);
    return median_sum;
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 200;
    int64_t W = 21;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 1000;
        }
        checksum += running_median(arr, N, W);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
