// Depth-First Search — iterative with explicit stack
// Measures: graph traversal, stack operations, adjacency list access
// Workload: N=2000 nodes, ~10000 edges, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t dfs(int64_t* adj, int64_t* deg, int64_t n, int64_t start,
                   int64_t* visited, int64_t* stack) {
    for (int64_t i = 0; i < n; i++) visited[i] = 0;
    int64_t sp = 0;
    stack[sp++] = start;
    visited[start] = 1;
    int64_t count = 0;
    while (sp > 0) {
        int64_t node = stack[--sp];
        count++;
        int64_t d = deg[node];
        int64_t base = node * 10;
        for (int64_t j = 0; j < d; j++) {
            int64_t neighbor = adj[base + j];
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                stack[sp++] = neighbor;
            }
        }
    }
    return count;
}

int main() {
    int64_t N = 2000;
    int64_t MAX_DEG = 10;
    int64_t ITERS = 3000;
    int64_t* adj = (int64_t*)malloc(N * MAX_DEG * sizeof(int64_t));
    int64_t* deg = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* visited = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* stack = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 31337 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t d = (seed % 5) + 1;
            deg[i] = d;
            int64_t base = i * MAX_DEG;
            for (int64_t j = 0; j < d; j++) {
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                adj[base + j] = seed % N;
            }
        }
        checksum += dfs(adj, deg, N, 0, visited, stack);
    }

    printf("%lld\n", (long long)checksum);
    free(adj); free(deg); free(visited); free(stack);
    return 0;
}