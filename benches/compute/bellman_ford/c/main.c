// Bellman-Ford shortest path benchmark
// Measures: edge relaxation, sequential memory access, graph algorithms
// Workload: 8000 vertices, 100000 edges, 300 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define INF 999999999

static int64_t bellman_ford(int64_t n, int64_t num_edges, const int64_t* src_arr,
                            const int64_t* dst_arr, const int64_t* wt_arr, int64_t* dist) {
    // Initialize distances
    for (int64_t i = 0; i < n; i++) dist[i] = INF;
    dist[0] = 0;

    // Relax edges V-1 times
    for (int64_t iter = 0; iter < n - 1; iter++) {
        int64_t changed = 0;
        for (int64_t e = 0; e < num_edges; e++) {
            int64_t u = src_arr[e];
            int64_t du = dist[u];
            if (du < INF) {
                int64_t v = dst_arr[e];
                int64_t w = wt_arr[e];
                int64_t nd = du + w;
                if (nd < dist[v]) {
                    dist[v] = nd;
                    changed = 1;
                }
            }
        }
        // Early exit if no changes
        if (!changed) break;
    }

    // Sum all finite distances for checksum
    int64_t sum = 0;
    for (int64_t i = 0; i < n; i++) {
        if (dist[i] < INF) sum += dist[i];
    }
    return sum;
}

int main() {
    int64_t N = 8000;
    int64_t NUM_EDGES = 100000;
    int64_t ITERS = 300;

    int64_t* src_arr = (int64_t*)malloc(NUM_EDGES * sizeof(int64_t));
    int64_t* dst_arr = (int64_t*)malloc(NUM_EDGES * sizeof(int64_t));
    int64_t* wt_arr = (int64_t*)malloc(NUM_EDGES * sizeof(int64_t));
    int64_t* dist = (int64_t*)malloc(N * sizeof(int64_t));

    // Generate random edge list with deterministic PRNG
    int64_t seed = 42;
    for (int64_t e = 0; e < NUM_EDGES; e++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t u = seed % N;
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t v = seed % N;
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t w = (seed % 100) + 1;
        src_arr[e] = u;
        dst_arr[e] = v;
        wt_arr[e] = w;
    }

    int64_t checksum = 0;
    for (int64_t rep = 0; rep < ITERS; rep++) {
        // Regenerate edges each iteration with different seed for varied workloads
        seed = 42 + rep * 7;
        for (int64_t e = 0; e < NUM_EDGES; e++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t u = seed % N;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t v = seed % N;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t w = (seed % 100) + 1;
            src_arr[e] = u;
            dst_arr[e] = v;
            wt_arr[e] = w;
        }
        checksum += bellman_ford(N, NUM_EDGES, src_arr, dst_arr, wt_arr, dist);
    }

    printf("%lld\n", (long long)checksum);
    free(src_arr); free(dst_arr); free(wt_arr); free(dist);
    return 0;
}
