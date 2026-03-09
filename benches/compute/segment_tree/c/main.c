// Segment Tree — iterative bottom-up, range sum query + point update
// Measures: random access patterns, tree traversal, arithmetic
// Workload: N=50000 elements, 200000 mixed update/query ops, 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void seg_build(int64_t* tree, int64_t n) {
    for (int64_t i = n - 1; i >= 1; i--) {
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }
}

static void seg_update(int64_t* tree, int64_t n, int64_t pos, int64_t val) {
    int64_t p = pos + n;
    tree[p] = val;
    p /= 2;
    while (p >= 1) {
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
        p /= 2;
    }
}

static int64_t seg_query(int64_t* tree, int64_t n, int64_t l_arg, int64_t r_arg) {
    int64_t sum = 0;
    int64_t l = l_arg + n;
    int64_t r = r_arg + n + 1;
    while (l < r) {
        if (l & 1) {
            sum += tree[l];
            l++;
        }
        if (r & 1) {
            r--;
            sum += tree[r];
        }
        l /= 2;
        r /= 2;
    }
    return sum;
}

int main() {
    int64_t N = 50000;
    int64_t OPS = 200000;
    int64_t ITERS = 100;
    int64_t* tree = (int64_t*)malloc(N * 2 * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Initialize leaves with deterministic values
        int64_t seed = 42 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            tree[i + N] = seed % 1000;
        }
        // Build internal nodes
        seg_build(tree, N);

        // Mixed operations
        for (int64_t op = 0; op < OPS; op++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t kind = seed % 3;
            if (kind == 0) {
                // Point update
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                int64_t pos = seed % N;
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                int64_t val = seed % 1000;
                seg_update(tree, N, pos, val);
            } else {
                // Range sum query
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                int64_t a = seed % N;
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                int64_t b = seed % N;
                int64_t l = a <= b ? a : b;
                int64_t r = a <= b ? b : a;
                int64_t result = seg_query(tree, N, l, r);
                checksum += result;
            }
        }
    }

    printf("%lld\n", (long long)(checksum % 1000000007));
    free(tree);
    return 0;
}
