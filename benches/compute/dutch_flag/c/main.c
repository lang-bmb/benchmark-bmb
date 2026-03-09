// Dutch National Flag — 3-way partition (Dijkstra's algorithm)
// Measures: swap operations, single-pass O(n) partitioning
// Workload: 500K elements (values 0,1,2), 500 iterations with different seeds

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void swap(int64_t* arr, int64_t i, int64_t j) {
    int64_t tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

static void dutch_flag(int64_t* arr, int64_t n) {
    int64_t lo = 0, mid = 0, hi = n - 1;
    while (mid <= hi) {
        int64_t val = arr[mid];
        if (val == 0) {
            swap(arr, lo, mid);
            lo++;
            mid++;
        } else if (val == 1) {
            mid++;
        } else {
            swap(arr, mid, hi);
            hi--;
        }
    }
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 3;
        }
        dutch_flag(arr, N);
        // Checksum: sample first, middle, last elements + boundary positions
        checksum += arr[0] + arr[N / 2] + arr[N - 1];
        // Verify partition: find first 1 and first 2
        int64_t f1 = 0;
        while (f1 < N && arr[f1] < 1) f1++;
        int64_t f2 = f1;
        while (f2 < N && arr[f2] < 2) f2++;
        checksum += f1 + f2;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
