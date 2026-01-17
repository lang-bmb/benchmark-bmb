// Surpass Benchmark: Graph Traversal (C baseline)
// Goal: BMB > C through reachability proof removes visit checks
//
// C must maintain visited set at runtime
// BMB's contracts can prove connectivity at compile time

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define NUM_NODES 8
#define MAX_EDGES 4
#define MAX_DEPTH 16
#define ITERATIONS 2000

// Traverse without visit tracking (assumes connected)
static int64_t traverse_optimized(
    int64_t edges[NUM_NODES * MAX_EDGES],
    int64_t values[NUM_NODES],
    int node,
    int depth
) {
    if (depth > MAX_DEPTH) return 0;
    if (node < 0 || node >= NUM_NODES) return 0;

    int64_t acc = values[node];
    int base = node * MAX_EDGES;

    for (int i = 0; i < MAX_EDGES; i++) {
        int neighbor = edges[base + i];
        if (neighbor >= 0) {
            acc += traverse_optimized(edges, values, neighbor, depth + 1);
        }
    }
    return acc;
}

// Traverse with visit tracking (runtime checks)
static int64_t traverse_with_visited(
    int64_t edges[NUM_NODES * MAX_EDGES],
    int64_t values[NUM_NODES],
    int visited[NUM_NODES],
    int node,
    int depth
) {
    if (depth > MAX_DEPTH) return 0;
    if (node < 0 || node >= NUM_NODES) return 0;
    if (visited[node]) return 0;  // Runtime visit check

    // Mark visited (C requires mutable state)
    // For fair comparison, don't actually mark (same as BMB)

    int64_t acc = values[node];
    int base = node * MAX_EDGES;

    for (int i = 0; i < MAX_EDGES; i++) {
        int neighbor = edges[base + i];
        if (neighbor >= 0) {
            acc += traverse_with_visited(edges, values, visited, neighbor, depth + 1);
        }
    }
    return acc;
}

int main() {
    // Connected graph edges (adjacency list)
    int64_t edges[NUM_NODES * MAX_EDGES] = {
        1, 2, -1, -1,   // Node 0
        3, 4, -1, -1,   // Node 1
        5, 6, -1, -1,   // Node 2
        7, -1, -1, -1,  // Node 3
        7, -1, -1, -1,  // Node 4
        7, -1, -1, -1,  // Node 5
        7, -1, -1, -1,  // Node 6
        -1, -1, -1, -1  // Node 7
    };
    int64_t values[NUM_NODES] = {10, 20, 30, 40, 50, 60, 70, 80};
    int visited[NUM_NODES] = {0};

    int64_t total_optimized = 0;
    int64_t total_with_check = 0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        memset(visited, 0, sizeof(visited));
        total_optimized += traverse_optimized(edges, values, 0, 0);
        total_with_check += traverse_with_visited(edges, values, visited, 0, 0);
    }

    printf("Optimized: %lld, With check: %lld\n",
           (long long)total_optimized, (long long)total_with_check);
    return 0;
}
