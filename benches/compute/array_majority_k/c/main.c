// Array Majority K — find elements appearing more than N/K times
// Measures: candidate tracking, verification scan
// Workload: N=500000, K=5, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define K 5

int main() {
    int64_t N = 500000;
    int64_t ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t candidates[K - 1];
    int64_t counts[K - 1];
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 20;  // Small range for likely majority
        }

        // Phase 1: Find candidates (generalized Boyer-Moore)
        memset(counts, 0, sizeof(counts));
        for (int64_t i = 0; i < K - 1; i++) candidates[i] = -1;

        for (int64_t i = 0; i < N; i++) {
            // Check if arr[i] is already a candidate
            int64_t found = 0;
            for (int64_t j = 0; j < K - 1; j++) {
                if (counts[j] > 0 && candidates[j] == arr[i]) {
                    counts[j]++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                // Try to add as new candidate
                int64_t added = 0;
                for (int64_t j = 0; j < K - 1; j++) {
                    if (counts[j] == 0) {
                        candidates[j] = arr[i];
                        counts[j] = 1;
                        added = 1;
                        break;
                    }
                }
                if (!added) {
                    // Decrement all counts
                    for (int64_t j = 0; j < K - 1; j++) {
                        counts[j]--;
                    }
                }
            }
        }

        // Phase 2: Verify
        for (int64_t j = 0; j < K - 1; j++) {
            if (counts[j] > 0) {
                int64_t count = 0;
                for (int64_t i = 0; i < N; i++) {
                    if (arr[i] == candidates[j]) count++;
                }
                if (count > N / K) {
                    checksum += candidates[j];
                }
            }
        }
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
