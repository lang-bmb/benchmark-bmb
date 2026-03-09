// Topological Sort — Kahn's algorithm (BFS-based)
// Measures: queue operations, indegree tracking, graph traversal
// Workload: N=5000 DAG nodes, ~15000 edges, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t topo_sort(int64_t* adj, int64_t* deg, int64_t n,
                         int64_t* indeg, int64_t* queue, int64_t* result) {
    int64_t max_deg = 10;
    for (int64_t i = 0; i < n; i++) indeg[i] = 0;
    for (int64_t i = 0; i < n; i++) {
        int64_t d = deg[i];
        int64_t base = i * max_deg;
        for (int64_t j = 0; j < d; j++) {
            int64_t v = adj[base + j];
            indeg[v]++;
        }
    }
    int64_t head = 0, tail = 0;
    for (int64_t i = 0; i < n; i++) {
        if (indeg[i] == 0) queue[tail++] = i;
    }
    int64_t count = 0;
    while (head < tail) {
        int64_t node = queue[head++];
        result[count++] = node;
        int64_t d = deg[node];
        int64_t base = node * max_deg;
        for (int64_t j = 0; j < d; j++) {
            int64_t v = adj[base + j];
            if (--indeg[v] == 0) {
                queue[tail++] = v;
            }
        }
    }
    return count;
}

int main() {
    int64_t N = 5000;
    int64_t MAX_DEG = 10;
    int64_t ITERS = 200;
    int64_t* adj = (int64_t*)malloc(N * MAX_DEG * sizeof(int64_t));
    int64_t* deg = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* indeg = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* queue = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* result = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 54321 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t d = (seed % 3) + 1;
            deg[i] = d;
            int64_t base = i * MAX_DEG;
            for (int64_t j = 0; j < d; j++) {
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                int64_t target = i + 1 + (seed % (N - i - 1 + 1));
                int64_t t = target >= N ? (i + 1) % N : target;
                adj[base + j] = t;
            }
        }
        deg[N - 1] = 0;
        checksum += topo_sort(adj, deg, N, indeg, queue, result);
    }

    printf("%lld\n", (long long)checksum);
    free(adj); free(deg); free(indeg); free(queue); free(result);
    return 0;
}