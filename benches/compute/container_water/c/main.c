// Container With Most Water — two pointers
// Measures: two-pointer convergence, register tracking
// Workload: N=2000000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 500;
    int64_t* heights = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            heights[i] = seed % 10000;
        }

        int64_t left = 0, right = N - 1;
        int64_t max_area = 0;

        while (left < right) {
            int64_t hl = heights[left];
            int64_t hr = heights[right];
            int64_t h = (hl < hr) ? hl : hr;
            int64_t area = h * (right - left);
            if (area > max_area) max_area = area;
            if (hl < hr) {
                left++;
            } else {
                right--;
            }
        }
        checksum += max_area;
    }
    printf("%lld\n", (long long)checksum);
    free(heights);
    return 0;
}
