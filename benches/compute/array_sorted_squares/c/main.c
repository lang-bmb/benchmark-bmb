// Array Sorted Squares — two-pointer merge to produce sorted squares of sorted array
// Measures: two-pointer merge, register carry (left, right), store to result
// Workload: N=1000000 array, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t sorted_squares(int64_t* arr, int64_t* result, int64_t n) {
    int64_t left = 0, right = n - 1, pos = n - 1;
    while (left <= right) {
        int64_t lv = arr[left];
        int64_t rv = arr[right];
        int64_t abs_l = lv < 0 ? -lv : lv;
        int64_t abs_r = rv < 0 ? -rv : rv;
        if (abs_l > abs_r) {
            result[pos] = abs_l * abs_l;
            left++;
        } else {
            result[pos] = abs_r * abs_r;
            right--;
        }
        pos--;
    }
    // Return checksum: sum of first 8 + last 8 elements
    int64_t cs = 0;
    for (int64_t j = 0; j < 8; j++) {
        cs += result[j];
        cs += result[n - 1 - j];
    }
    return cs;
}

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* result = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Fill with sorted values in range [-N/2, N/2)
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = i - N / 2 + seed % 3;
        }
        checksum += sorted_squares(arr, result, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    free(result);
    return 0;
}
