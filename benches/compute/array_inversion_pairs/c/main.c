// Array Inversion Pairs — count pairs (i,j) where i<j and arr[i]>arr[j]
// Measures: merge sort, recursive divide-and-conquer, register carry (count)
// Workload: N=50000 array, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t merge_count(int64_t* arr, int64_t* tmp, int64_t left, int64_t right) {
    if (right - left <= 1) return 0;
    int64_t mid = left + (right - left) / 2;
    int64_t count = 0;
    count += merge_count(arr, tmp, left, mid);
    count += merge_count(arr, tmp, mid, right);

    int64_t i = left, j = mid, k = left;
    while (i < mid && j < right) {
        if (arr[i] <= arr[j]) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
            count += mid - i;
        }
    }
    while (i < mid) tmp[k++] = arr[i++];
    while (j < right) tmp[k++] = arr[j++];
    for (int64_t x = left; x < right; x++) arr[x] = tmp[x];
    return count;
}

int main() {
    int64_t N = 50000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* tmp = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 100000;
        }
        checksum += merge_count(arr, tmp, 0, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    free(tmp);
    return 0;
}
