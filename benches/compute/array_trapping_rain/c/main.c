// Trapping Rain Water — two-pointer approach
// Measures: two-pointer, register tracking (left_max, right_max)
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
            heights[i] = seed % 1000;
        }

        int64_t left = 0, right = N - 1;
        int64_t left_max = 0, right_max = 0;
        int64_t water = 0;

        while (left < right) {
            int64_t hl = heights[left];
            int64_t hr = heights[right];
            if (hl < hr) {
                if (hl >= left_max) {
                    left_max = hl;
                } else {
                    water += left_max - hl;
                }
                left++;
            } else {
                if (hr >= right_max) {
                    right_max = hr;
                } else {
                    water += right_max - hr;
                }
                right--;
            }
        }
        checksum += water;
    }
    printf("%lld\n", (long long)checksum);
    free(heights);
    return 0;
}
