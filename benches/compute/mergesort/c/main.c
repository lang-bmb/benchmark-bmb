// Merge sort benchmark — divide-and-conquer + array merging
// Measures: recursive splitting, sequential merge, memory copy patterns
// Workload: 500K elements, 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 500000
#define ITERS 100

static void merge(int64_t* arr, int64_t* tmp, int64_t lo, int64_t mid, int64_t hi) {
    for (int64_t i = lo; i <= hi; i++) tmp[i] = arr[i];
    int64_t i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi) {
        if (tmp[i] <= tmp[j]) { arr[k++] = tmp[i++]; }
        else { arr[k++] = tmp[j++]; }
    }
    while (i <= mid) arr[k++] = tmp[i++];
    while (j <= hi) arr[k++] = tmp[j++];
}

static void mergesort(int64_t* arr, int64_t* tmp, int64_t lo, int64_t hi) {
    if (lo >= hi) return;
    int64_t mid = lo + (hi - lo) / 2;
    mergesort(arr, tmp, lo, mid);
    mergesort(arr, tmp, mid + 1, hi);
    merge(arr, tmp, lo, mid, hi);
}

int main() {
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* tmp = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 31415 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed;
        }
        mergesort(arr, tmp, 0, N - 1);
        checksum += arr[0] + arr[N / 2] + arr[N - 1];
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    free(tmp);
    return 0;
}
