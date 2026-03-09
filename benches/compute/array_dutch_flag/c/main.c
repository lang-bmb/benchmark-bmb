// Dutch National Flag — 3-way partition (0,1,2)
// Measures: swap operations, pointer tracking
// Workload: N=500000, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 500000;
    int64_t ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate array of 0,1,2
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 3;
        }

        // Dutch National Flag partition
        int64_t lo = 0, mid = 0, hi = N - 1;
        while (mid <= hi) {
            if (arr[mid] == 0) {
                int64_t t = arr[lo]; arr[lo] = arr[mid]; arr[mid] = t;
                lo++;
                mid++;
            } else if (arr[mid] == 1) {
                mid++;
            } else {
                int64_t t = arr[mid]; arr[mid] = arr[hi]; arr[hi] = t;
                hi--;
            }
        }

        checksum += arr[0] + arr[N/2] + arr[N-1];
        checksum += lo + mid;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
