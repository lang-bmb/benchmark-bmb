// First and Last Position — binary search for range
// Measures: binary search, register tracking
// Workload: N=2000000, 2000 iterations, sorted array

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate sorted array with duplicates
        int64_t val = 0;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            val += seed % 3; // many duplicates
            arr[i] = val;
        }

        // Search for multiple targets
        for (int64_t t = 0; t < 100; t++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t target = seed % (val + 1);

            // Find first position
            int64_t lo = 0, hi = N;
            while (lo < hi) {
                int64_t mid = lo + (hi - lo) / 2;
                if (arr[mid] < target) lo = mid + 1;
                else hi = mid;
            }
            int64_t first = lo;

            // Find last position
            lo = 0; hi = N;
            while (lo < hi) {
                int64_t mid = lo + (hi - lo) / 2;
                if (arr[mid] <= target) lo = mid + 1;
                else hi = mid;
            }
            int64_t last = lo - 1;

            if (first <= last) {
                checksum += last - first + 1;
            }
        }
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
