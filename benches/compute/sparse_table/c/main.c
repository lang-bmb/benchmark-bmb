// Sparse Table — O(1) range minimum query after O(n log n) preprocessing
// Measures: 2D array access, logarithmic preprocessing, random queries
// Workload: N=100000, 500000 queries, 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAXLOG 17

static void build_sparse_table(const int64_t* arr, int64_t n,
                                int64_t* table, int64_t maxlog) {
    for (int64_t i = 0; i < n; i++) table[i] = arr[i];
    for (int64_t j = 1; j < maxlog; j++) {
        int64_t prev_row = (j - 1) * n;
        int64_t curr_row = j * n;
        int64_t half = (int64_t)1 << (j - 1);
        for (int64_t i = 0; i + (1 << j) <= n; i++) {
            int64_t a = table[prev_row + i];
            int64_t b = table[prev_row + i + half];
            table[curr_row + i] = (a < b) ? a : b;
        }
    }
}

static int64_t query(const int64_t* table, int64_t n,
                     const int64_t* log_table, int64_t l, int64_t r) {
    int64_t len = r - l + 1;
    int64_t k = log_table[len];
    int64_t a = table[k * n + l];
    int64_t b = table[k * n + r - (1 << k) + 1];
    return (a < b) ? a : b;
}

int main() {
    int64_t N = 100000;
    int64_t QUERIES = 500000;
    int64_t ITERS = 300;

    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* table = (int64_t*)malloc(MAXLOG * N * sizeof(int64_t));
    int64_t* log_table = (int64_t*)malloc((N + 1) * sizeof(int64_t));

    // Precompute log table
    log_table[1] = 0;
    for (int64_t i = 2; i <= N; i++) {
        log_table[i] = log_table[i / 2] + 1;
    }

    int64_t seed = 42;
    int64_t checksum = 0;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Fill array
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 1000000;
        }
        build_sparse_table(arr, N, table, MAXLOG);

        // Random queries
        for (int64_t q = 0; q < QUERIES; q++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t l = seed % N;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t r = seed % N;
            if (l > r) { int64_t tmp = l; l = r; r = tmp; }
            checksum += query(table, N, log_table, l, r);
        }
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    free(table);
    free(log_table);
    return 0;
}
