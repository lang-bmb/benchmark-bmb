// Connected Components — Union-Find with path compression and union by rank
// Measures: union-find operations, path compression, component counting
// Workload: N=5000 vertices, ~20000 edges, 3000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t find(int64_t* parent, int64_t x) {
    int64_t r = x;
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

static int64_t do_union(int64_t* parent, int64_t* rank, int64_t a, int64_t b) {
    int64_t ra = find(parent, a);
    int64_t rb = find(parent, b);
    if (ra == rb) return 0;
    if (rank[ra] < rank[rb]) {
        parent[ra] = rb;
    } else {
        parent[rb] = ra;
        if (rank[ra] == rank[rb]) {
            rank[ra]++;
        }
    }
    return 1;
}

int main() {
    int64_t N = 5000;
    int64_t NUM_EDGES = 20000;
    int64_t ITERS = 3000;
    int64_t* parent = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* rank = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 99999 + iter;
        // Initialize union-find
        for (int64_t i = 0; i < N; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
        // Generate edges and union
        for (int64_t e = 0; e < NUM_EDGES; e++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t u = seed % N;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t v = seed % N;
            do_union(parent, rank, u, v);
        }
        // Count components: vertices where find(i) == i
        int64_t components = 0;
        for (int64_t i = 0; i < N; i++) {
            int64_t ri = find(parent, i);
            if (ri == i) {
                components++;
            }
        }
        checksum += components;
    }

    printf("%lld\n", (long long)checksum);
    free(parent);
    free(rank);
    return 0;
}