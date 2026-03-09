// Largest Rectangle in Histogram — stack-based O(n)
// Measures: stack operations, area tracking
// Workload: N=500000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 500000;
    int64_t ITERS = 500;
    int64_t* heights = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* stack = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            heights[i] = seed % 1000 + 1;
        }

        int64_t max_area = 0;
        int64_t top = -1;

        for (int64_t i = 0; i <= N; i++) {
            int64_t h = (i == N) ? 0 : heights[i];
            while (top >= 0 && heights[stack[top]] > h) {
                int64_t height = heights[stack[top]];
                top--;
                int64_t width = (top < 0) ? i : i - stack[top] - 1;
                int64_t area = height * width;
                if (area > max_area) max_area = area;
            }
            top++;
            stack[top] = i;
        }
        checksum += max_area;
    }
    printf("%lld\n", (long long)checksum);
    free(heights);
    free(stack);
    return 0;
}
