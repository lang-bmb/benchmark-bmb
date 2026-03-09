// Graph Coloring — greedy coloring of adjacency matrix
// Measures: adjacency matrix access, bit manipulation, greedy search
// Workload: N=500 vertices, density=30%, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 500;
    int64_t ITERS = 200;
    int64_t* adj = (int64_t*)malloc(N * N * sizeof(int64_t));
    int64_t* color = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* used = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate random graph (adjacency matrix)
        for (int64_t i = 0; i < N; i++) {
            for (int64_t j = i + 1; j < N; j++) {
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                int64_t edge = (seed % 100) < 30 ? 1 : 0;
                adj[i * N + j] = edge;
                adj[j * N + i] = edge;
            }
            adj[i * N + i] = 0;
        }

        // Greedy coloring
        for (int64_t i = 0; i < N; i++) color[i] = -1;

        for (int64_t v = 0; v < N; v++) {
            // Mark colors used by neighbors
            for (int64_t i = 0; i < N; i++) used[i] = 0;
            for (int64_t u = 0; u < N; u++) {
                if (adj[v * N + u] && color[u] >= 0) {
                    used[color[u]] = 1;
                }
            }
            // Find smallest available color
            int64_t c = 0;
            while (used[c]) c++;
            color[v] = c;
        }

        // Checksum: sum of all colors
        for (int64_t i = 0; i < N; i++) {
            checksum += color[i];
        }
    }
    printf("%lld\n", (long long)checksum);
    free(adj);
    free(color);
    free(used);
    return 0;
}
