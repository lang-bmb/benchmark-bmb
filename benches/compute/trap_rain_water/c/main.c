// Trapping Rain Water — two-pointer O(n) solution
// Measures: two-pointer technique, sequential access, min/max
// Workload: N=500000 array, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t trap(const int64_t* height, int64_t n) {
    int64_t left = 0, right = n - 1;
    int64_t left_max = 0, right_max = 0;
    int64_t water = 0;
    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= left_max) left_max = height[left];
            else water += left_max - height[left];
            left++;
        } else {
            if (height[right] >= right_max) right_max = height[right];
            else water += right_max - height[right];
            right--;
        }
    }
    return water;
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 1000;
        }
        checksum += trap(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
