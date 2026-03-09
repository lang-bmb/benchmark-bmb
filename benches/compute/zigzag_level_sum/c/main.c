// Zigzag Level Sum — alternating direction level traversal simulation
// Measures: queue-based BFS, direction alternation
// Workload: tree with 1000000 nodes, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 200;
    int64_t* values = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* queue = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            values[i] = seed % 1000;
        }

        // Simulate BFS zigzag on complete binary tree
        int64_t front = 0, back = 0;
        queue[back++] = 0; // root
        int64_t level = 0;
        int64_t total = 0;

        while (front < back) {
            int64_t level_size = back - front;
            int64_t level_sum = 0;
            int64_t sign = (level % 2 == 0) ? 1 : -1;

            for (int64_t i = 0; i < level_size; i++) {
                int64_t node = queue[front++];
                level_sum += values[node] * sign;

                // Add children
                int64_t left = 2 * node + 1;
                int64_t right = 2 * node + 2;
                if (left < N) queue[back++] = left;
                if (right < N) queue[back++] = right;
            }
            total += level_sum;
            level++;
        }
        checksum += total;
    }
    printf("%lld\n", (long long)checksum);
    free(values);
    free(queue);
    return 0;
}
