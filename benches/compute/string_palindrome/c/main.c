// String Palindrome — check if i64 arrays are palindromes
// Measures: two-pointer scan, comparison, early exit
// Workload: N=10000 array, 5000000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t is_palindrome(int64_t* arr, int64_t n) {
    int64_t lo = 0, hi = n - 1;
    while (lo < hi) {
        if (arr[lo] != arr[hi]) return 0;
        lo++;
        hi--;
    }
    return 1;
}

int main() {
    int64_t N = 10000;
    int64_t ITERS = 5000000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        arr[i] = seed % 100;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        if (iter % 1000 == 0) {
            for (int64_t i = 0; i < N / 2; i++) {
                arr[N - 1 - i] = arr[i];
            }
        } else {
            arr[N / 2] = iter % 200;
        }
        checksum += is_palindrome(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
