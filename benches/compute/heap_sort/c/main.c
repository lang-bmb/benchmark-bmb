// Heap Sort — in-place comparison sort using binary heap
// Measures: heap operations (sift-down), array swaps
// Workload: N=200000, 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void sift_down(int64_t* arr, int64_t start, int64_t end) {
    int64_t root = start;
    while (root * 2 + 1 <= end) {
        int64_t child = root * 2 + 1;
        int64_t swap = root;
        if (arr[swap] < arr[child]) swap = child;
        if (child + 1 <= end && arr[swap] < arr[child + 1]) swap = child + 1;
        if (swap == root) return;
        int64_t tmp = arr[root];
        arr[root] = arr[swap];
        arr[swap] = tmp;
        root = swap;
    }
}

static void heap_sort(int64_t* arr, int64_t n) {
    // Build max heap
    for (int64_t start = (n - 2) / 2; start >= 0; start--) {
        sift_down(arr, start, n - 1);
    }
    // Extract elements
    for (int64_t end = n - 1; end > 0; end--) {
        int64_t tmp = arr[0];
        arr[0] = arr[end];
        arr[end] = tmp;
        sift_down(arr, 0, end - 1);
    }
}

int main() {
    int64_t N = 200000;
    int64_t ITERS = 100;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % N;
        }
        heap_sort(arr, N);
        checksum += arr[0] + arr[N/2] + arr[N-1];
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
