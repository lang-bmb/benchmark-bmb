// Array Sorted Merge In-Place — merge two sorted halves without extra space
// Measures: gap-based merge, sequential swaps
// Workload: N=200000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 200000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate two sorted halves
        int64_t half = N / 2;
        int64_t val = 0;
        for (int64_t i = 0; i < half; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            val += seed % 5 + 1;
            arr[i] = val;
        }
        val = 0;
        for (int64_t i = half; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            val += seed % 5 + 1;
            arr[i] = val;
        }

        // Shell-sort-like gap merge
        int64_t gap = N;
        while (gap > 0) {
            gap = (gap <= 1) ? 0 : (gap + 1) / 2;
            if (gap == 0) break;
            for (int64_t i = 0; i + gap < N; i++) {
                if (arr[i] > arr[i + gap]) {
                    int64_t t = arr[i];
                    arr[i] = arr[i + gap];
                    arr[i + gap] = t;
                }
            }
        }

        checksum += arr[0] + arr[N / 2] + arr[N - 1];
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
