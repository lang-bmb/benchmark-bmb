// Counting Inversions via Merge Sort — count inversions while sorting
// Measures: merge sort, counting during merge
// Workload: N=200000, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t merge_count(int64_t* arr, int64_t* tmp, int64_t lo, int64_t hi) {
    if (lo >= hi) return 0;
    int64_t mid = lo + (hi - lo) / 2;
    int64_t count = 0;
    count += merge_count(arr, tmp, lo, mid);
    count += merge_count(arr, tmp, mid + 1, hi);

    // Merge and count
    int64_t i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi) {
        if (arr[i] <= arr[j]) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
            count += (mid - i + 1);
        }
    }
    while (i <= mid) tmp[k++] = arr[i++];
    while (j <= hi) tmp[k++] = arr[j++];
    for (int64_t x = lo; x <= hi; x++) arr[x] = tmp[x];
    return count;
}

int main() {
    int64_t N = 200000;
    int64_t ITERS = 200;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* tmp = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % N;
        }
        checksum += merge_count(arr, tmp, 0, N - 1);
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    free(tmp);
    return 0;
}
