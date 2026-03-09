// Minimum Spanning Tree benchmark — Kruskal's algorithm with Union-Find
// Measures: sorting, union-find with path compression + union by rank
// Workload: 500 vertices, ~5000 edges, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Union-Find: find with path compression (iterative)
static int64_t uf_find(int64_t* parent, int64_t x) {
    int64_t r = x;
    // Find root
    while (parent[r] != r) {
        r = parent[r];
    }
    // Path compression
    int64_t c = x;
    while (c != r) {
        int64_t next = parent[c];
        parent[c] = r;
        c = next;
    }
    return r;
}

// Union-Find: union by rank, returns 1 if merged, 0 if same set
static int64_t uf_union(int64_t* parent, int64_t* rank, int64_t a, int64_t b) {
    int64_t ra = uf_find(parent, a);
    int64_t rb = uf_find(parent, b);
    if (ra == rb) return 0;
    int64_t rka = rank[ra];
    int64_t rkb = rank[rb];
    if (rka < rkb) {
        parent[ra] = rb;
    } else {
        parent[rb] = ra;
        if (rka == rkb) {
            rank[ra] = rka + 1;
        }
    }
    return 1;
}

// Selection sort edges by weight (O(n^2) for fairness)
static void sort_edges(int64_t* edge_u, int64_t* edge_v, int64_t* edge_w, int64_t num_edges) {
    for (int64_t i = 0; i < num_edges - 1; i++) {
        int64_t min_idx = i;
        for (int64_t j = i + 1; j < num_edges; j++) {
            if (edge_w[j] < edge_w[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            // Swap u
            int64_t tu = edge_u[i];
            edge_u[i] = edge_u[min_idx];
            edge_u[min_idx] = tu;
            // Swap v
            int64_t tv = edge_v[i];
            edge_v[i] = edge_v[min_idx];
            edge_v[min_idx] = tv;
            // Swap w
            int64_t tw = edge_w[i];
            edge_w[i] = edge_w[min_idx];
            edge_w[min_idx] = tw;
        }
    }
}

// Kruskal's MST: returns sum of MST edge weights
static int64_t kruskal(int64_t* edge_u, int64_t* edge_v, int64_t* edge_w,
                        int64_t num_edges, int64_t num_verts,
                        int64_t* parent, int64_t* rank) {
    // Initialize union-find
    for (int64_t i = 0; i < num_verts; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    // Process edges in sorted order
    int64_t mst_weight = 0;
    int64_t mst_edges = 0;
    for (int64_t e = 0; e < num_edges; e++) {
        if (mst_edges >= num_verts - 1) break;
        int64_t u = edge_u[e];
        int64_t v = edge_v[e];
        int64_t w = edge_w[e];
        int64_t merged = uf_union(parent, rank, u, v);
        if (merged == 1) {
            mst_weight += w;
            mst_edges++;
        }
    }
    return mst_weight;
}

int main() {
    int64_t num_verts = 500;
    int64_t num_edges = 5000;
    int64_t iters = 1000;

    // Edge arrays (3 parallel arrays: u, v, weight)
    int64_t* edge_u = (int64_t*)malloc(num_edges * sizeof(int64_t));
    int64_t* edge_v = (int64_t*)malloc(num_edges * sizeof(int64_t));
    int64_t* edge_w = (int64_t*)malloc(num_edges * sizeof(int64_t));
    // Union-find arrays
    int64_t* parent = (int64_t*)malloc(num_verts * sizeof(int64_t));
    int64_t* rank = (int64_t*)malloc(num_verts * sizeof(int64_t));

    // Generate random edges using LCG
    int64_t seed = 42;
    for (int64_t i = 0; i < num_edges; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t u = seed % num_verts;
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t v = seed % num_verts;
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t w = (seed % 1000) + 1;
        edge_u[i] = u;
        edge_v[i] = v;
        edge_w[i] = w;
    }

    // Sort edges by weight once
    sort_edges(edge_u, edge_v, edge_w, num_edges);

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        checksum += kruskal(edge_u, edge_v, edge_w, num_edges,
                           num_verts, parent, rank);
    }
    printf("%lld\n", (long long)checksum);
    free(edge_u);
    free(edge_v);
    free(edge_w);
    free(parent);
    free(rank);
    return 0;
}
