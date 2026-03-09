// Array Three Sum Closest — three pointers on sorted array to find closest sum to target
// Measures: three-pointer technique, register comparisons, sorted array scan
// Workload: N=5000, 200 iterations, pre-sorted array

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int cmp_i64(const void* a, const void* b) {
    int64_t va = *(const int64_t*)a;
    int64_t vb = *(const int64_t*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

static int64_t abs_i64(int64_t x) {
    return x < 0 ? -x : x;
}

static int64_t three_sum_closest(int64_t* arr, int64_t n, int64_t target) {
    int64_t best = arr[0] + arr[1] + arr[2];
    for (int64_t i = 0; i < n - 2; i++) {
        int64_t lo = i + 1;
        int64_t hi = n - 1;
        while (lo < hi) {
            int64_t s = arr[i] + arr[lo] + arr[hi];
            if (abs_i64(s - target) < abs_i64(best - target)) {
                best = s;
            }
            if (s < target) {
                lo++;
            } else if (s > target) {
                hi--;
            } else {
                return s;
            }
        }
    }
    return best;
}

int main() {
    int64_t N = 5000;
    int64_t ITERS = 200;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 100000 - 50000;
        }
        qsort(arr, N, sizeof(int64_t), cmp_i64);

        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t target = seed % 100000 - 50000;
        checksum += three_sum_closest(arr, N, target);
    }

    printf("%lld\n", (long long)(checksum % 1000000007));
    free(arr);
    return 0;
}
