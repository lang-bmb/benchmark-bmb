// Floyd-Warshall all-pairs shortest path benchmark
// Measures: triple nested loop, 2D array access, min operations
// Workload: 500 nodes, ~30% edge density, 20 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define INF 999999999

static int64_t floyd_warshall(int64_t* dist, int64_t n) {
    for (int64_t k = 0; k < n; k++) {
        for (int64_t i = 0; i < n; i++) {
            int64_t dik = dist[i * n + k];
            if (dik >= INF) continue;
            for (int64_t j = 0; j < n; j++) {
                int64_t dkj = dist[k * n + j];
                int64_t via_k = dik + dkj;
                if (via_k < dist[i * n + j]) {
                    dist[i * n + j] = via_k;
                }
            }
        }
    }
    // Return sum of all finite distances
    int64_t sum = 0;
    for (int64_t i = 0; i < n * n; i++) {
        if (dist[i] < INF) sum += dist[i];
    }
    return sum;
}

int main() {
    int64_t n = 500;
    int64_t iters = 20;
    int64_t* dist = (int64_t*)malloc(n * n * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        // Initialize: INF everywhere, 0 on diagonal
        for (int64_t i = 0; i < n; i++) {
            for (int64_t j = 0; j < n; j++) {
                dist[i * n + j] = (i == j) ? 0 : INF;
            }
        }
        // Add random edges (~30% density)
        int64_t seed = 77777 + iter;
        for (int64_t i = 0; i < n; i++) {
            for (int64_t j = 0; j < n; j++) {
                if (i == j) continue;
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                if (seed % 100 < 30) {
                    seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                    dist[i * n + j] = (seed % 100) + 1;
                }
            }
        }
        checksum += floyd_warshall(dist, n);
    }
    printf("%lld\n", (long long)checksum);
    free(dist);
    return 0;
}
