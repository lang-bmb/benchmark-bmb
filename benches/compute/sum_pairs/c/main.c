// Sum Pairs benchmark — sort + two-pointer pair counting
// Measures: insertion sort, two-pointer scan, branch prediction
// Workload: N=10000 array, target=10000, 500 iterations, LCG PRNG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void insertion_sort(int64_t* arr, int64_t n) {
    for (int64_t i = 1; i < n; i++) {
        int64_t key = arr[i];
        int64_t j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

static int64_t count_pairs(int64_t* arr, int64_t n, int64_t target) {
    int64_t left = 0;
    int64_t right = n - 1;
    int64_t count = 0;
    while (left < right) {
        int64_t sum = arr[left] + arr[right];
        if (sum == target) {
            count++;
            left++;
            right--;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    return count;
}

int main() {
    int64_t N = 10000;
    int64_t TARGET = 10000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % N;
        }
        insertion_sort(arr, N);
        int64_t pairs = count_pairs(arr, N, TARGET);
        checksum += pairs;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
