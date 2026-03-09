// Longest Consecutive Sequence — hash-set based O(n) approach
// Measures: hash table probing, sequential scan
// Workload: N=500000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main() {
    int64_t N = 500000;
    int64_t ITERS = 500;
    int64_t TABLE_SIZE = 1048576; // 2^20
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* table = (int64_t*)malloc(TABLE_SIZE * sizeof(int64_t));
    int64_t* used = (int64_t*)malloc(TABLE_SIZE * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 100000;
        }

        // Build hash set
        memset(used, 0, TABLE_SIZE * sizeof(int64_t));
        for (int64_t i = 0; i < N; i++) {
            int64_t h = (arr[i] * 2654435761LL) & (TABLE_SIZE - 1);
            while (used[h]) {
                if (table[h] == arr[i]) goto next_insert;
                h = (h + 1) & (TABLE_SIZE - 1);
            }
            used[h] = 1;
            table[h] = arr[i];
            next_insert:;
        }

        // Find longest consecutive
        int64_t max_len = 0;
        for (int64_t i = 0; i < N; i++) {
            int64_t val = arr[i];
            // Check if val-1 exists (if so, skip — not start of sequence)
            int64_t prev = val - 1;
            int64_t h = (prev * 2654435761LL) & (TABLE_SIZE - 1);
            int64_t found_prev = 0;
            while (used[h]) {
                if (table[h] == prev) { found_prev = 1; break; }
                h = (h + 1) & (TABLE_SIZE - 1);
            }
            if (found_prev) continue;

            // Count consecutive from val
            int64_t len = 1;
            int64_t next = val + 1;
            while (1) {
                h = (next * 2654435761LL) & (TABLE_SIZE - 1);
                int64_t found = 0;
                while (used[h]) {
                    if (table[h] == next) { found = 1; break; }
                    h = (h + 1) & (TABLE_SIZE - 1);
                }
                if (!found) break;
                len++;
                next++;
            }
            if (len > max_len) max_len = len;
        }
        checksum += max_len;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    free(table);
    free(used);
    return 0;
}
