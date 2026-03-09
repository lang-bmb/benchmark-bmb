// Fenwick Tree (Binary Indexed Tree) — point update + prefix sum query
// Measures: random access patterns, bitwise operations, branch-heavy control flow
// Workload: N=100000 elements, 500000 mixed update/query ops, 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static void fenwick_update(int64_t* tree, int64_t i_arg, int64_t delta, int64_t n) {
    int64_t i = i_arg + 1;
    while (i <= n) {
        tree[i - 1] += delta;
        i += i & (-i);
    }
}

static int64_t fenwick_query(int64_t* tree, int64_t i_arg) {
    int64_t sum = 0;
    int64_t i = i_arg + 1;
    while (i > 0) {
        sum += tree[i - 1];
        i -= i & (-i);
    }
    return sum;
}

int main() {
    int64_t N = 100000;
    int64_t OPS = 500000;
    int64_t ITERS = 100;
    int64_t* tree = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        memset(tree, 0, N * sizeof(int64_t));
        int64_t seed = 42 + iter;
        for (int64_t op = 0; op < OPS; op++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t kind = seed % 2;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t idx = seed % N;
            if (kind == 0) {
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                int64_t delta = seed % 1000;
                fenwick_update(tree, idx, delta, N);
            } else {
                int64_t result = fenwick_query(tree, idx);
                checksum += result;
            }
        }
    }

    printf("%lld\n", (long long)(checksum % 1000000007));
    free(tree);
    return 0;
}
