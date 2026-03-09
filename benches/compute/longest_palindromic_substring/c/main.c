// Longest Palindromic Substring — expand around center
// Measures: sequential scan, symmetric expansion
// Workload: N=10000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 10000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10; // small alphabet
        }

        int64_t max_len = 1;

        for (int64_t center = 0; center < N; center++) {
            // Odd length
            int64_t lo = center, hi = center;
            while (lo > 0 && hi < N - 1 && arr[lo - 1] == arr[hi + 1]) {
                lo--;
                hi++;
            }
            int64_t len = hi - lo + 1;
            if (len > max_len) max_len = len;

            // Even length
            lo = center;
            hi = center + 1;
            if (hi < N && arr[lo] == arr[hi]) {
                while (lo > 0 && hi < N - 1 && arr[lo - 1] == arr[hi + 1]) {
                    lo--;
                    hi++;
                }
                len = hi - lo + 1;
                if (len > max_len) max_len = len;
            }
        }
        checksum += max_len;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
