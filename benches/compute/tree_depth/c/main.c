// Tree Depth — iterative BFS max depth
// Measures: queue operations, tree traversal, indirect indexing
// Workload: N=10000 nodes, 20000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t max_depth_bfs(int64_t n, const int64_t* left, const int64_t* right,
                             int64_t* queue, int64_t* depth) {
    // BFS from root (node 0)
    int64_t head = 0, tail = 0;
    queue[tail++] = 0;
    depth[0] = 0;

    int64_t max_d = 0;
    while (head < tail) {
        int64_t u = queue[head++];
        int64_t d = depth[u];
        int64_t l = left[u];
        int64_t r = right[u];
        if (l != -1) {
            depth[l] = d + 1;
            queue[tail++] = l;
            if (d + 1 > max_d) max_d = d + 1;
        }
        if (r != -1) {
            depth[r] = d + 1;
            queue[tail++] = r;
            if (d + 1 > max_d) max_d = d + 1;
        }
    }
    return max_d;
}

int main() {
    int64_t N = 10000;
    int64_t ITERS = 20000;

    int64_t* left  = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* right = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* val   = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* queue = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* depth = (int64_t*)malloc(N * sizeof(int64_t));

    // Build complete-ish binary tree
    for (int64_t i = 0; i < N; i++) {
        int64_t l = 2 * i + 1;
        int64_t r = 2 * i + 2;
        left[i]  = (l < N) ? l : -1;
        right[i] = (r < N) ? r : -1;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Permute values each iteration
        for (int64_t i = 0; i < N; i++) {
            val[i] = (i + iter) % N;
        }
        checksum += max_depth_bfs(N, left, right, queue, depth);
    }

    printf("%lld\n", (long long)checksum);
    free(left);
    free(right);
    free(val);
    free(queue);
    free(depth);
    return 0;
}
