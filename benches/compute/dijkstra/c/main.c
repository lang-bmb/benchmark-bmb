// Dijkstra shortest path benchmark — min-heap + graph traversal
// Measures: priority queue operations, random memory access, graph algorithms
// Workload: 20000 nodes, ~6 edges/node, weighted, 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define INF 0x7FFFFFFFFFFFFFFF

static void dijk_swap(int64_t* dist, int64_t* node, int64_t a, int64_t b) {
    int64_t td = dist[a]; dist[a] = dist[b]; dist[b] = td;
    int64_t tn = node[a]; node[a] = node[b]; node[b] = tn;
}

static void dijk_up(int64_t* dist, int64_t* node, int64_t i) {
    while (i > 0) {
        int64_t p = (i - 1) / 2;
        if (dist[i] < dist[p]) { dijk_swap(dist, node, i, p); i = p; }
        else break;
    }
}

static void dijk_down(int64_t* dist, int64_t* node, int64_t size, int64_t i) {
    while (1) {
        int64_t s = i, l = 2*i+1, r = 2*i+2;
        if (l < size && dist[l] < dist[s]) s = l;
        if (r < size && dist[r] < dist[s]) s = r;
        if (s == i) break;
        dijk_swap(dist, node, i, s);
        i = s;
    }
}

static int64_t dijkstra(int64_t nodes, const int64_t* adj_off, const int64_t* adj_dst,
                        const int64_t* adj_wt, int64_t src, int64_t* best,
                        int64_t* heap_d, int64_t* heap_n) {
    for (int64_t i = 0; i < nodes; i++) best[i] = INF;
    best[src] = 0;

    int64_t hsize = 0;
    heap_d[hsize] = 0;
    heap_n[hsize] = src;
    hsize++;

    while (hsize > 0) {
        int64_t d = heap_d[0];
        int64_t u = heap_n[0];
        hsize--;
        heap_d[0] = heap_d[hsize];
        heap_n[0] = heap_n[hsize];
        if (hsize > 0) dijk_down(heap_d, heap_n, hsize, 0);

        if (d > best[u]) continue;

        int64_t begin = adj_off[u];
        int64_t end = adj_off[u + 1];
        for (int64_t e = begin; e < end; e++) {
            int64_t v = adj_dst[e];
            int64_t nd = d + adj_wt[e];
            if (nd < best[v]) {
                best[v] = nd;
                heap_d[hsize] = nd;
                heap_n[hsize] = v;
                dijk_up(heap_d, heap_n, hsize);
                hsize++;
            }
        }
    }

    // Return max distance (diameter estimate)
    int64_t mx = 0;
    for (int64_t i = 0; i < nodes; i++) {
        if (best[i] != INF && best[i] > mx) mx = best[i];
    }
    return mx;
}

int main() {
    int64_t NODES = 20000;
    int64_t EDGES_PER = 6;
    int64_t ITERS = 100;

    int64_t total_edges = NODES * EDGES_PER;
    int64_t* adj_off = (int64_t*)malloc((NODES + 1) * sizeof(int64_t));
    int64_t* adj_dst = (int64_t*)malloc(total_edges * sizeof(int64_t));
    int64_t* adj_wt = (int64_t*)malloc(total_edges * sizeof(int64_t));
    int64_t* best = (int64_t*)malloc(NODES * sizeof(int64_t));
    int64_t* heap_d = (int64_t*)malloc(NODES * sizeof(int64_t));
    int64_t* heap_n = (int64_t*)malloc(NODES * sizeof(int64_t));

    // Build weighted random graph
    int64_t seed = 12345;
    for (int64_t i = 0; i < NODES; i++) {
        adj_off[i] = i * EDGES_PER;
        for (int64_t e = 0; e < EDGES_PER; e++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            adj_dst[i * EDGES_PER + e] = seed % NODES;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            adj_wt[i * EDGES_PER + e] = (seed % 100) + 1;
        }
    }
    adj_off[NODES] = total_edges;

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        checksum += dijkstra(NODES, adj_off, adj_dst, adj_wt, iter % NODES, best, heap_d, heap_n);
    }

    printf("%lld\n", (long long)checksum);
    free(adj_off); free(adj_dst); free(adj_wt);
    free(best); free(heap_d); free(heap_n);
    return 0;
}
