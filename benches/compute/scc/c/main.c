// Strongly Connected Components — Kosaraju's algorithm
// Measures: 2-pass DFS, graph reversal, component tracking
// Workload: N=3000 nodes, ~9000 edges, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_DEG 10

static void dfs1(int64_t* adj, int64_t* deg, int64_t n, int64_t node,
                 int64_t* visited, int64_t* order, int64_t* order_idx, int64_t* stack) {
    int64_t sp = 0;
    stack[sp++] = node;
    visited[node] = 1;
    int64_t idx = *order_idx;
    while (sp > 0) {
        int64_t cur = stack[--sp];
        int64_t d = deg[cur];
        int64_t base = cur * MAX_DEG;
        int pushed = 0;
        for (int64_t j = 0; j < d; j++) {
            int64_t nb = adj[base + j];
            if (!visited[nb]) {
                visited[nb] = 1;
                stack[sp++] = nb;
                pushed++;
            }
        }
        if (!pushed) {
            order[idx++] = cur;
        }
    }
    *order_idx = idx;
}

static int64_t dfs2(int64_t* radj, int64_t* rdeg, int64_t node,
                     int64_t* visited, int64_t* stack) {
    int64_t sp = 0;
    stack[sp++] = node;
    visited[node] = 1;
    int64_t count = 0;
    while (sp > 0) {
        int64_t cur = stack[--sp];
        count++;
        int64_t d = rdeg[cur];
        int64_t base = cur * MAX_DEG;
        for (int64_t j = 0; j < d; j++) {
            int64_t nb = radj[base + j];
            if (!visited[nb]) {
                visited[nb] = 1;
                stack[sp++] = nb;
            }
        }
    }
    return count;
}

static int64_t kosaraju(int64_t* adj, int64_t* deg, int64_t* radj, int64_t* rdeg,
                         int64_t n, int64_t* visited, int64_t* order, int64_t* stack) {
    for (int64_t i = 0; i < n; i++) visited[i] = 0;
    int64_t order_idx = 0;
    for (int64_t i = 0; i < n; i++) {
        if (!visited[i]) dfs1(adj, deg, n, i, visited, order, &order_idx, stack);
    }
    for (int64_t i = 0; i < n; i++) visited[i] = 0;
    int64_t num_scc = 0;
    for (int64_t i = n - 1; i >= 0; i--) {
        int64_t node = order[i];
        if (!visited[node]) {
            dfs2(radj, rdeg, node, visited, stack);
            num_scc++;
        }
    }
    return num_scc;
}

int main() {
    int64_t N = 3000;
    int64_t ITERS = 200;
    int64_t* adj = (int64_t*)malloc(N * MAX_DEG * sizeof(int64_t));
    int64_t* deg = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* radj = (int64_t*)malloc(N * MAX_DEG * sizeof(int64_t));
    int64_t* rdeg = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* visited = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* order = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* stack = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 99999 + iter;
        for (int64_t i = 0; i < N; i++) rdeg[i] = 0;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t d = (seed % 3) + 1;
            deg[i] = d;
            int64_t base = i * MAX_DEG;
            for (int64_t j = 0; j < d; j++) {
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                int64_t target = seed % N;
                adj[base + j] = target;
                int64_t rd = rdeg[target];
                if (rd < MAX_DEG) {
                    radj[target * MAX_DEG + rd] = i;
                    rdeg[target] = rd + 1;
                }
            }
        }
        checksum += kosaraju(adj, deg, radj, rdeg, N, visited, order, stack);
    }

    printf("%lld\n", (long long)checksum);
    free(adj); free(deg); free(radj); free(rdeg);
    free(visited); free(order); free(stack);
    return 0;
}