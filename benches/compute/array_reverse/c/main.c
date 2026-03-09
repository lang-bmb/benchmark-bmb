// Array Reverse — in-place reversal
// Measures: two-pointer swap, random access, cache behavior
// Workload: N=500000 array, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void reverse(int64_t* arr, int64_t n) {
    int64_t i = 0, j = n - 1;
    while (i < j) {
        int64_t t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
        i++;
        j--;
    }
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 5000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        arr[i] = seed;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        reverse(arr, N);
        checksum += arr[0] + arr[N - 1];
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
