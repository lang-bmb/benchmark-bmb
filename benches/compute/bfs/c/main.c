// BFS benchmark — breadth-first search on random graph
// Measures: queue operations, random memory access, graph traversal
// Workload: 50000 nodes, ~4 edges/node, 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t bfs(int64_t nodes, const int64_t* adj_off, const int64_t* adj_data,
                   int64_t start, int64_t* dist, int64_t* queue) {
    for (int64_t i = 0; i < nodes; i++) dist[i] = -1;
    dist[start] = 0;
    int64_t head = 0, tail = 0;
    queue[tail++] = start;

    int64_t max_dist = 0;
    while (head < tail) {
        int64_t u = queue[head++];
        int64_t d = dist[u];
        int64_t begin = adj_off[u];
        int64_t end = adj_off[u + 1];
        for (int64_t e = begin; e < end; e++) {
            int64_t v = adj_data[e];
            if (dist[v] == -1) {
                dist[v] = d + 1;
                queue[tail++] = v;
                if (d + 1 > max_dist) max_dist = d + 1;
            }
        }
    }
    return max_dist;
}

int main() {
    int64_t NODES = 50000;
    int64_t EDGES_PER = 4;
    int64_t ITERS = 100;

    int64_t total_edges = NODES * EDGES_PER;
    int64_t* adj_off = (int64_t*)malloc((NODES + 1) * sizeof(int64_t));
    int64_t* adj_data = (int64_t*)malloc(total_edges * sizeof(int64_t));
    int64_t* dist = (int64_t*)malloc(NODES * sizeof(int64_t));
    int64_t* queue = (int64_t*)malloc(NODES * sizeof(int64_t));

    // Build random graph with LCG
    int64_t seed = 42;
    for (int64_t i = 0; i < NODES; i++) {
        adj_off[i] = i * EDGES_PER;
        for (int64_t e = 0; e < EDGES_PER; e++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            adj_data[i * EDGES_PER + e] = seed % NODES;
        }
    }
    adj_off[NODES] = total_edges;

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t start = iter % NODES;
        checksum += bfs(NODES, adj_off, adj_data, start, dist, queue);
    }

    printf("%lld\n", (long long)checksum);
    free(adj_off);
    free(adj_data);
    free(dist);
    free(queue);
    return 0;
}
