// Bubble Sort — in-place with early termination
// Measures: sequential comparison+swap, branch prediction
// Workload: N=3000 array, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void bubble_sort(int64_t* arr, int64_t n) {
    for (int64_t i = 0; i < n - 1; i++) {
        for (int64_t j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int64_t tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int main() {
    int64_t N = 3000;
    int64_t ITERS = 200;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % N;
        }
        bubble_sort(arr, N);
        for (int64_t i = 0; i < 10; i++) checksum += arr[i];
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}