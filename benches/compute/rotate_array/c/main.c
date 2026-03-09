// Rotate Array — in-place cyclic rotation using reverse
// Measures: sequential access, reverse pattern, cache behavior
// Workload: N=50000 array, 5000 rotations with varying offsets

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void reverse(int64_t* arr, int64_t lo, int64_t hi) {
    while (lo < hi) {
        int64_t tmp = arr[lo];
        arr[lo] = arr[hi];
        arr[hi] = tmp;
        lo++;
        hi--;
    }
}

static void rotate(int64_t* arr, int64_t n, int64_t k) {
    k = k % n;
    if (k < 0) k += n;
    if (k == 0) return;
    reverse(arr, 0, n - 1);
    reverse(arr, 0, k - 1);
    reverse(arr, k, n - 1);
}

int main() {
    int64_t N = 50000;
    int64_t ITERS = 30000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    // Initialize
    for (int64_t i = 0; i < N; i++) arr[i] = i;

    int64_t checksum = 0;
    int64_t seed = 42;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t k = seed % N;
        rotate(arr, N, k);
        checksum += arr[0] + arr[N/2] + arr[N-1];
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
